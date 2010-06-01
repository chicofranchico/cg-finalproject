/**
 * types.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "types.hpp"

// Includes
#include "utils.hpp"

#include <cmath>


GRAPHICSLAB_NAMESPACE_BEGIN


////////////////////////////////////////////////////////
// Point
////////////////////////////////////////////////////////

Point::Point( float x_, float y_, float z_, float w_ ) :
    x( array[0] ), 
    y( array[1] ), 
    z( array[2] ), 
    w( array[3] )
{
    array[0] = x_; array[1] = y_; array[2] = z_; array[3] = w_;
}

Point::Point( const Point &other ) :
    x( array[0] ), 
    y( array[1] ), 
    z( array[2] ), 
    w( array[3] )
{        
    for ( uint i = 0; i < 4; i ++ )
    {
        array[i] = other.array[i];
    }  
}

Point &Point::operator=( const Point &other )
{
    for ( uint i = 0; i < 4; i ++ )
    {
        array[i] = other.array[i];
    }
    return *this;
}

bool Point::operator==( const Point &other )
{
    return ( 
            ( array[0] == other.array[0] ) &&
            ( array[1] == other.array[1] ) &&
            ( array[2] == other.array[2] ) &&
            ( array[3] == other.array[3] ) );
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
    for ( uint i = 0; i < 4; i ++ )
    {
        array[i] = other.array[i];
    }        
}

Color &Color::operator=( const Color &other )
{
    for ( uint i = 0; i < 4; i ++ )
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

////////////////////////////////////////////////////////
// Rectangle
////////////////////////////////////////////////////////

Rectangle::Rectangle( float x1_, float y1_, float x2_, float y2_ ) :
    x1( x1_ ), 
    y1( y1_ ), 
    x2( x2_ ), 
    y2( y2_ )
{
}

float Rectangle::getWidth() const
{
    return fabs( x2 - x1 );
}

float Rectangle::getHeight() const
{
    return fabs( y2 - y1 );
}



////////////////////////////////////////////////////////
// SphericalCoordinates
////////////////////////////////////////////////////////

SphericalCoordinates::SphericalCoordinates( float radius_, float elevation_, float azimuth_ ) :
    radius( radius_ ), 
    elevation( elevation_ ), 
    azimuth( azimuth_ )
{
}

void SphericalCoordinates::getCartesianPoint( Point &point )
{
	point.x = radius*cos( elevation )*sin( azimuth );
    point.y = radius*sin( elevation );
	point.z = radius*cos( elevation )*cos( azimuth );	
	point.w = 1.0;
}

void SphericalCoordinates::set( const Point &position, const Point &origin )
{
    vec3f ray( position.x - origin.x, position.y - origin.y, position.z - origin.z );
    radius = Utils::length( ray );
    elevation = asin( ray[1]/radius );
    azimuth = asin( ray[0]/( radius*cos( elevation ) ) );
}


GRAPHICSLAB_NAMESPACE_END

