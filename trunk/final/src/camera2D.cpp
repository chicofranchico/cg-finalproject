/**
 * camera2D.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   23.03.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "camera2D.hpp"

// Includes
#include "opengl_includes.hpp"


GRAPHICSLAB_NAMESPACE_BEGIN


Camera2D::Camera2D( Scene &scene ) :
    Camera( scene )
{
}

void Camera2D::reset()
{
    Camera::reset();
    
    _viewVolume = ViewVolume( -10.0, 10.0, -10.0, 10.0, 0.0, 10.0 );
}

void Camera2D::setViewVolume( const Camera2D::ViewVolume &viewVolume )
{
    _viewVolume = viewVolume;
}

void Camera2D::applyProjection()
{    
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( _viewVolume.left, _viewVolume.right, _viewVolume.bottom, _viewVolume.top, _viewVolume.zNear, _viewVolume.zFar );
}

GRAPHICSLAB_NAMESPACE_END

