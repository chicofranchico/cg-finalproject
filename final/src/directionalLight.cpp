/**
 * directionalLight.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   08.03.2010
 *
 * All rights reserved.
 */


// Class declaration include
#include "directionalLight.hpp"

// Includes
#include "utils.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

DirectionalLight::DirectionalLight( Scene &scene ) : Light( scene )
{
}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::setPosition( const Point &position ) 
{ 
    _position = position; _position.w = 0.0;
    glLightfv( _id, GL_POSITION, _position.array );
}

void DirectionalLight::setConstantAttenuation( const float constantAttenuation )
{ 
    _constantAttenuation = 1.0; 
    glLightf( _id, GL_CONSTANT_ATTENUATION, _constantAttenuation );
}

void DirectionalLight::setLinearAttenuation( const float linearAttenuation )
{ 
    _linearAttenuation = 0.0;            
    glLightf( _id, GL_LINEAR_ATTENUATION, _linearAttenuation );
}

void DirectionalLight::setQuadraticAttenuation( const float quadraticAttenuation )
{ 
    _quadraticAttenuation = 0.0;
    glLightf( _id, GL_QUADRATIC_ATTENUATION, _quadraticAttenuation );
}

//void DirectionalLight::draw( const RenderParameters &renderParameters )
//{    
//    //// EXERCISE 06 : Write code here to draw a representation for the light
//
//	GLUquadricObj* cyl;
//	cyl = gluNewQuadric();
//	
//	bool wire = false;
//
//	if ( renderParameters.drawMode == RenderParameters::WIREFRAME )
//		wire = true;
//
//	glMatrixMode( GL_MODELVIEW );
//
//	glPushMatrix();
//		glDisable( GL_LIGHTING );
//		glColor3f( _diffuse.r, _diffuse.g, _diffuse.b );
//		glTranslatef( _position.x, _position.y, _position.z );
//
//		if (!wire)
//			gluQuadricDrawStyle(cyl, GLU_SMOOTH);
//		else
//			gluQuadricDrawStyle(cyl, GLU_LINE);
//
//		//height is the podium width, and I have to translate back by half of this width
//		//change the positional position of the sphere to 0 in z
//		gluCylinder(cyl,0.1,0.1,5.25,20,20);
//
//	glPopMatrix();
//
//
//}

void DirectionalLight::draw( const RenderParameters &renderParameters )
{
    if ( !isOn() )
        return;

	bool wire = false;

	if ( renderParameters.drawMode == RenderParameters::WIREFRAME )
		wire = true;
    
    glDisable( GL_LIGHTING );
    
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
		glColor3f( _diffuse.r, _diffuse.g, _diffuse.b );

	    glTranslatef( _position.x, _position.y, _position.z );

		vec3f pos ( _position.x, _position.y, _position.z );
	    float length = Utils::length( pos );

	    
	    glLineWidth( 2.5 );

	    glBegin( GL_LINES );
	    	glVertex3f( 0.0, 0.0, 0.0 );
	    	glVertex3f( _position.x/length, _position.y/length, _position.z/length );
	    glEnd();

	    glLineWidth( 1 );
    glPopMatrix();
    
}


GRAPHICSLAB_NAMESPACE_END


