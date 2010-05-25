/**
 * spotLight.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   08.03.2010
 *
 * All rights reserved.
 */


#include "spotLight.hpp"

#include "utils.hpp"
#include "material.hpp"

#include <cmath>

GRAPHICSLAB_NAMESPACE_BEGIN

SpotLight::SpotLight( Scene &scene ) : 
Light( scene ), 
_spotDirection( vec3f( 0, 0, -1 ) ), 
_spotExponent( 0 ),
_spotCutoff( 180 )
{     
}

SpotLight::~SpotLight()
{
}


void SpotLight::apply()
{
    Light::apply();

	glLightfv( _id, GL_SPOT_DIRECTION, _spotDirection.array() );
    glLightf( _id, GL_SPOT_EXPONENT, _spotExponent );
    glLightf( _id, GL_SPOT_CUTOFF, _spotCutoff );
}

void SpotLight::setSpotDirection( const vec3f &spotDirection )
{ 
    _spotDirection = spotDirection; 
    Utils::normalize( _spotDirection );
    float spotDirectionArr[4] = { _spotDirection[0], _spotDirection[1], _spotDirection[2], 1.0 };
    glLightfv( _id, GL_SPOT_DIRECTION, spotDirectionArr );
}

void SpotLight::lookAt( const vec3f &target )
{
    vec3f direction( target[0] - _position.x, target[1] - _position.y, target[2] - _position.z );
    setSpotDirection( direction );
}

void SpotLight::setSpotExponent( const float spotExponent )
{ 
    _spotExponent = spotExponent; 
    glLightf( _id, GL_SPOT_EXPONENT, _spotExponent );
}

void SpotLight::setSpotCutoff( const short spotCutoff )
{ 
    _spotCutoff = spotCutoff; 
    glLightf( _id, GL_SPOT_CUTOFF, _spotCutoff );
}

void SpotLight::draw( const RenderParameters &renderParameters )
{
    if ( !isOn() )
        return;

    glDisable( GL_LIGHTING );

	bool wire = false;

	if ( renderParameters.drawMode == RenderParameters::WIREFRAME )
		wire = true;

    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
		glColor3f( _diffuse.r, _diffuse.g, _diffuse.b );
		glTranslatef ( _position.x, _position.y, _position.z );
	    
	    Utils::rotate( vec3f( 0, 0, -1 ), _spotDirection );
	    
	    float height = 0.5;
	    float spotAngle = _spotCutoff*( 2*Utils::PI ) / 360 ;
	    float base = std::tan( spotAngle ) * height;

		if (!wire)
			glutSolidCone( base, height, 20, 20);
		else
			glutWireCone( base, height, 20, 20);
	    
    glPopMatrix();
    
}


GRAPHICSLAB_NAMESPACE_END

