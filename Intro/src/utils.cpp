/**
 * utils.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   05.03.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "utils.hpp"

// Includes
#include "types.hpp"

#include "opengl_includes.hpp"

#include <cmath>

GRAPHICSLAB_NAMESPACE_BEGIN

const float Utils::PI = 3.1416f;

float Utils::length( const vec3f &vec )
{
    return sqrt( vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2] );
}

void Utils::normalize( vec3f &v )
{
    v /= length( v );
}


float Utils::dot( const vec3f &v1, const vec3f &v2 )
{
    return ( v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2] );
}


vec3f Utils::cross( const vec3f &v1, const vec3f &v2 )
{
    vec3f result( v1[1] * v2[2] - v1[2] * v2[1], v1[2] * v2[0] - v1[0] * v2[2], v1[0] * v2[1] - v1[1] * v2[0] );
    return result;
}

vec3f Utils::normal( const Point &p1, const Point &p2, const Point &p3 )
{
    vec3f v1( p2.x - p1.x, p2.y - p1.y, p2.z - p1.z );
    vec3f v2( p3.x - p1.x, p3.y - p1.y, p3.z - p1.z );
    
    vec3f result = cross( v1, v2 );
    normalize( result );
    
    return result;
}

vec3f Utils::normal( const vec3f &p1, const vec3f &p2, const vec3f &p3 )
{
    return normal( Point( p1[0], p1[1], p1[2] ), Point( p2[0], p2[1], p2[2] ), Point( p3[0], p3[1], p3[2] ) );
}

void Utils::rotate( const vec3f &from, const vec3f &to )
{
    float rad = std::acos( dot( from, to ) /( length( from ) * length( to ) ) );
    float deg = ( rad*360 ) / ( 2. * PI );

    vec3f cp = cross( from, to );
    normalize( cp );

    glRotatef( deg, cp[0], cp[1], cp[2] );
}




GRAPHICSLAB_NAMESPACE_END


