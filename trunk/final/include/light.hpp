/**
 * light.hpp
 * 
 * Author   :   Fatih Erol
 * Date     :   08.03.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_LIGHT_HPP
#define GRAPHICSLAB_LIGHT_HPP

// Base class include
#include "drawable.hpp"

// Includes
#include "types.hpp"
#include "opengl_includes.hpp"
#include <map>

GRAPHICSLAB_NAMESPACE_BEGIN

// Forward declarations
class Scene;

/** Base class for an OpenGL light */
class Light : public Drawable
{
public:
	/** 
	 * Constructor.
	 * 
	 * @param[in]	scene	Owning scene
	 */
    Light( Scene &scene );

	/** Destructor */
    virtual ~Light();
    
    
    // This function calls glLight* function for position and direction if existing.
    // As these are kept in eye coordinates, the visualizer may call them after applying transformations.
	/** Apply the OpenGL light */
    virtual void apply();

	/**
	 * Enable/Disable the light.
	 *
	 * @param[in]	on		Enable/Disable light
	 */
    virtual void turnOn(bool on = true);

	/**
	 * Check if the ligth is enabled.
	 *
	 * @return		True if light is enabled, false otherwise
	 */
    virtual bool isOn() const;
    
	
    /**
     * Draw the object to the screen.
     *
     * @param[in]   renderParameters    Parameters for drawing
     */
    virtual void draw( const RenderParameters &renderParameters ) = 0;

    // Get/Setters
    const Point &getPosition() const { return _position; }
    virtual void setPosition( const Point &position );
    
    const Color &getAmbient() const { return _ambient; }
    void setAmbient( const Color &ambient );
    
    const Color &getDiffuse() const { return _diffuse; }
    void setDiffuse( const Color &diffuse );
    
    const Color &getSpecular() const { return _specular; }
    void setSpecular( const Color &specular );
    
    const float getConstantAttenuation() const { return _constantAttenuation; }
    virtual void setConstantAttenuation( const float constantAttenuation );
    
    const float getLinearAttenuation() const { return _linearAttenuation; }
    virtual void setLinearAttenuation( const float linearAttenuation );
    
    const float getQuadraticAttenuation() const { return _quadraticAttenuation; }
    virtual void setQuadraticAttenuation( const float quadraticAttenuation );

	static GLenum getLightID();
    
protected:
	/** OpenGL light ID */
    GLenum _id;
	/** Whether the light is enabled */
    bool _on;

	// Properties of light
    Color _ambient;
    Color _diffuse;
    Color _specular;
    Point _position;
    
    float _constantAttenuation;
    float _linearAttenuation;
    float _quadraticAttenuation;
    
    
protected:
    typedef std::map<GLenum, bool> LightAllocationMap;
    static LightAllocationMap &lightAllocationMap;
    static LightAllocationMap &initLightAllocationMap();
    
    
    
    static void releaseLightID( GLenum id );
    
}; // class Light

GRAPHICSLAB_NAMESPACE_END

#endif  // GRAPHICSLAB_LIGHT_HPP


