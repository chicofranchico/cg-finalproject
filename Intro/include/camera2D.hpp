/**
 * camera2D.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   23.03.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_CAMERA2D_HPP
#define GRAPHICSLAB_CAMERA2D_HPP

// Base class include
#include "camera.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

/** Class to simulate a 2D camera with orthogonal viewing volume */
class Camera2D : public Camera
{
public:
    /**
     * Constructor.
     *
     * @param[in]   scene   Owning scene
     */
    Camera2D( Scene &scene );
    
    /** Reset the camera to default values */
    void reset(); 
    
    /** Structure to define an orthogonal view volume */
    struct ViewVolume
    {
        float left, right, bottom, top, zNear, zFar;
        
        /**
         * Constructor.
         * 
         * @param[in]   left_   Left boundary of the view volume
         * @param[in]   right_  Right boundary of the view volume
         * @param[in]   bottom_ Bottom boundary of the view volume
         * @param[in]   top_    Top boundary of the view volume
         * @param[in]   near_   Near boundary of the view volume
         * @param[in]   far_    Far boundary of the view volume
         */
        ViewVolume( float left_ = -10.0, float right_ = 10.0, float bottom_ = -10, float top_ = 10.0, float zNear_ = 0.0, float zFar_ = 10.0 ) :
            left( left_ ), right ( right_ ), bottom( bottom_ ), top( top_ ), zNear( zNear_ ), zFar( zFar_ )
        {
        }
        
    };  // struct ViewVolume
    
    
    /**
     * Set the orthogonal view volume.
     *
     * @param[in]   viewVolume     ViewVolume to set to
     */
    void setViewVolume( const ViewVolume &viewVolume );
    
    /** Apply projection transformation */
    void applyProjection();
    
private:
    ViewVolume _viewVolume;
    
};  // class Camera2D


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_CAMERA2D_HPP


