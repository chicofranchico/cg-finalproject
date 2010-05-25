/**
 * camera3D.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   23.03.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_CAMERA3D_HPP
#define GRAPHICSLAB_CAMERA3D_HPP

// Base class include
#include "camera.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN


/** Class to simulate a 3D camera */
class Camera3D : public Camera
{
public:
    /**
     * Constructor.
     *
     * @param[in]   scene   Owning scene
     */
    Camera3D( Scene &scene );
    
    /** Reset the camera to default values */
    void reset(); 
    
    
    /////////////////////////////////////////////////////
    /** Structure to set up projection transformation */
    struct Frustum
    {
        /** Field of view angle */
        float fov;
        /** Aspect ratio of x to y, to define fov in x direction */ 
        float aspect;
        /** Distance of near clipping plane to camera */
        float zNear;
        /** Distance of far clipping plane to camera */
        float zFar;
        
        /**
         * Constructor.
         *
         * @param[in]   fov     Field of view in y direction in degrees
         * @param[in]   aspect  Aspect ratio of x to y, to idetify fov in x direction
         * @param[in]   zNear   Near clipping plane
         * @param[in]   zFar    Far clipping plane
         */
        Frustum( float fov_ = 90, float aspect_ = 1.0, float zNear_ = 1.0, float zFar_ = 30.0 ) :
            fov( fov_ ), aspect( aspect_ ), zNear( zNear_ ), zFar( zFar_ )
        {
        }
    };

	/**
	 * Get the projection frustum
	 *
	 * @return		Camera frustum
	 */
	const Frustum &getFrustum() const { return _frustum; }
    
    /**
     * Set the projection frustum.
     *
     * @param[in]   frustum     Frustum to set to
     */
    void setFrustum( const Frustum &frustum );
    
    /** Apply projection transformation */
    void applyProjection();
    
    
private:    
    /** Frustum for projection */
    Frustum _frustum;
    
};  // class Camera3D



GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_CAMERA3D_HPP


