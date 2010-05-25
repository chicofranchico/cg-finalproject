/**
 * plyModel.hpp
 * 
 * Author   :   Fatih Erol
 * Date     :   04.03.2010
 *
 * All rights reserved.
 */


#ifndef GRAPHICSLAB_PLYMODEL_HPP
#define GRAPHICSLAB_PLYMODEL_HPP

// Base class include
#include "drawable.hpp"

// Includes
#include "material.hpp"
#include <string>

GRAPHICSLAB_NAMESPACE_BEGIN

// Forward declarations
class PLYData;

/** Class to hold data for a ply model in the screen */
class PLYModel : public Drawable
{
public:
    /**
     * Constructor.
     *
     * @param[in]   scene   Owning scene
     */
    PLYModel( Scene &scene );
    
    /** Destructor */
    virtual ~PLYModel();

    /**
     * Load a model from a file.
     *
     * @param[in]   fname   Name of the file to load ply data from
     */
    virtual void loadModel( const std::string &fname );

    /**
     * Draw the ply model to the screen.
     *
     * @param[in]   renderParameters    Parameters for drawing to the screen
     */
    virtual void draw( const RenderParameters &renderParameters );    
    

	/**
	 * Get ply data.
	 *
	 * @return		PLYData pointer
	 */
	const PLYData *getPLYData() const { return _plyData; }

protected:
    /** PLY data */
    PLYData *_plyData;

    /** Material */
    Material _material;
        
}; // class PLYModel


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_PLYMODEL_HPP


