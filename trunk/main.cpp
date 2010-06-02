/**
 * main.cpp
 * Main file for the final project of Computer Graphics Lab 2010
 * by JuanPi Carbajl carbajal@ifi.uzh.ch
 */

// Includes for Intro
#include "exception.hpp"
#include "window.hpp"
GRAPHICSLAB_NAMESPACE_USE

// Includes for the Arena
#include "ShootingDemo.h"
#include "GlutStuffs.h"
#include "GLDebugDrawer.h"
#include "btBulletDynamicsCommon.h"
GLDebugDrawer	gDebugDrawer;

// Includes for the End
#include "End.hpp"
extern ParticleContext_t P;

// Signal handler
#include <csignal>
#include <cstdlib>

#include <iostream>

void signalHandler(int signal)
{
    std::cout << "Caught signal " << signal << "... Exiting..." << std::endl;
    exit(0);
}

int main( int argc, char *argv[] )
{

    /*************************
    * INTRO
    **************************/
      // Signal handler
	signal(SIGINT, signalHandler);
    
    try
    {
        Window mainWindow;
        mainWindow.initialize( argc, argv );

        mainWindow.show();
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

    /*************************
    * ARENA
    **************************/
/*
    try
    {

	ShootingDemo* ccdDemo = new ShootingDemo();

	ccdDemo->initPhysics();
	ccdDemo->getDynamicsWorld()->setDebugDrawer(&gDebugDrawer);

	glutmain(argc, argv,640,480,"Shooting Arena Demo",ccdDemo);

	delete ccdDemo;
    }
    catch (char const* msg)
    {
        std::cout<<msg<<std::endl;
    }
  */
    /*************************
    * END
    **************************/
/*
    // Initialize GLUT.
    glutInit(&argc, argv);

    // Make a normal 3D window.
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Particle Example");

    glutDisplayFunc(Draw);
    glutIdleFunc(Draw);
    glutReshapeFunc(Reshape);

    // We want depth buffering, etc.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Make a particle group
    int particle_handle = P.GenParticleGroups(1, 10000);

    P.CurrentGroup(particle_handle);

    try {
        glutMainLoop();
    }
    catch (PError_t &Er) {
        std::cerr << "Particle API exception: " << Er.ErrMsg << std::endl;
        throw Er;
    }

*/
    return 0;
};

