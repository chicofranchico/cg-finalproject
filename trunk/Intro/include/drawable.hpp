/**
 * drawable.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_DRAWABLE_HPP
#define GRAPHICSLAB_DRAWABLE_HPP

// Includes
#include "types.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

// Forward declarations
class Scene;

/** Abstract base class to provide interface for a drawable object in the scene */
class Drawable
{
public:
    /**
     * Constructor.
     *
     * @param[in]   scene   Scene to which this drawable belongs
     */
    Drawable( Scene &scene ) :
        _scene( scene )
    {
    }
    
    /** Destructor */
    virtual ~Drawable() {}
    
    /**
     * Draw the object to the screen.
     *
     * @param[in]   renderParameters    Parameters for drawing
     */
    virtual void draw( const RenderParameters &renderParameters ) = 0;
    
protected:
    /** Owning scene for the drawable object */
    Scene &_scene;
    
}; // class Drawable


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_DRAWABLE_HPP


