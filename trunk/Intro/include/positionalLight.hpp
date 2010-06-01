/**
 * positionalLight.hpp
 * 
 * Author   :   Fatih Erol
 * Date     :   08.03.2010
 * 
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_POSITIONALLIGHT_HPP
#define GRAPHICSLAB_POSITIONALLIGHT_HPP

// Base class include
#include "light.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

/** Class for a positional point light source */
class PositionalLight : public Light
{
public:
	/**
	 * Constructor.
	 *
	 * @param[in]	scene	Owning scene
	 */
    PositionalLight( Scene &scene );

	/** Destructor */
    virtual ~PositionalLight();
    
    virtual void draw( const RenderParameters &renderParameters );

}; // class PositionalLight

GRAPHICSLAB_NAMESPACE_END

#endif  //  GRAPHICSLAB_POSITIONALLIGHT_HPP





