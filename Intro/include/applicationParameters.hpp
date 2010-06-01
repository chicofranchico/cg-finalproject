/**
 * applicationParameters.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   24.02.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_APPLICATIONPARAMETERS_HPP
#define GRAPHICSLAB_APPLICATIONPARAMETERS_HPP

// Includes
#include "defs.hpp"

#include <string>

GRAPHICSLAB_NAMESPACE_BEGIN

/** Class to specify parameters to the application */
class ApplicationParameters
{
public:
    /**
     * Constructor.
     *
     * @param[in]   argc    Number of arguments
     * @param[in]   argv    List of arguments
     */
    ApplicationParameters( int argc = 0, char **argv = NULL );
    
    // Getter functions
    /**
     * Get the width of the window.
     *
     * @return      Width of the window
     */
    uint getWidth() const { return _width; }
    /**
     * Get the height of the window.
     *
     * @return      Height of the window
     */
    uint getHeight() const { return _height; }
    
    /**
     * Get the title of the window.
     *
     * @return      Title of the window
     */
    const std::string &getTitle() const { return _title; }

	/**
	 * Get the model file name.
	 *
	 * @return		File name to load model from
	 */
	const std::string &getModelFileName() const { return _modelFileName; }
    
    /**
     * Parse the arguments to fill out internal member values.
     *
     * @param[in]   argc    Number of arguments
     * @param[in]   argv    List of arguments
     */
    void parseArguments( int argc, char **argv );
    
private:
    /** Width of the window */
    uint _width;
    /** Height of the window */
    uint _height;

	/** Title of the window */
    std::string _title;

	/** File name to load model from */
	std::string _modelFileName;

	// Default values
	/** Default window width */
	static const uint _DEFAULT_WINDOW_WIDTH;
	/** Default window height */
	static const uint _DEFAULT_WINDOW_HEIGHT;

	/** Default window title */
	static const std::string _DEFAULT_WINDOW_TITLE;

        
}; // class ApplicationParameters

GRAPHICSLAB_NAMESPACE_END

#endif  //  GRAPHICSLAB_APPLICATIONPARAMETERS_HPP


