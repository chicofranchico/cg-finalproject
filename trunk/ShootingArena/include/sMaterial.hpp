/**
 * material.hpp
 * Modified version of Fatih Erol material and color classes
 * By JuanPi Carbajal carbajal@ifi.uzh.ch
 * 05.2010
 */


#ifndef S_MATERIAL_HPP
#define S_MATERIAL_HPP

#include "GlutStuffs.h"

/** Structure for RGBA color */
struct Color
{
    /** Red, green, blue and alpha components of the color */
    float &r, &g, &b, &a;   // Reference to array elements for r, g, b, a
    float array[4];         // Actual array to hold data
    
    /**
     * Constructor.
     * A color is represented by its red, green and blue components. The alpha value
     * is usually used for representing transparency, where 1.0 means a totally opaque
     * color and 0.0 means a totally transparent color.
     *
     * @param[in]   r_      Red component of the color
     * @param[in]   g_      Green component of the color
     * @param[in]   b_      Blue component of the color
     * @param[in]   r_      Alpha component of the color
     */
    Color( float r_ = 0.0f, float g_ = 0.0f, float b_ = 0.0f, float a_ = 1.0 );
    
    /** 
     * Copy constructor.
     *
     * @param[in]   other   Color object to copy from
     */
    Color( const Color &other );
    
    /**
     * Assignment operator.
     *
     * @param[in]   other   Color object to copy values from
     *
     * @return      New Color object with same content as other object
     */
    Color &operator=( const Color &other );
    
    /**
     * Check if two Color objects have the same values
     *
     * @param[in]   other   Color object to compare to
     *
     * @return      True if they have same values, false otherwise
     */
    bool operator==( const Color &other );
    
    // Static Color objects to define basic colors
    static const Color &WHITE;
    static const Color &BLACK;
    static const Color &GRAY;
    static const Color &RED;
    static const Color &GREEN;
    static const Color &BLUE;
    static const Color &YELLOW;
    static const Color &BROWN;
};  // struct Color

/** Class to set up surface material */
class sMaterial
{
public:
	/** Constructor */
    sMaterial();
	/** Destructor */
    ~sMaterial();
    
    /**
	 * Set the material as active
	 *
	 * @param[in]	face	Face to apply the material to
	 */
    void setActive( GLenum face = GL_FRONT_AND_BACK ) const;
    
    // Material properties    
    const Color &getAmbient() const             { return _ambient; }
    void setAmbient( const Color &ambient )     { _ambient = ambient; }
    
    const Color &getDiffuse() const             { return _diffuse; }
    void setDiffuse( const Color &diffuse )     { _diffuse = diffuse; }
    
    const Color &getSpecular() const            { return _specular; }
    void setSpecular( const Color &specular )   { _specular = specular; }
    
    const Color &getEmission() const            { return _emission; }
    void setEmission( const Color &emission )   { _emission = emission; }
    
    const float getShininess() const            { return _shininess; }
    void setShininess( const float shininess )  { _shininess = shininess; }
    
private:
	// Properties of the material
    Color _ambient;
    Color _diffuse;
    Color _specular;
    Color _emission;
    float _shininess;
    
}; // class Material


#endif  // S_MATERIAL_HPP



