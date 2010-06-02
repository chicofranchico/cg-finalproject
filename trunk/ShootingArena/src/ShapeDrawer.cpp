/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2006 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include "GLDebugFont.h"


#include "GlutStuffs.h"
#include "ShapeDrawer.h"
#include "BulletCollision/CollisionShapes/btPolyhedralConvexShape.h"
#include "BulletCollision/CollisionShapes/btTriangleMeshShape.h"
#include "BulletCollision/CollisionShapes/btBoxShape.h"
#include "BulletCollision/CollisionShapes/btSphereShape.h"
#include "BulletCollision/CollisionShapes/btConeShape.h"
#include "BulletCollision/CollisionShapes/btCylinderShape.h"
#include "BulletCollision/CollisionShapes/btTetrahedronShape.h"
#include "BulletCollision/CollisionShapes/btCompoundShape.h"
#include "BulletCollision/CollisionShapes/btCapsuleShape.h"
#include "BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h"
#include "BulletCollision/CollisionShapes/btUniformScalingShape.h"
#include "BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "BulletCollision/CollisionShapes/btMultiSphereShape.h"

///
#include "BulletCollision/CollisionShapes/btShapeHull.h"

#include "LinearMath/btTransformUtil.h"


#include "LinearMath/btIDebugDraw.h"
//for debugmodes

#include <stdio.h> //printf debugging

using namespace PAPI;


void  ShapeDrawer::drawCoordSystem()  {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(1, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 1, 0);
	glColor3f(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 1);
	glEnd();

}

class GlDrawcallback : public btTriangleCallback
{

public:

	bool	m_wireframe;

	GlDrawcallback()
		:m_wireframe(false)
	{
	}

	virtual void processTriangle(btVector3* triangle,int partId, int triangleIndex)
	{

		(void)triangleIndex;
		(void)partId;


		if (m_wireframe)
		{
			glBegin(GL_LINES);
			glColor3f(1, 0, 0);
			glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
			glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
			glColor3f(0, 1, 0);
			glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
			glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
			glColor3f(0, 0, 1);
			glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
			glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
			glEnd();
		} else
		{
			glBegin(GL_TRIANGLES);
    		btVector3 diff1 = triangle[1] - triangle[0];
    		btVector3 diff2 = triangle[2] - triangle[0];
    		btVector3 normal = diff1.cross(diff2);

    		normal.normalize();

    		glNormal3d(normal.getX(),normal.getY(),normal.getZ());
    		glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
    		glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
    		glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());

    		glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
    		glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
    		glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());

			glEnd();
		}
	}
};

class TriangleGlDrawcallback : public btInternalTriangleIndexCallback
{
public:
	virtual void internalProcessTriangleIndex(btVector3* triangle,int partId,int  triangleIndex)
	{
		(void)triangleIndex;
		(void)partId;


		glBegin(GL_TRIANGLES);//LINES);
		glColor3f(1, 0, 0);
		glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
		glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
		glColor3f(0, 1, 0);
		glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
		glVertex3d(triangle[1].getX(), triangle[1].getY(), triangle[1].getZ());
		glColor3f(0, 0, 1);
		glVertex3d(triangle[2].getX(), triangle[2].getY(), triangle[2].getZ());
		glVertex3d(triangle[0].getX(), triangle[0].getY(), triangle[0].getZ());
		glEnd();
	}
};


void  ShapeDrawer::drawSphere(btScalar radius, int lats, int longs) 
{
	int i, j;
	for(i = 0; i <= lats; i++) {
		btScalar lat0 = SIMD_PI * (-btScalar(0.5) + (btScalar) (i - 1) / lats);
		btScalar z0  = radius*sin(lat0);
		btScalar zr0 =  radius*cos(lat0);

		btScalar lat1 = SIMD_PI * (-btScalar(0.5) + (btScalar) i / lats);
		btScalar z1 = radius*sin(lat1);
		btScalar zr1 = radius*cos(lat1);

		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs; j++) {
			btScalar lng = 2 * SIMD_PI * (btScalar) (j - 1) / longs;
			btScalar x = cos(lng);
			btScalar y = sin(lng);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(x * zr1, y * zr1, z1);
			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(x * zr0, y * zr0, z0);
		}
		glEnd();
	}
}

void  ShapeDrawer::drawCylinder(float radius,float halfHeight, int upAxis)
{

	glPushMatrix();
	switch (upAxis)
	{
	case 0:
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, -halfHeight);
		break;
	case 1:
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		glTranslatef(0.0, 0.0, -halfHeight);
		break;
	case 2:

		glTranslatef(0.0, 0.0, -halfHeight);
		break;
	default:
		{
			btAssert(0);
		}

	}

	GLUquadricObj *quadObj = gluNewQuadric();

	//The gluCylinder subroutine draws a cylinder that is oriented along the z axis. 
	//The base of the cylinder is placed at z = 0; the top of the cylinder is placed at z=height. 
	//Like a sphere, the cylinder is subdivided around the z axis into slices and along the z axis into stacks.

	gluQuadricDrawStyle(quadObj, (GLenum)GLU_FILL);
	gluQuadricNormals(quadObj, (GLenum)GLU_SMOOTH);

	gluDisk(quadObj,0,radius,15, 10);

	gluCylinder(quadObj, radius, radius, 2.f*halfHeight, 15, 10);
	glTranslatef(0.0f, 0.0f, 2.f*halfHeight);
	glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
	gluDisk(quadObj,0.f,radius,15, 10);

	glPopMatrix();
	gluDeleteQuadric(quadObj);
}

 ShapeDrawer::ShapeCache*	ShapeDrawer::cache(btConvexShape* shape)
{
	ShapeCache*		sc=(ShapeCache*)shape->getUserPointer();
	if(!sc)
	{
		sc=new(btAlignedAlloc(sizeof(ShapeCache),16)) ShapeCache(shape);
		sc->m_shapehull.buildHull(shape->getMargin());
		m_shapecaches.push_back(sc);
		shape->setUserPointer(sc);
		/* Build edges	*/ 
		const int			ni=sc->m_shapehull.numIndices();
		const int			nv=sc->m_shapehull.numVertices();
		const unsigned int*	pi=sc->m_shapehull.getIndexPointer();
		const btVector3*	pv=sc->m_shapehull.getVertexPointer();
		btAlignedObjectArray<ShapeCache::Edge*>	edges;
		sc->m_edges.reserve(ni);
		edges.resize(nv*nv,0);
		for(int i=0;i<ni;i+=3)
		{
			const unsigned int* ti=pi+i;
			const btVector3		nrm=btCross(pv[ti[1]]-pv[ti[0]],pv[ti[2]]-pv[ti[0]]).normalized();
			for(int j=2,k=0;k<3;j=k++)
			{
				const unsigned int	a=ti[j];
				const unsigned int	b=ti[k];
				ShapeCache::Edge*&	e=edges[btMin(a,b)*nv+btMax(a,b)];
				if(!e)
				{
					sc->m_edges.push_back(ShapeCache::Edge());
					e=&sc->m_edges[sc->m_edges.size()-1];
					e->n[0]=nrm;e->n[1]=-nrm;
					e->v[0]=a;e->v[1]=b;
				}
				else
				{
					e->n[1]=nrm;
				}
			}
		}
	}
	return(sc);
}

void renderSquareA(float x, float y, float z)
{
	glBegin(GL_LINE_LOOP);
	glVertex3f(x, y, z);
	glVertex3f(x + 10.f, y, z);
	glVertex3f(x + 10.f, y + 10.f, z);
	glVertex3f(x, y + 10.f, z);
	glEnd();
}

inline void glDrawVector(const btVector3& v) { glVertex3d(v[0], v[1], v[2]); }


void  ShapeDrawer::drawOpenGL(btScalar* m, const btCollisionShape* shape, 
    int	debugMode,const btVector3& worldBoundsMin,
    const btVector3& worldBoundsMax, const int obj_id)
{

	
	glPushMatrix(); 
	btglMultMatrix(m);

	// Initialize the textures
	if(m_textureenabled && (!m_textureinitialized[obj_id]) )
		{
			
			// Here look for the texture arrays.
			printf("Loading Texture %s for Object %d\n",m_textureFile[obj_id].c_str(), obj_id);
			gl_texture_t *tga_tex = NULL;

            m_texturehandle[obj_id] = 0;

            tga_tex = ReadTGAFile (m_textureFile[obj_id].c_str());    
                                    
    		glGenTextures(1,(GLuint*)&m_texturehandle[obj_id]);
			glBindTexture(GL_TEXTURE_2D,m_texturehandle[obj_id]);
			glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

        	//filter modes
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

            printf("Read Texture %d x %d\n",tga_tex->width,tga_tex->height);
   		    gluBuild2DMipmaps(GL_TEXTURE_2D, tga_tex->internalFormat,
			 tga_tex->width, tga_tex->height,
			 tga_tex->format, GL_UNSIGNED_BYTE, tga_tex->texels);


			free (tga_tex->texels);
            free (tga_tex);

		}

		// Transform the textures
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glScalef(m_texturescale[obj_id],m_texturescale[obj_id],m_texturescale[obj_id]);
		glRotatef(m_texturerot[obj_id][0],1,0,0);
    	glRotatef(m_texturerot[obj_id][1],0,1,0);
		glRotatef(m_texturerot[obj_id][2],0,0,1);    	
		glMatrixMode(GL_MODELVIEW);

		static const GLfloat	planex[]={1,0,0,0};
		static const GLfloat	planey[]={0,1,0,0};
		static const GLfloat	planez[]={0,0,1,0};
			glTexGenfv(GL_S,GL_OBJECT_PLANE,planex);
			glTexGenfv(GL_T,GL_OBJECT_PLANE,planez);
			glTexGenfv(GL_R,GL_OBJECT_PLANE,planey);
						
			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
			glTexGeni(GL_R,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);			
			glEnable(GL_TEXTURE_GEN_S);
			glEnable(GL_TEXTURE_GEN_T);
			glEnable(GL_TEXTURE_GEN_R);
			m_textureinitialized[obj_id]=true;
	
		if(m_textureenabled) 
		{
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D,m_texturehandle[obj_id]);
		} else
		{
    		glDisable(GL_TEXTURE_2D);
    	}
   		glEnable(GL_COLOR_MATERIAL);
      	Color diff = m_materials[obj_id].getDiffuse();
        glColor3f(diff.r,diff.g,diff.b);
        	
		bool useWireframeFallback = true;

		if (!(debugMode & btIDebugDraw::DBG_DrawWireframe))
		{
			int shapetype=shape->getShapeType();
			switch (shapetype)
			{

				case SPHERE_SHAPE_PROXYTYPE:
				{
					const btSphereShape* sphereShape = static_cast<const btSphereShape*>(shape);
					float radius = sphereShape->getMargin();//radius doesn't include the margin, so draw with margin
					drawSphere(radius,10,10);
					useWireframeFallback = false;
					break;
				}

    		default:
				{


					if (shape->isConvex())
					{
						ShapeCache*	sc=cache((btConvexShape*)shape);
        
						btShapeHull* hull = &sc->m_shapehull;
						if (hull->numTriangles () > 0)
						{
								int index = 0;
								const unsigned int* idx = hull->getIndexPointer();
								const btVector3* vtx = hull->getVertexPointer();

								glBegin (GL_TRIANGLES);

								for (int i = 0; i < hull->numTriangles (); i++)
								{
									int i1 = index++;
									int i2 = index++;
									int i3 = index++;
									btAssert(i1 < hull->numIndices () &&
										i2 < hull->numIndices () &&
										i3 < hull->numIndices ());

									int index1 = idx[i1];
									int index2 = idx[i2];
									int index3 = idx[i3];
									btAssert(index1 < hull->numVertices () &&
										index2 < hull->numVertices () &&
										index3 < hull->numVertices ());

									btVector3 v1 = vtx[index1];
									btVector3 v2 = vtx[index2];
									btVector3 v3 = vtx[index3];
									btVector3 normal = (v3-v1).cross(v2-v1);
									normal.normalize ();
									glNormal3f(normal.getX(),normal.getY(),normal.getZ());
									glVertex3f (v1.x(), v1.y(), v1.z());
									glVertex3f (v2.x(), v2.y(), v2.z());
									glVertex3f (v3.x(), v3.y(), v3.z());

								}
								glEnd ();

						}
					}
				}
			}

		}


		glNormal3f(0,1,0);
	

		if (shape->isConcave() && !shape->isInfinite())
		{
			btConcaveShape* concaveMesh = (btConcaveShape*) shape;

			GlDrawcallback drawCallback;
			drawCallback.m_wireframe = (debugMode & btIDebugDraw::DBG_DrawWireframe)!=0;

			concaveMesh->processAllTriangles(&drawCallback,worldBoundsMin,worldBoundsMax);

		}

	glPopMatrix();

}


void ShapeDrawer::drawShadow(btScalar* m,const btVector3& extrusion,
            const btCollisionShape* shape,const btVector3& worldBoundsMin,
            const btVector3& worldBoundsMax)
{
	glPushMatrix(); 
	btglMultMatrix(m);
	
	if (shape->isConvex())
		{
			ShapeCache*	sc=cache((btConvexShape*)shape);
			btShapeHull* hull =&sc->m_shapehull;
			glBegin(GL_QUADS);
			for(int i=0;i<sc->m_edges.size();++i)
			{			
				const btScalar		d=btDot(sc->m_edges[i].n[0],extrusion);
				if((d*btDot(sc->m_edges[i].n[1],extrusion))<0)
				{
					const int			q=	d<0?1:0;
					const btVector3&	a=	hull->getVertexPointer()[sc->m_edges[i].v[q]];
					const btVector3&	b=	hull->getVertexPointer()[sc->m_edges[i].v[1-q]];
					glVertex3f(a[0],a[1],a[2]);
					glVertex3f(b[0],b[1],b[2]);
					glVertex3f(b[0]+extrusion[0],b[1]+extrusion[1],b[2]+extrusion[2]);
					glVertex3f(a[0]+extrusion[0],a[1]+extrusion[1],a[2]+extrusion[2]);
				}
			}
			glEnd();
		}

	if (shape->isConcave())
	{
		btConcaveShape* concaveMesh = (btConcaveShape*) shape;

		GlDrawcallback drawCallback;
		drawCallback.m_wireframe = false;
		concaveMesh->processAllTriangles(&drawCallback,worldBoundsMin,worldBoundsMax);

	}
	glPopMatrix();

}

//
ShapeDrawer::ShapeDrawer()
{
	m_textureenabled		=	true;
}

ShapeDrawer::~ShapeDrawer()
{
	int i;
	for (i=0;i<m_shapecaches.size();i++)
	{
		m_shapecaches[i]->~ShapeCache();
		btAlignedFree(m_shapecaches[i]);
	}
	m_shapecaches.clear();
	for(int i=0; i<m_textureinitialized.size();i++)
    	if(m_textureinitialized[i])
	    {
		glDeleteTextures(1,(const GLuint*) &m_texturehandle[i]);
	    }
}

