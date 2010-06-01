/**
 * positionalLight.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   08.03.2010
 *
 * All rights reserved.
 */


#include "positionalLight.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN
    
PositionalLight::PositionalLight( Scene &scene ) : 
    Light( scene )
{
}

PositionalLight::~PositionalLight()
{
}


void PositionalLight::draw( const RenderParameters &renderParameters )
{
	if ( !isOn() )
		return;

    //// EXERCISE 06 : Write code here to draw a representation for the light
    // You can use the following in this file, but need to implement this function
    // for DirectionalLight and SpotLight.
	bool wire = false;

	if ( renderParameters.drawMode == RenderParameters::WIREFRAME )
		wire = true;

	glMatrixMode( GL_MODELVIEW );

	glPushMatrix();
		glDisable( GL_LIGHTING );
		glColor3f( _diffuse.r, _diffuse.g, _diffuse.b );
		glTranslatef( _position.x, _position.y, _position.z );

		if (!wire)
			glutSolidSphere( 0.25, 20, 20 );
		else
			glutWireSphere ( 0.25, 20, 20 );

	glPopMatrix();
}



GRAPHICSLAB_NAMESPACE_END

