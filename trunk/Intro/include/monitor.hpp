/**
 * monitor.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   28.03.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_MONITOR_HPP
#define GRAPHICSLAB_MONITOR_HPP

// Base class include
#include "drawable.hpp"

// Includes
#include "material.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

// Forward declarations
class Texture;

/** Rperesents a TV like monitor where a texture can be displayed */
class Monitor : public Drawable
{
public:
	/** 
	 * Constructor.
	 *
	 * @param[in]	scene	Owning scene
	 */
	Monitor( Scene &scene );
	
    /**
     * Draw the object to the screen.
     *
     * @param[in]   renderParameters    Parameters for drawing
     */
    virtual void draw( const RenderParameters &renderParameters );

	/** 
	 * Set screen to show.
	 *
	 * @param[in]	screenTexture	Texture to display on screen
	 */
	void setScreen( const Texture &texture );

	/**
	 * Set size of the monitor.
	 *
	 * @param[in]	width	Width of the monitor
	 * @param[in]	height	Height of the monitor
	 */
	void setSize( float width, float height );

private:

	/** Size of the monitor */
	float _width, _height;

	/** Current screen texture */
	const Texture *_texture;

	/** Material for monitor geometry */
	Material _material;

}; // class Monitor


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_MONITOR_HPP


