/*
Based on Bullet demo suit
*/

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btSphereSphereCollisionAlgorithm.h"
#include "BulletCollision/CollisionDispatch/btSphereTriangleCollisionAlgorithm.h"
#include "BulletCollision/Gimpact/btGImpactShape.h"
#include "BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h"

#include "LinearMath/btQuickprof.h"
#include "LinearMath/btIDebugDraw.h"

#include "GLDebugFont.h"
#include <stdio.h> //printf debugging

#include "ShootingDemo.h"
#include "ShapeDrawer.h"

#include "GlutStuff.h"

#include "BunnyMesh.h"

#include "material.hpp"

static float gCollisionMargin = 0.05f;
extern float eye[3];

extern int glutScreenWidth;
extern int glutScreenHeight;

const int maxProxies = 32766;
const int maxOverlap = 65535;

bool createConstraint = true;

const int gNumObjects = 400;


const int maxNumObjects = 32760;

int	shapeIndex[maxNumObjects];

int flag = 0;

float px = 0.0;
float py = 4.0;
float pz = 4.0;


#define CUBE_HALF_EXTENTS 0.5
#define BIG_CUBE_HALF_EXTENTS 0.8

void ShootingDemo::createShelf(float xSpan,float ySpan, float zSpan,
	            btVector3 pos, float yAngle, float zAngle )
{
     btTransform trans;
	 trans.setIdentity();
	 trans.setOrigin(pos);
	
	 btQuaternion rot;
     rot.setRotation(btVector3(0.f,1.f,0.f),yAngle*3.1415/180.f);
	 trans.setRotation(rot);

     btCollisionShape* shape = new btBoxShape(btVector3(xSpan,ySpan,zSpan));//floor
	 btRigidBody* body = localCreateRigidBody(0.f,trans,shape);
     obj_id.insert ( std::pair<btRigidBody*,int>(body,ShootingDemo::table) );
    
     body->setCollisionFlags(body->getCollisionFlags()|btCollisionObject::CF_STATIC_OBJECT);
}	            
	            
void ShootingDemo::createPyramid(btCollisionShape* shape, float halfElemSize, btScalar elemMass, 
	            int nRows, btVector3 pos, float angle )
{
	btTransform trans, orient;
	trans.setIdentity();
    orient.setIdentity();

    btQuaternion rot;
    rot.setRotation(btVector3(0.f,1.f,0.f),angle*3.1415/180.f);
	orient.setRotation(rot);
	

	for(int i=0; i<nRows; i++)
	{
		// This constructs a row, from left to right
		int rowSize = nRows - i;
		for(int j=0; j< rowSize; j++)
		{
			btVector3 elemPos;
			elemPos.setValue(
				-rowSize * halfElemSize + halfElemSize + j * 2.0f * halfElemSize,
				halfElemSize + i * halfElemSize * 2.0f,
				0.f);

			trans.setOrigin(orient*elemPos + pos);

			btRigidBody* body = 0;
			body = localCreateRigidBody(elemMass,trans,shape);
	        obj_id.insert ( std::pair<btRigidBody*,int>(body,ShootingDemo::can) );

		}
	}
	
	// Shelf
    btVector3 mov(0.f,-halfElemSize,.0f);
    createShelf(nRows*halfElemSize,.1f,halfElemSize*2.f, pos+mov,angle,0.f);

}
void	ShootingDemo::initGImpactCollision()
{
	// create trimesh
	btTriangleIndexVertexArray* indexVertexArrays = new btTriangleIndexVertexArray(BUNNY_NUM_TRIANGLES,
		&gIndicesBunny[0][0],
		3*sizeof(int),
		BUNNY_NUM_VERTICES,(REAL*) &gVerticesBunny[0],sizeof(REAL)*3);

	btGImpactMeshShape * trimesh = new btGImpactMeshShape(indexVertexArrays);
	m_trimeshShape = trimesh;

	//register algorithm

	btCollisionDispatcher * dispatcher = static_cast<btCollisionDispatcher *>(m_dynamicsWorld ->getDispatcher());
	btGImpactCollisionAlgorithm::registerAlgorithm(dispatcher);

}

int ShootingDemo::createMovingTarget(btScalar scale,btScalar mass, 
	            btScalar angle, btVector3 sliderWorldPos, btVector3 sliderAxis,
	            float speed, bool motorized)
{
    //create trimesh model and shape
    initGImpactCollision();

        btTransform trans;
        
        trans.setIdentity();
        trans.setOrigin(sliderWorldPos);
		btMatrix3x3 sliderOrientation(btQuaternion(sliderAxis ,angle*SIMD_PI/180.f));
		trans.setBasis(sliderOrientation);
	
	    btGImpactMeshShape *bunny = m_trimeshShape;
        bunny->setLocalScaling(btVector3(scale,scale,scale));
	    bunny->updateBound();

        btAABB box = bunny->getLocalBox ();
        btVector3 mov=box.m_min;
	    
		
        btScalar targetHeight=1.f;

        btScalar lowerSliderLimit = -10;
        btScalar hiSliderLimit = 10;

    
        btRigidBody* d6body0 = 0;
        btSliderConstraint* spSlider6Dof = NULL;

		d6body0 = localCreateRigidBody( mass,trans,bunny);
		
        obj_id.insert ( std::pair<btRigidBody*,int>(d6body0,ShootingDemo::bunny) );         
        
//		d6body0->setActivationState(DISABLE_DEACTIVATION);

		btRigidBody* fixedBody1 = localCreateRigidBody(0,trans,0);
		m_dynamicsWorld->addRigidBody(fixedBody1);

		btTransform frameInA, frameInB;
		frameInA = btTransform::getIdentity();
		frameInB = btTransform::getIdentity();
		frameInA.setOrigin(btVector3(0., 5., 0.));
		frameInB.setOrigin(btVector3(0., 5., 0.));
        
		bool useLinearReferenceFrameA = true;
		spSlider6Dof = new btSliderConstraint(*fixedBody1, *d6body0,frameInA,frameInB,useLinearReferenceFrameA);
		spSlider6Dof->setLowerLinLimit(lowerSliderLimit);
		spSlider6Dof->setUpperLinLimit(hiSliderLimit);

		//range should be small, otherwise singularities will 'explode' the constraint
		spSlider6Dof->setLowerAngLimit(0);
		spSlider6Dof->setUpperAngLimit(0);

		spSlider6Dof->setPoweredLinMotor(motorized);
		spSlider6Dof->setTargetLinMotorVelocity(speed);
		spSlider6Dof->setMaxLinMotorForce(1.0f);


		m_dynamicsWorld->addConstraint(spSlider6Dof);
		movingTargets.push_back((btSliderConstraint*)m_dynamicsWorld->
		                  getConstraint(m_dynamicsWorld->getNumConstraints()-1));
		
		// Rail
		float length=hiSliderLimit-lowerSliderLimit;
		float width=box.m_max[1]-box.m_min[1];
		mov.setValue(0,mov[1]-.25,0);
	    btVector3 final_pos=sliderWorldPos+mov;
        createShelf(length/2,0.2,width/2,final_pos ,angle,0.f);	
        
        // Sound - not really good
//        sounder.setSourcePosition(-final_pos[0],final_pos[1],final_pos[2]);
//        sounder.playSound(BELT);        
        	                  
		return    movingTargets.size()-1;
		               
}

void ShootingDemo::eraseSlider(btSliderConstraint * slider)
{
		// Apply impulses
  		m_dynamicsWorld->removeConstraint((btTypedConstraint*)slider);
//        printf("Erased\n");
		movingTargets.remove(slider);
// Experimental not really working as desired
        sounder.stopSound(BELT);        
		
}

void ShootingDemo::eraseBullet(btRigidBody * obj)
{
		if (obj && obj->getMotionState())
		{
			delete obj->getMotionState();
		}
		bullets.remove(obj);
		obj_id.erase(obj);
		
		m_dynamicsWorld->removeCollisionObject( obj );
		delete obj;
}

void ShootingDemo::createScenario()
{
	float mass = 0.f;
	btTransform	startTransform;
	startTransform.setIdentity();

	btCollisionShape* staticboxShape1 = new btBoxShape(btVector3(arenaWidth,.1,arenaDepth));//floor
	btCollisionShape* staticboxShape2 = new btBoxShape(btVector3(.1,arenaHeight,arenaDepth));//left wall
	btCollisionShape* staticboxShape3 = new btBoxShape(btVector3(.1,arenaHeight,arenaDepth));//right wall
	btCollisionShape* staticboxShape4 = new btBoxShape(btVector3(arenaWidth,arenaHeight,.1));//back wall
    btCollisionShape* staticboxShape5 = new btBoxShape(btVector3(arenaWidth,.1,arenaDepth));//ceiling

// Floor
	startTransform.setOrigin(btVector3(0,-arenaHeight,arenaDepth)+m_cameraTargetPosition);
    btRigidBody* staticBody = localCreateRigidBody(mass, startTransform,staticboxShape1);
   	staticBody->setCollisionFlags(staticBody->getCollisionFlags()|btCollisionObject::CF_STATIC_OBJECT);
    obj_id.insert ( std::pair<btRigidBody*,int>(staticBody,ShootingDemo::ground) );     	
//Walls
	startTransform.setOrigin(btVector3(-arenaWidth,0.f,arenaDepth)+m_cameraTargetPosition);
    staticBody = localCreateRigidBody(mass, startTransform,staticboxShape2);
   	staticBody->setCollisionFlags(staticBody->getCollisionFlags()|btCollisionObject::CF_STATIC_OBJECT);
    obj_id.insert ( std::pair<btRigidBody*,int>(staticBody,ShootingDemo::wall) );     	

	startTransform.setOrigin(btVector3(arenaWidth,0.f,arenaDepth)+m_cameraTargetPosition);
    staticBody = localCreateRigidBody(mass, startTransform,staticboxShape3);
   	staticBody->setCollisionFlags(staticBody->getCollisionFlags()|btCollisionObject::CF_STATIC_OBJECT);
    obj_id.insert ( std::pair<btRigidBody*,int>(staticBody,ShootingDemo::wall) );     	

	startTransform.setOrigin(btVector3(0.f,0.f,arenaDepth)+m_cameraTargetPosition);
    staticBody = localCreateRigidBody(mass, startTransform,staticboxShape4);
   	staticBody->setCollisionFlags(staticBody->getCollisionFlags()|btCollisionObject::CF_STATIC_OBJECT);
    obj_id.insert ( std::pair<btRigidBody*,int>(staticBody,ShootingDemo::wall) );     	

// Ceiling
	startTransform.setOrigin(btVector3(0.f,arenaHeight,arenaDepth)+m_cameraTargetPosition);
    staticBody = localCreateRigidBody(mass, startTransform,staticboxShape5);
   	staticBody->setCollisionFlags(staticBody->getCollisionFlags()|btCollisionObject::CF_STATIC_OBJECT);
    obj_id.insert ( std::pair<btRigidBody*,int>(staticBody,ShootingDemo::roof) );     	
    
}
////////////////////////////////////

bool ShootingDemo::isBullet(btCollisionObject* obj)
{
    for (int j=0; j<bullets.size(); j++)
    {
        if ( obj == bullets[j] )
            return true;   
    }
    return false;
}
bool ShootingDemo::isMovingTarget(btCollisionObject* obj,btSliderConstraint*& slider)
{
    
    for (int j=0; j<movingTargets.size(); j++)
    {
        slider = movingTargets[j];
        const btCollisionObject* body = &(slider->getRigidBodyB());

        if ( obj == body )
             return true;   
    }
    return false;
}

//experimental jitter damping (1 = no damping, 0 = total damping once motion below threshold)
extern btScalar gJitterVelocityDampingFactor;

extern int gNumManifold;
extern int gOverlappingPairs;

void ShootingDemo::clientMoveAndDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	float dt = getDeltaTimeMicroseconds() * 0.000001f;

	//printf("dt = %f: ",dt);
	if (m_dynamicsWorld)
	{

		//during idle mode, just run 1 simulation step maximum
		int maxSimSubSteps = m_idle ? 1 : 1;
		if (m_idle)
			dt = 1.0/420.f;

		int numSimSteps = 0;
		numSimSteps = m_dynamicsWorld->stepSimulation(dt,maxSimSubSteps);

		//optional but useful: debug drawing
		m_dynamicsWorld->debugDrawWorld();

	}

	renderme();

	updateCamera();

	glFlush();
	//some additional debugging info

	glutSwapBuffers();

    btSliderConstraint* moving=0;
    
    // Check collision with bullets
    int numManifolds = m_dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold =  m_dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
		
            
		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
            
            if (isBullet(obB))
             {
                if( isMovingTarget(obA,moving))
                   eraseSlider(moving);

                eraseBullet(btRigidBody::upcast(obB));

                sounder.setSourcePosition(-ptB[0],ptB[1],ptB[2]);
                sounder.playSound(BOOM);
		
		px = ptB[0];
		py = ptB[1];
		pz = ptB[2];
		flag = 1;

             }
            else if (isBullet(obA))
             {
                if( isMovingTarget(obB,moving))
                   eraseSlider(moving);

                eraseBullet(btRigidBody::upcast(obA));
                printf("Boom!!\n");
             }

			}
		}
	}

	// Check moving targets
	for(int i=0; i<movingTargets.size(); i++)
	{
	   moving = movingTargets[i];

	   if (moving->getLinearPos() >= moving->getUpperLinLimit ()-.1 &&
	   moving->getTargetLinMotorVelocity ()>0)
	       moving->setTargetLinMotorVelocity(-moving->getTargetLinMotorVelocity ());

	   if (moving->getLinearPos() <= moving->getLowerLinLimit ()+.1 &&
	   moving->getTargetLinMotorVelocity ()<0)
           moving->setTargetLinMotorVelocity(-moving->getTargetLinMotorVelocity ());
    }

}

void ShootingDemo::displayCallback(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderme();

	//optional but useful: debug drawing
	if (m_dynamicsWorld)
		m_dynamicsWorld->debugDrawWorld();

	glFlush();
	glutSwapBuffers();
}
void	ShootingDemo::setupEmptyDynamicsWorld()
{
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_overlappingPairCache = new btDbvtBroadphase();
	m_constraintSolver = new btSequentialImpulseConstraintSolver();
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher,m_overlappingPairCache,m_constraintSolver,m_collisionConfiguration);

    ///SOLVER_RANDMIZE_ORDER makes cylinder stacking a bit more stable
	m_dynamicsWorld->getSolverInfo().m_solverMode |= SOLVER_RANDMIZE_ORDER;

    m_dynamicsWorld->getSolverInfo().m_numIterations = 4;

	m_dynamicsWorld->getDispatchInfo().m_enableSPU = true;

	m_dynamicsWorld->setGravity(btVector3(0,-10,0));

   // Configure Fixed parameters
   
   // Members related to the arena
   arenaDepth = 45.f;
   arenaWidth = 20.f;
   arenaHeight = 15.f;
   
   // Sun direction
   m_sundirection.setValue(1000,-400,1000);

   //Camera Position
   setCameraDistance(2.f);
   setCameraTargetPosition(0.f,15.f,0.f);
 
   // bullet Speed
   m_ShootBoxInitialSpeed=40.f;  
}


void	ShootingDemo::initPhysics()
{
	setTexturing(true);
	setShadows(false);

	setupEmptyDynamicsWorld();
	
	///Please don't make the box sizes larger then 1000: the collision detection will be inaccurate.
	///See http://www.continuousphysics.com/Bullet/phpBB2/viewtopic.php?t=346
//	m_collisionShapes.push_back(new btBoxShape (btVector3(200,CUBE_HALF_EXTENTS,200)));

    // Scenario
    createScenario();
	
	// Pyramids
	m_collisionShapes.push_back(new btCylinderShape (btVector3(CUBE_HALF_EXTENTS,CUBE_HALF_EXTENTS,CUBE_HALF_EXTENTS)));
	m_collisionShapes.push_back(new btCylinderShape (btVector3(BIG_CUBE_HALF_EXTENTS,BIG_CUBE_HALF_EXTENTS,BIG_CUBE_HALF_EXTENTS)));
	
	// On the Left wall
	btVector3 pos(arenaWidth-2.f*CUBE_HALF_EXTENTS,0.f,1.5*arenaDepth/2.f);
    createPyramid(m_collisionShapes[0], CUBE_HALF_EXTENTS, 1.f,
    6,pos+m_cameraTargetPosition, 90.f );

    pos.setValue(arenaWidth-2.f*CUBE_HALF_EXTENTS,0.f,arenaDepth/2.f);    
    createPyramid(m_collisionShapes[0], CUBE_HALF_EXTENTS, 4.f, 
	            8, pos+m_cameraTargetPosition, 90.f );
    
    // Diagonal on the Back
    pos.setValue(arenaWidth/3.f,0.f,arenaDepth*.8);    
    createPyramid(m_collisionShapes[0], CUBE_HALF_EXTENTS, 1.f, 
	            6, pos+m_cameraTargetPosition, 30.f );

    pos.setValue(-arenaWidth/3.f,0.f,arenaDepth*.8);    
    createPyramid(m_collisionShapes[0], CUBE_HALF_EXTENTS, 1.f, 
	            6, pos+m_cameraTargetPosition, -30.f );

    // On the middle
    pos.setValue(3*arenaWidth/8.f,0.f,arenaDepth/2.f);    
    createPyramid(m_collisionShapes[0], CUBE_HALF_EXTENTS, 1.f, 
	            6, pos+m_cameraTargetPosition, -45.f );

    pos.setValue(-3*arenaWidth/8.f,0.f,arenaDepth/2.f);    
    createPyramid(m_collisionShapes[0], CUBE_HALF_EXTENTS, 1.f, 
	            6, pos+m_cameraTargetPosition, 45.f );

    // Big one hidding bunnies
    pos.setValue(-2.5*arenaWidth/8.f,-arenaHeight+.3,arenaDepth*5.f/12.f);    
    createPyramid(m_collisionShapes[1], BIG_CUBE_HALF_EXTENTS, 18.f, 
	            12, pos+m_cameraTargetPosition, 0.f );

    // Small Bunnies
    pos.setValue(-3*arenaWidth/8.f,arenaHeight*0.1,arenaDepth*.7);    
    btVector3 axis(0.f,1.f,0.f);
    createMovingTarget(1.f, 1.f,180.f, pos+m_cameraTargetPosition, axis,9.2f,true);

    pos.setValue(-3*arenaWidth/8.f,-arenaHeight/3.f,arenaDepth*.8);    
    createMovingTarget(1.f, 1.f,180.f, pos+m_cameraTargetPosition, axis,9.f,true);

    pos.setValue(-3*arenaWidth/8.f,-arenaHeight/3.f,arenaDepth/2.f);    
    createMovingTarget(1.f, 1.f,180.f, pos+m_cameraTargetPosition, axis,8.f,true);
    
    pos.setValue(-3*arenaWidth/8.f,-arenaHeight/4.f,arenaDepth/3.f);    
    createMovingTarget(1.f, 1.f,180.f, pos+m_cameraTargetPosition, axis,7.8f,true);

    pos.setValue(-3*arenaWidth/8.f,-3*arenaHeight/8.f,arenaDepth/4.f);    
    createMovingTarget(1.f, 1.f,180.f, pos+m_cameraTargetPosition, axis,8.9f,true);

    // Big bunnies
    pos.setValue(arenaWidth/2.f,-arenaHeight/2.f,arenaDepth/4.f);    
    createMovingTarget(3.f, 1.f,250.f, pos+m_cameraTargetPosition, axis,-5.f,true);

}

void	ShootingDemo::exitPhysics()
{
	//cleanup in the reverse order of creation/initialization
	int i;
	
    //removed/delete constraints
	for (i=m_dynamicsWorld->getNumConstraints()-1; i>=0 ;i--)
	{
		btTypedConstraint* constraint = m_dynamicsWorld->getConstraint(i);
		m_dynamicsWorld->removeConstraint(constraint);
		delete constraint;
	}
	//remove the rigidbodies from the dynamics world and delete them
	for (i=m_dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject( obj );
		delete obj;
	}

	//delete collision shapes
	for (int j=0;j<m_collisionShapes.size();j++)
	{
		btCollisionShape* shape = m_collisionShapes[j];
		m_collisionShapes[j] = 0;
		delete shape;
	}

	//delete dynamics world
	delete m_dynamicsWorld;

	//delete solver
	delete m_constraintSolver;

	//delete broadphase
	delete m_overlappingPairCache;

	//delete dispatcher
	delete m_dispatcher;

	delete m_collisionConfiguration;

}

void ShootingDemo::setShootBoxShape ()
{
   if (!m_shootBoxShape)
   {
   	m_shootBoxShape = new btSphereShape(.3f);
   }
}    

void ShootingDemo::shootBox(const btVector3& destination)
{

	if (m_dynamicsWorld)
	{
		float mass = 1.f;
		btTransform startTransform;
		startTransform.setIdentity();
		btVector3 camPos = getCameraPosition();
		startTransform.setOrigin(camPos);

		setShootBoxShape ();

		btRigidBody* body = this->localCreateRigidBody(mass, startTransform,m_shootBoxShape);
        bullets.push_back(body);
        obj_id.insert ( std::pair<btRigidBody*,int>(body,ShootingDemo::ball) );   
        
		body->setLinearFactor(btVector3(1,1,1));

		btVector3 linVel(destination[0]-camPos[0],destination[1]-camPos[1],destination[2]-camPos[2]);
		linVel.normalize();
		linVel*=m_ShootBoxInitialSpeed;

		body->getWorldTransform().setOrigin(camPos);
		body->getWorldTransform().setRotation(btQuaternion(0,0,0,1));
		body->setLinearVelocity(linVel);
		body->setAngularVelocity(btVector3(0,0,0));
		body->setCcdMotionThreshold(1.);
		body->setCcdSweptSphereRadius(0.2f);
		
        sounder.setSourcePosition(-camPos[0],camPos[1],camPos[2]);
        sounder.playSound(BANG);
      	m_boxes += 1;
        
	}
}

void ShootingDemo::myinit(void)
{

	GLfloat light_ambient[] = { btScalar(0.2), btScalar(0.2), btScalar(0.2), btScalar(1.0) };
	GLfloat light_diffuse[] = { btScalar(1.0), btScalar(1.0), btScalar(1.0), btScalar(1.0) };
	GLfloat light_specular[] = { btScalar(1.0), btScalar(1.0), btScalar(1.0), btScalar(1.0 )};
	/*	light_position is NOT default value	*/
	GLfloat light_position0[] = { btScalar(1.0), btScalar(10.0), btScalar(1.0), btScalar(0.0 )};
	GLfloat light_position1[] = { btScalar(-1.0), btScalar(-10.0), btScalar(-1.0), btScalar(0.0) };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(btScalar(0.7),btScalar(0.7),btScalar(0.7),btScalar(0));
	
	m_shapeDrawer->m_textureFile[ball]="../tex/test.tga";
	m_shapeDrawer->m_texturescale[ball]=1.f;
	Material mat;
    mat.setDiffuse(Color(1.f,1.0f,0.5f));
    m_shapeDrawer->m_materials[ball]=mat;
    
	m_shapeDrawer->m_textureFile[roof]="../tex/test.tga";
	m_shapeDrawer->m_texturescale[roof]=1.f;
    m_shapeDrawer->m_materials[roof]=mat;

	m_shapeDrawer->m_textureFile[wall]="../tex/woodwalltex.tga";
	m_shapeDrawer->m_texturescale[wall]=0.08f;	
	m_shapeDrawer->m_texturerot[wall]=btVector3(90,0,0);                	
    m_shapeDrawer->m_materials[wall]=mat;

    m_shapeDrawer->m_textureFile[ground]="../tex/rockgroundtex.tga";    
   	m_shapeDrawer->m_texturescale[ground]=0.05f;
    m_shapeDrawer->m_materials[ground]=mat;

    m_shapeDrawer->m_textureFile[can]="../tex/Soupcan.tga";
   	m_shapeDrawer->m_texturescale[can]=0.8f;    
	m_shapeDrawer->m_texturerot[can]=btVector3(90,0,0); 
    m_shapeDrawer->m_materials[can]=mat;

    m_shapeDrawer->m_textureFile[table]="../tex/test.tga";
   	m_shapeDrawer->m_texturescale[table]=0.3f;    
	m_shapeDrawer->m_texturerot[table]=btVector3(0,0,45);                	   	
    m_shapeDrawer->m_materials[table]=mat;

	m_shapeDrawer->m_textureFile[bunny]="../tex/bunnytex.tga";
    m_shapeDrawer->m_materials[bunny]=mat;
   	m_shapeDrawer->m_texturescale[bunny]=0.1f;  	
	m_shapeDrawer->m_texturerot[bunny]=btVector3(0,0,90);                	
	
	//  glEnable(GL_CULL_FACE);
	//  glCullFace(GL_BACK);
}

