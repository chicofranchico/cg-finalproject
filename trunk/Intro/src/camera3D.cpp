/**
 * camera3D.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   23.03.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "camera3D.hpp"

// Includes
#include "opengl_includes.hpp"


GRAPHICSLAB_NAMESPACE_BEGIN


Camera3D::Camera3D( Scene &scene ) :
    Camera( scene )
{
}


void Camera3D::reset()
{
    Camera::reset();
    
    _frustum = Frustum( 100, _viewport.width*1.0/_viewport.height, 1.0, 30.0 );
}


void Camera3D::setFrustum( const Camera3D::Frustum &frustum )
{
    _frustum = frustum;
}


void Camera3D::applyProjection()
{    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( _frustum.fov, _frustum.aspect, _frustum.zNear, _frustum.zFar );
}



GRAPHICSLAB_NAMESPACE_END

