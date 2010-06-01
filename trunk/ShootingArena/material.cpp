/**
 * material.cpp
 * Modified version of Fatih Erol material and color classes
 * By JuanPi Carbajal carbajal@ifi.uzh.ch
 * 05.2010
 */


// Class declaration include
#include "material.hpp"

Material::Material() :
    _ambient( Color( 0.2, 0.2, 0.2, 1.0 ) ),
    _diffuse( Color( 0.8, 0.8, 0.8, 1.0 ) ),
    _specular( Color( 0.0, 0.0, 0.0, 1.0 ) ),
    _emission( Color( 0.0, 0.0, 0.0, 1.0 ) ),
    _shininess( 0 )
{
}

Material::~Material()
{
}

void Material::setActive( GLenum face ) const
{
    glMaterialfv( face, GL_AMBIENT, _ambient.array );
    glMaterialfv( face, GL_DIFFUSE, _diffuse.array );
    glMaterialfv( face, GL_SPECULAR, _specular.array );
    glMaterialfv( face, GL_EMISSION, _emission.array );
    
    glMaterialf( face, GL_SHININESS, _shininess );
}

////////////////////////////////////////////////////////
// Color
////////////////////////////////////////////////////////

const Color &Color::WHITE = Color( 1.0, 1.0, 1.0, 1.0 );
const Color &Color::BLACK = Color( 0.0, 0.0, 0.0, 1.0 );
const Color &Color::GRAY = Color( 0.5, 0.5, 0.5, 1.0 );
const Color &Color::RED = Color( 1.0, 0.0, 0.0, 1.0 );
const Color &Color::GREEN = Color( 0.0, 1.0, 0.0, 1.0 );
const Color &Color::BLUE = Color( 0.0, 0.0, 1.0, 1.0 );
const Color &Color::YELLOW = Color( 1.0, 1.0, 0.0, 1.0 );
const Color &Color::BROWN = Color( 0.545098,0.270588,0.074510);

Color::Color( float r_, float g_, float b_, float a_ ) :
    r( ( array[0] ) ), 
    g( ( array[1] ) ), 
    b( ( array[2] ) ), 
    a( ( array[3] ) )
{
    array[0] = r_; array[1] = g_; array[2] = b_; array[3] = a_;
}

Color::Color( const Color &other ) :
    r( ( array[0] ) ), 
    g( ( array[1] ) ), 
    b( ( array[2] ) ), 
    a( ( array[3] ) )
{
    for ( unsigned int i = 0; i < 4; i ++ )
    {
        array[i] = other.array[i];
    }        
}

Color &Color::operator=( const Color &other )
{
    for ( unsigned int i = 0; i < 4; i ++ )
    {
        array[i] = other.array[i];
    }
    return *this;
}

bool Color::operator==( const Color &other )
{
    return ( 
            ( array[0] == other.array[0] ) &&
            ( array[1] == other.array[1] ) &&
            ( array[2] == other.array[2] ) &&
            ( array[3] == other.array[3] ) );
}

