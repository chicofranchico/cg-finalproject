/*
* A Shape Drawer class derived from Bullet Shape Drawer
* By JuanPi Carbajal carbajal@ifi.uzh.ch
* 05.2010
*/
#ifndef SHAPE_DRAWER_H
#define SHAPE_DRAWER_H

class btCollisionShape;
class btShapeHull;
#include "LinearMath/btAlignedObjectArray.h"
#include "LinearMath/btVector3.h"

#include "BulletCollision/CollisionShapes/btShapeHull.h"

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
	unsigned int						m_texturehandle;
	bool								m_textureenabled;
	bool								m_textureinitialized;
	

	ShapeCache*							cache(btConvexShape*);

public:
		 ShapeDrawer();

		virtual ~ ShapeDrawer();

		///drawOpenGL might allocate temporary memoty, stores pointer in shape userpointer
		virtual void drawOpenGL(btScalar* m, const btCollisionShape* shape, 
		const btVector3& color,int	debugMode,const btVector3& worldBoundsMin,
		const btVector3& worldBoundsMax);
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
		
};

void OGL_displaylist_register_shape(btCollisionShape * shape);
void OGL_displaylist_clean();

#endif //SHAPE_DRAWER_H

