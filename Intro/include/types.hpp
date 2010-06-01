/**
 * types.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_TYPES_HPP
#define GRAPHICSLAB_TYPES_HPP

// Includes
#include "defs.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN


/** Structure for a 3D point */
struct Point
{
    /** Homogeneous coordinates of the point */
    float &x, &y, &z, &w;   // Reference to array elements for x, y, z, w
    float array[4];         // Actual array to hold the data
    
    /**
     * Constructor.
     * If w is non-zero, the point is equivalent to Euclidean 3D point ( x/w, y/w, z/w ).
     * If w is 0, it is not Euclidean, and usually corresponds to a point in infinity.
     *
     * @param[in]   x_      X coordinate of the point
     * @param[in]   y_      Y coordinate of the point
     * @param[in]   z_      Z coordinate of the point
     * @param[in]   w_      Homogeneous w value
     */     
    Point( float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f, float w_ = 1.0f );
    
	/**
	 * Copy constructor.
	 *
	 * @param[in]	other	Point to copy from
	 */
	Point( const Point &other );
    
    /**
     * Assignment operator.
     *
     * @param[in]   other   Point object to copy values from
     *
     * @return      New Point object with same content as other object
     */
    Point &operator=( const Point &other );
    
    /**
     * Check if two Point objects have the same values
     *
     * @param[in]   other   Point object to compare to
     *
     * @return      True if they have same values, false otherwise
     */
    bool operator==( const Point &other );    
    
};  // struct Point



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
    
};  // struct Color


/** Structure for rectangle */
struct Rectangle
{
    float 
        x1, y1, // x, y coordinates for lower left corner
        x2, y2; // x, y coordinates for upper right corner
    
    /** 
     * Constructor.
     *
     * @param[in]   x1_     x coordinate of lower left corner
     * @param[in]   y1_     y coordinate of lower left corner
     * @param[in]   x2_     x coordinate of upper right corner
     * @param[in]   y2_     y coordinate of upper right corner
     */
    Rectangle( float x1_ = 0.0, float y1_ = 0.0, float x2_ = 0.0, float y2_ = 0.0 );
    
    /**
     * Get width of the rectangle.
     *
     * @return      Width of the rectangle
     */
    float getWidth() const;
    
    /**
     * Get height of the rectangle.
     *
     * @return      Height of the rectangle
     */
    float getHeight() const;

};  // struct Rectangle




/** 
 * Structure for spherical coordinates.
 * xz plane is the reference plane. 
 */
struct SphericalCoordinates
{
	float radius;		// Distance from origin
	float elevation;	// Radial angle between xz plane and the origin-point line
	float azimuth;		// Radial angle around y axis from +z axis

    /**
     * Constructor.
     *
     * @param[in]   radius_     Radius of the sphere
     * @param[in]   elevation_  Elevation angle from xz reference plane
     * @param[in]   azimuth_    Azimuth angle from +z axis
     */
	SphericalCoordinates( float radius_ = 1.0, float elevation_ = 0.0, float azimuth_ = 0.0 );
    
	/**
	 * Get the equivalent cartesian coordinates.
	 * 
	 * @param[out]	point	Cartesian coordinates
	 */
	void getCartesianPoint( Point &point );
    
    /**
     * Set the spherical coordinates from given cartesian coordinates.
     *
     * @param[in]   position    Cartesian coordinate mapping to position on sphere surface
     * @param[in]   origin      Cartesian coordinate mapping to sphere origin
     */
    void set( const Point &position, const Point &origin );
    
};  // struct SphericalCoordinates



/** Structure for parameters for drawing */
struct RenderParameters
{
    /** Whether the polygons should be rendered smoothly or flat by OpenGL */
    bool smoothShading;
    
	/** Whether the polygons should be rendered in wireframe lines, or polygons */
	enum DrawMode
	{
		WIREFRAME,
		POLYGON
	} drawMode;
    
    /** Constructor */
    RenderParameters() :
        smoothShading( true ),
        drawMode( POLYGON )
    {
    }
    
};  // struct RenderParameters


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_TYPES_HPP


