/**
 * text.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   01.03.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "text.hpp"

// Includes
#include "opengl_includes.hpp"


GRAPHICSLAB_NAMESPACE_BEGIN

const int Text::SPACING = 3;


Text::Text( Scene &scene, const char *text ) : 
    Drawable( scene ),
    _font( GLUT_STROKE_ROMAN )
{
    setText( text );
}

Text::~Text()
{
}

void Text::setText( const char *text )
{
    if ( text == NULL )
        _text = "";
    else
        _text = text;
    
    _width = 0;
    _height = 120;  // Constant value for the moment
    
    // Add up widths of individual characters
    for ( size_t i = 0; i < _text.length(); i++ )
    {
        _width += glutStrokeWidth( _font, _text[i] );
    }
    // Add up spacings between characters
    if ( _text.length() > 0 )
    {
        _width += SPACING * ( _text.length() - 1 );
    }
}

void Text::draw( const RenderParameters &renderParameters )
{
    int cursorX = 0;
    for ( size_t i = 0; i < _text.length(); i++ )
    {
        glutStrokeCharacter( _font, _text[i] );
        cursorX += SPACING + glutStrokeWidth( _font, _text[i] );
    }
}


GRAPHICSLAB_NAMESPACE_END

