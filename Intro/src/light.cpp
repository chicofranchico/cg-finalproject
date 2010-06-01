/**
 * light.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   08.03.2010
 *
 * All rights reserved.
 */


// Class declaration include
#include "light.hpp"

// Includes
#include "exception.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

Light::Light( Scene &scene ) :
	Drawable( scene ),
    _id( getLightID() ),
    _on( false ),
    _ambient( Color( 0.0, 0.0, 0.0, 1.0 ) ),
    _position( Point( 0.0, 0.0, 1.0 ) ),
    _constantAttenuation( 1.0 ),
    _linearAttenuation( 0.0 ),
    _quadraticAttenuation( 0.0 )
{
    if ( _id == GL_LIGHT0 )
    {
        _diffuse = Color( 1.0, 1.0, 1.0, 1.0 );
        _specular = Color( 1.0, 1.0, 1.0, 1.0 );
    }
    else
    {
        _diffuse = Color( 0.0, 0.0, 0.0, 1.0 );
        _specular = Color( 0.0, 0.0, 0.0, 1.0 );
    }
    
    
}

Light::~Light()
{
    releaseLightID( _id );
}


void Light::turnOn( bool on )
{
    _on = on;
    if ( on == true )
        glEnable( _id );
    else
        glDisable( _id );
}

bool Light::isOn() const
{
    return ( _on );
}


void Light::apply()
{
    if ( _on )
        glEnable( _id );
    else
        glDisable( _id );
    
    // Position
    glLightfv( _id, GL_POSITION, _position.array );
    
    // Color
    glLightfv( _id, GL_AMBIENT, _ambient.array );
    glLightfv( _id, GL_DIFFUSE, _diffuse.array );
    glLightfv( _id, GL_SPECULAR, _specular.array );
    
    // Attenuation
    glLightf( _id, GL_CONSTANT_ATTENUATION, _constantAttenuation );    
    glLightf( _id, GL_LINEAR_ATTENUATION, _linearAttenuation );    
    glLightf( _id, GL_QUADRATIC_ATTENUATION, _quadraticAttenuation );
    
}


void Light::setPosition( const Point &position ) 
{ 
    _position = position; _position.w = 1.0;
    glLightfv( _id, GL_POSITION, _position.array );
}


void Light::setAmbient( const Color &ambient ) 
{
    _ambient = ambient; 
    glLightfv( _id, GL_AMBIENT, _ambient.array );
}

void Light::setDiffuse( const Color &diffuse )
{ 
    _diffuse = diffuse;
    glLightfv( _id, GL_DIFFUSE, _diffuse.array );    
}

void Light::setSpecular( const Color &specular )
{ 
    _specular = specular;
    glLightfv( _id, GL_SPECULAR, _specular.array );
}

void Light::setConstantAttenuation( const float constantAttenuation )
{ 
    _constantAttenuation = constantAttenuation; 
    glLightf( _id, GL_CONSTANT_ATTENUATION, _constantAttenuation );
}

void Light::setLinearAttenuation( const float linearAttenuation )
{ 
    _linearAttenuation = linearAttenuation;            
    glLightf( _id, GL_LINEAR_ATTENUATION, _linearAttenuation );
}

void Light::setQuadraticAttenuation( const float quadraticAttenuation )
{ 
    _quadraticAttenuation = quadraticAttenuation;
    glLightf( _id, GL_QUADRATIC_ATTENUATION, _quadraticAttenuation );
}


// Static functions 
Light::LightAllocationMap &Light::initLightAllocationMap()
{
    static LightAllocationMap map;
    map[GL_LIGHT0] = map[GL_LIGHT1] = map[GL_LIGHT2] = map[GL_LIGHT3] = map[GL_LIGHT4] = map[GL_LIGHT5] = map[GL_LIGHT6] = map[GL_LIGHT7] = false;
    
    return map;
}
Light::LightAllocationMap &Light::lightAllocationMap = Light::initLightAllocationMap();



GLenum Light::getLightID()
{
    for ( LightAllocationMap::iterator lightIter = lightAllocationMap.begin();
         lightIter != lightAllocationMap.end();
         ++lightIter )
    {
        GLenum light = lightIter->first;
        bool lightAllocated = lightIter->second;
        if ( false == lightAllocated )
        {
            lightAllocationMap[light] = true;
            return light;
        }
    }
    
    throw Exception( "Not enough lights in OpenGL environment" );
}


void Light::releaseLightID( GLenum id )
{
    LightAllocationMap::iterator lightIter = lightAllocationMap.find( id );
    if ( lightIter == lightAllocationMap.end() )
        throw Exception( "Undefined light ID" );
    
    lightIter->second = false;
    glDisable( id );
}

GRAPHICSLAB_NAMESPACE_END

