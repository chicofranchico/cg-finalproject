/**
 * camera.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_CAMERA_HPP
#define GRAPHICSLAB_CAMERA_HPP

// Includes
#include "types.hpp"
#include "vector.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

// Forward declarations
class Scene;

/** Scene object to represent a camera for viewing the scene */
class Camera
{
public:
    /**
     * Constructor.
     *
     * @param[in]   scene   Scene to which this drawable belongs
     */
    Camera( Scene &scene );
    
    /** Destructor */
    virtual ~Camera();
    
	// Set up OpenGL matrices

    /** Reset the camera to default values */
    virtual void reset();    

    /////////////////////////////////////////////////////
    /** Structure to set up viewport */
    struct Viewport
    {
        /** Width of the window */
        uint width;
        /** Height of the window */
        uint height;
        
        /**
         * Constructor.
         *
         * @param[in]   width_      Width of the window
         * @param[in]   height_     Height of the window
         */
        Viewport( uint width_ = 800, uint height_ = 600 ) :
            width( width_ ), height( height_ )
        {
        }
    };

	/**
	 * Get the viewport.
	 *
	 * @return		Viewport of the camera
	 */
	const Viewport &getViewport() const { return _viewport; }
    
	/** 
	 * Set window viewport transformation.
	 *
	 * @param[in]	viewport	Viewport structure to set
	 */
    virtual void setViewport( const Viewport &viewport );

	/** Apply viewport transformation */
    virtual void applyViewport();

    
	/** Apply projection transformation */
    virtual void applyProjection() = 0;
    

    /////////////////////////////////////////////////////
	/** Structure to set up a viewing transformation */
	struct LookAtData
	{
		/** Position of the camera */
		Point position;
		/** The point where the camera is looking at */
		Point center;
		/** The up vector for the camera */
		vec3f up;

		/** Default position point */
		static const Point _DEFAULT_POSITION;
		/** Default center point */
		static const Point _DEFAULT_CENTER;
		/** Default up vector */
		static const vec3f _DEFAULT_UP;

		/**
		 * Constructor.
		 *
		 * @param[in]	position_	Position of the camera
		 * @param[in]	center_		Center point where the camera is looking at
		 * @param[in]	up_			Up vector for the camera
		 */
		LookAtData( const Point &position_ = _DEFAULT_POSITION,
					const Point &center_ = _DEFAULT_CENTER,
					const vec3f &up_ = _DEFAULT_UP ) :
			position( position_ ),
			center( center_ ),
			up( up_ )
		{}

		/** Reset the values */
		void reset()
		{
			position = _DEFAULT_POSITION;
			center = _DEFAULT_CENTER;
			up = _DEFAULT_UP;
		}
	};

	/**
	 * Get the camera look at data for viewing transformation.
	 *
	 * @return		Current LookAtData of the computer
	 */
	const LookAtData getLookAtData() const { return _lookAtData; }

	/**
	 * Set the LookAtData of the camera.
	 *
	 * @param[in]	lookAtData		LookAtData to set up 
	 */
	virtual void setLookAtData( const LookAtData &lookAtData );

	/** Apply the viewing transformation. */
	virtual void applyModelview();

	/** LookAtData to specify viewing transformation */
	LookAtData _lookAtData;

protected:
    /** Owning scene for the camera */
    Scene &_scene;

    /** Viewport = Width and height of the screen */
    Viewport _viewport;
    
	
    
}; // class Camera

   

GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_CAMERA_HPP


