/**
 * camera.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "camera.hpp"

// Includes
#include "opengl_includes.hpp"


GRAPHICSLAB_NAMESPACE_BEGIN



const Point Camera::LookAtData::_DEFAULT_POSITION = Point( 0.0, 0.0, 10.0 );
const Point Camera::LookAtData::_DEFAULT_CENTER = Point( 0.0, 0.0, 0.0 );
const vec3f Camera::LookAtData::_DEFAULT_UP = vec3f( 0.0, 1.0, 0.0 );


Camera::Camera( Scene &scene ) : 
    _scene( scene )
{
}

Camera::~Camera()
{
}

void Camera::reset()
{
	_lookAtData.reset();
}


void Camera::setViewport( const Viewport &viewport )
{
    _viewport = viewport;
}


void Camera::applyViewport()
{
    glViewport( 0, 0, ( GLsizei ) _viewport.width, ( GLsizei ) _viewport.height );
}



void Camera::setLookAtData( const LookAtData &lookAtData )
{
	_lookAtData = lookAtData;
}

void Camera::applyModelview()
{    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt( _lookAtData.position.x, _lookAtData.position.y, _lookAtData.position.z,
               _lookAtData.center.x, _lookAtData.center.y, _lookAtData.center.z,
               _lookAtData.up[0], _lookAtData.up[1], _lookAtData.up[2] );
}


GRAPHICSLAB_NAMESPACE_END

