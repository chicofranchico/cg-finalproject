/*
* A Shape Drawer class derived from Bullet Shape Drawer
* By JuanPi Carbajal carbajal@ifi.uzh.ch
* 05.2010
*/
#ifndef SHAPE_DRAWER_H
#define SHAPE_DRAWER_H

//#include <cmath>
//#include <iostream>
//#include <fstream>

class btCollisionShape;
class btShapeHull;
#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btVector3.h"

#include "BulletCollision/CollisionShapes/btShapeHull.h"

#include "../End/Particle/pAPI.h"

#include <map>
#include <string>
#include "tga.h"
#include "material.hpp"

using namespace PAPI;

/// OpenGL shape drawing
class  ShapeDrawer
{
protected:
	struct ShapeCache
	{
    	struct Edge { btVector3 n[2];int v[2]; };
	    ShapeCache(btConvexShape* s) : m_shapehull(s) {}
	    btShapeHull					m_shapehull;
	    btAlignedObjectArray<Edge>	m_edges;
	};
	
	//clean-up memory of dynamically created shape hulls
	
	btAlignedObjectArray<ShapeCache*>	m_shapecaches;
 
    std::map<int,unsigned int>	        m_texturehandle;
    bool            					m_textureenabled;
	std::map<int,bool>					m_textureinitialized;
	
	

	ShapeCache*							cache(btConvexShape*);

public:
       // Textures
        std::map<int,std::string>         m_textureFile;
        std::map<int,float>	            m_texturescale;
        std::map<int,btVector3>	        m_texturerot;                
        std::map<int,Material>            m_materials;

	ParticleContext_t P;

		 ShapeDrawer();

		virtual ~ ShapeDrawer();

		///drawOpenGL might allocate temporary memoty, stores pointer in shape userpointer
		virtual void drawOpenGL(btScalar* m, const btCollisionShape* shape, 
                                int	debugMode,const btVector3& worldBoundsMin,
		const btVector3& worldBoundsMax, const int obj_id);
		virtual void drawShadow(btScalar* m, const btVector3& extrusion,
		const btCollisionShape* shape,const btVector3& worldBoundsMin,
		const btVector3& worldBoundsMax);
		
		bool enableTexture(bool enable) { bool p=m_textureenabled;m_textureenabled=enable;return(p); }
		bool hasTextureEnabled() const
		{
			return m_textureenabled;
		}
		
		static void		drawCylinder(float radius,float halfHeight, int upAxis);
		void			drawSphere(btScalar r, int lats, int longs);
		static void		drawCoordSystem();
		
		GLbyte* gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);
};

void OGL_displaylist_register_shape(btCollisionShape * shape);
void OGL_displaylist_clean();

#endif //SHAPE_DRAWER_H

