/**
 * utils.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   05.03.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_UTILS_HPP
#define GRAPHICSLAB_UTILS_HPP

// Includes
#include "defs.hpp"
#include "vector.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

// Forward declarations
struct Point;


/**
 * Static class for some utility functions
 */
class Utils
{
public:
    
    /** PI number */
    static const float PI;
    
    /**
     * Get the length of a vector.
     *
     * @param[in]   v     Vector to calculate the length of
     *
     * @return      Length of the given vector
     */
    static float length( const vec3f &v );
    
    /**
     * Normalize the given vector to size 1.0.
     *
     * @param[in]   v   Vector to normalize
     */
    static void normalize( vec3f &v );
    
    
    /**
     * Calculate the dot product of two vectors.
     *
     * @param[in]   v1      First vector
     * @param[in]   v2      Second vector
     *
     * @return      Dot product vector of two vectors
     */
    static float dot( const vec3f &v1, const vec3f &v2 );
    
    
    /**
     * Calculate the cross product of two vectors.
     *
     * @param[in]   v1      First vector
     * @param[in]   v2      Second vector
     *
     * @return      Cross product vector of two vectors
     */
    static vec3f cross( const vec3f &v1, const vec3f &v2 );
    
    /**
     * Calculate the normal of a triangle with given three points.
     *
     * @param[in]   p1      First vertex of the triangle
     * @param[in]   p2      Second vertex of the triangle
     * @param[in]   p3      Third vertex of the triangle
     *
     * @return      Normal of the triangle
     */
    static vec3f normal( const Point &p1, const Point &p2, const Point &p3 );
    
    
    /**
     * Calculate the normal of a triangle with given three points.
     *
     * @param[in]   v1      First vertex of the triangle
     * @param[in]   v2      Second vertex of the triangle
     * @param[in]   v3      Third vertex of the triangle
     *
     * @return      Normal of the triangle
     */
    static vec3f normal( const vec3f &p1, const vec3f &p2, const vec3f &p3 );

	static void rotate( const vec3f &from, const vec3f &to );

	//static GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);
    
        
}; // class Utils


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_UTILS_HPP


