/**
 * spotLight.hpp
 * 
 * Author   :   Fatih Erol
 * Date     :   08.03.2010
 */

#ifndef GRAPHICSLAB_SPOTLIGHT_HPP
#define GRAPHICSLAB_SPOTLIGHT_HPP

// Base class include
#include "light.hpp"

// Includes
#include "vector.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

/** Light to simulate a spot light */
class SpotLight : public Light
{
public:
    /**
     * Constructor.
     * 
     * @param[in]   scene   Owning scene
     */
    SpotLight( Scene &scene );
    
    /** Destructor */
    virtual ~SpotLight();
    
    virtual void draw( const RenderParameters &renderParameters );
    virtual void apply();
    
    const vec3f &getSpotDirection() const { return _spotDirection; }
    virtual void setSpotDirection( const vec3f &spotDirection );
    virtual void lookAt( const vec3f &target );
    
    const float getSpotExponent() const { return _spotExponent; }
    void setSpotExponent( const float spotExponent );
    
    const short getSpotCutoff() const { return _spotCutoff; }
    virtual void setSpotCutoff( const short spotCutoff );
    
protected:
    vec3f _spotDirection;
    float _spotExponent;
    short _spotCutoff;
    
}; // class SpotLight

GRAPHICSLAB_NAMESPACE_END

#endif  //  GRAPHICSLAB_SPOTLIGHT_HPP





