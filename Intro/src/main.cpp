/**
 * main.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   24.02.2010
 *
 * All rights reserved.
 */

// Includes
#include "exception.hpp"
#include "window.hpp"

#include <iostream>

// Signal handler
#include <csignal>
#include <cstdlib>
void signalHandler(int signal)
{
    std::cout << "Caught signal " << signal << "... Exiting..." << std::endl;
    exit(0);
}


GRAPHICSLAB_NAMESPACE_USE

int main( int argc, char *argv[] )
{
    // Signal handler
	signal(SIGINT, signalHandler);
    
    try
    {
        Window mainWindow;
        mainWindow.initialize( argc, argv );

        mainWindow.show();  // Never returns
    }
    catch ( const Exception &e )
    {
        std::cerr << "Exception : " << e.what() << std::endl;
        return 1;
    }
    catch ( ... )
    {
        std::cerr << "Exception : Unknown exception" << std::endl;
        return 1;
    }

    
    return 0;
};

