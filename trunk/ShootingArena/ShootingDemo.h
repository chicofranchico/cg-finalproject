/*

*/

#ifndef SHOOTING_DEMO_H
#define SHOOTING_DEMO_H

#include "GlutDemoApplication.h"
#include "LinearMath/btAlignedObjectArray.h"

#include "soundClass.hpp"


class btBroadphaseInterface;
class btCollisionShape;
class btOverlappingPairCache;
class btCollisionDispatcher;
class btConstraintSolver;
struct btCollisionAlgorithmCreateFunc;
class btDefaultCollisionConfiguration;
class btSliderConstraint;
class btTriangleIndexVertexArray;
class btGImpactMeshShape;
class btCollisionObject;

///ShootingDemo shows basic stacking using Bullet physics, and allows toggle of Ccd (using key '1')
class ShootingDemo : public GlutDemoApplication
{
	//keep the collision shapes, for deletion/cleanup
	btAlignedObjectArray<btCollisionShape*>	m_collisionShapes;

	btBroadphaseInterface*	m_overlappingPairCache;

	btCollisionDispatcher*	m_dispatcher;

	btConstraintSolver*	m_constraintSolver;

	btDefaultCollisionConfiguration* m_collisionConfiguration;

	btCollisionAlgorithmCreateFunc*	m_boxBoxCF;

    btTriangleIndexVertexArray* m_indexVertexArrays;
    
    btGImpactMeshShape * m_trimeshShape;

public:

    void myinit(void);

	void	initPhysics();

	void	exitPhysics();

	virtual ~ShootingDemo()
	{
		exitPhysics();
	}

    // Dispaly methods
	virtual void clientMoveAndDisplay();

	virtual void displayCallback();
	
	// Configuration Methods
    void setupEmptyDynamicsWorld();	
    
    void initGImpactCollision();

	static DemoApplication* Create()
	{
		ShootingDemo* demo = new ShootingDemo;
		demo->myinit();
		demo->initPhysics();
		return demo;
	}
    
    void setShootBoxShape ();
    
    // Objects Creation Methods
    void createScenario();
    
	void createPyramid(btCollisionShape* shape, float halfElemSize, btScalar elemMass, 
	            int nRows, btVector3 pos, float angle );

	void createWall( btCollisionShape* shape, float halfCubeSize, int size, float yPos );
		
	int createMovingTarget(btScalar scale,btScalar mass, 
	            btScalar angle, btVector3 sliderWorldPos, btVector3 sliderAxis,
	            float speed, bool motorized);

	void createShelf(float xSpan,float ySpan, float zSpan, 
	            btVector3 pos, float yAngle, float zAngle );

    void shootBox(const btVector3& destination);

	// Objects Destruction methods
	void eraseSlider(btSliderConstraint* slider);
	
	void eraseBullet(btRigidBody * obj);
	
    // Camera manipulation methods
    void setCameraTargetPosition(float x,float y, float z)
    {
        m_cameraTargetPosition.setValue(x,y,z);
    }
    
    // Logical functions
    bool isBullet(btCollisionObject* obj);
    bool isMovingTarget(btCollisionObject* obj,btSliderConstraint*& slider); 
    
public:

    // Array of moving targets
    btAlignedObjectArray<btSliderConstraint*> movingTargets;
    
    // Array of bullets
    btAlignedObjectArray<btRigidBody*> bullets;
    
    // Members related to the arena
    btScalar arenaDepth;
    btScalar arenaWidth;
    btScalar arenaHeight;
    
    // Placeholders for Shelfs
    btAlignedObjectArray<btVector3> shelfPosition;

    // Shape for pyramids elements
    btCollisionShape* pyramidShape;
    
    // Starts and end of conveyor belts
    btAlignedObjectArray<btVector3> conveyorStart;
    btAlignedObjectArray<btVector3> conveyorEnd;
    
    // Sound synthetizer
    SoundClass sounder;
};

#endif //SHOOTING_DEMO_H
