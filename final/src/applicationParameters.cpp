/**
 * ApplicationParameters.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   24.02.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "applicationParameters.hpp"

// Includes
#include <cstdlib>
#include <iostream>

GRAPHICSLAB_NAMESPACE_BEGIN

const uint ApplicationParameters::_DEFAULT_WINDOW_WIDTH = 800;
const uint ApplicationParameters::_DEFAULT_WINDOW_HEIGHT = 600;
const std::string ApplicationParameters::_DEFAULT_WINDOW_TITLE = "Graphics Lab FS10";

ApplicationParameters::ApplicationParameters( int argc, char **argv ) : 
    _width( _DEFAULT_WINDOW_WIDTH ),
    _height( _DEFAULT_WINDOW_HEIGHT ),
	_title( _DEFAULT_WINDOW_TITLE ),
	_modelFileName( "" )
{
    parseArguments( argc, argv );
}

void ApplicationParameters::parseArguments( int argc, char **argv )
{
	// Reset values to default first
	_width = _DEFAULT_WINDOW_WIDTH;
    _height = _DEFAULT_WINDOW_HEIGHT;
	_title = _DEFAULT_WINDOW_TITLE;
	_modelFileName = "";

	// Parse arguments
    for ( int argID = 1; argID < argc; )
    {
        std::string arg = argv[argID++];
        if ( arg == "-width" )
        {
            _width = atoi( argv[argID++] );
        }
        else if ( arg == "-height" )
        {
            _height = atoi( argv[argID++] );
        }
        else if ( arg == "-title" )
        {
            _title = argv[argID++];
        }
        else if ( arg == "-model" )
        {
            _modelFileName = argv[argID++];
        }
        else
        {
            std::cerr << "WARNING: Unknown application parameter \"" << arg << "\"" << std::endl;
        }
    }
}


GRAPHICSLAB_NAMESPACE_END

