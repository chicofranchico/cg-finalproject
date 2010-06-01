/**
 * monitor.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   28.03.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "monitor.hpp"


// Includes
#include "texture.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

Monitor::Monitor( Scene &scene ) :
	Drawable( scene ),
	_width( 1.0 ),
	_height( 1.0 ),
	_texture( NULL )
{
	_material.setAmbient( Color( 0.2, 0.8, 0.2 ) );
	_material.setDiffuse( Color( 0.2, 0.8, 0.2 ) );
	_material.setSpecular( Color( 0.2, 0.8, 0.2 ) );
	_material.setShininess( 64 );
}

void Monitor::draw( const RenderParameters &renderParameters )
{
	float depth = 0.1, border = 0.2;
	const Rectangle &rect = _texture->getRectangle();
	
	glDisable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_LIGHTING );
	_material.setActive();
	
		
	glBegin( GL_QUADS );
	glNormal3f( 0.0, 0.0, 1.0 );
	glVertex3f( -_width/2, -_height/2, -depth );
	glVertex3f( _width/2, -_height/2, -depth );	
	glVertex3f( _width/2, _height/2, -depth );	
	glVertex3f( -_width/2, _height/2, -depth );
	glEnd();

	glDisable( GL_LIGHTING );
	_texture->setActive( true );

	glBegin( GL_QUADS );
	glTexCoord2f( 0.0, 0.0 );
	glVertex3f( -_width/2 + border, -_height/2 + border, 0.0 );
	glTexCoord2f( rect.getWidth(), 0.0 );
	glVertex3f( _width/2 - border, -_height/2 + border, 0.0 );
	glTexCoord2f( rect.getWidth(), rect.getHeight() );
	glVertex3f( _width/2 - border, _height/2 - border, 0.0 );
	glTexCoord2f( 0.0, rect.getHeight() );
	glVertex3f( -_width/2 + border, _height/2 - border, 0.0 );
	glEnd();

	_texture->setActive( false );
}

void Monitor::setScreen( const Texture &texture )
{
	_texture = &texture;
}

void Monitor::setSize( float width, float height )
{
	_width = width;
	_height = height;
}

GRAPHICSLAB_NAMESPACE_END

