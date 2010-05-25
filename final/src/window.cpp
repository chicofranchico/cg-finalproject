/**
 * window.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "window.hpp"

// Includes
#include "opengl_includes.hpp"
#include "exception.hpp"
#include "scene.hpp"

#include <cstdlib>
#include <iostream>

GRAPHICSLAB_NAMESPACE_BEGIN


WindowBinder *WindowBinder::_instance = NULL;
WindowBinder &WindowBinder::getInstance()
{
    if ( _instance == NULL )
    {
        _instance = new WindowBinder();
    }
    return *_instance;
}

//////////////////////////////////////////////////
// Static handler functions
//////////////////////////////////////////////////
static void __displayFunc()
{
    WindowBinder &windowBinder = WindowBinder::getInstance();
    Window *activeWindow = windowBinder.getActiveWindow();
    if ( activeWindow == NULL )
    {
        throw Exception( "Active window hasn't been set on WindowBinder" );
    }
    
    activeWindow->displayFunc();
}

static void __reshapeFunc( int width, int height )
{
    WindowBinder &windowBinder = WindowBinder::getInstance();
    Window *activeWindow = windowBinder.getActiveWindow();
    if ( activeWindow == NULL )
    {
        throw Exception( "Active window hasn't been set on WindowBinder" );
    }
    
    activeWindow->reshapeFunc( width, height );
}

static void __visibilityFunc( int state )
{
    WindowBinder &windowBinder = WindowBinder::getInstance();
    Window *activeWindow = windowBinder.getActiveWindow();
    if ( activeWindow == NULL )
    {
        throw Exception( "Active window hasn't been set on WindowBinder" );
    }
    
    activeWindow->visibilityFunc( state );
}

static void __keyboardFunc( unsigned char key, int x, int y )
{
    WindowBinder &windowBinder = WindowBinder::getInstance();
    Window *activeWindow = windowBinder.getActiveWindow();
    if ( activeWindow == NULL )
    {
        throw Exception( "Active window hasn't been set on WindowBinder" );
    }
    
    activeWindow->keyboardFunc( key );
}

static void __specialFunc( int key, int x, int y )
{
    WindowBinder &windowBinder = WindowBinder::getInstance();
    Window *activeWindow = windowBinder.getActiveWindow();
    if ( activeWindow == NULL )
    {
        throw Exception( "Active window hasn't been set on WindowBinder" );
    }
    
    activeWindow->specialFunc( key );
}

static void __mouseFunc( int button, int state, int x, int y )
{
    WindowBinder &windowBinder = WindowBinder::getInstance();
    Window *activeWindow = windowBinder.getActiveWindow();
    if ( activeWindow == NULL )
    {
        throw Exception( "Active window hasn't been set on WindowBinder" );
    }
    
    activeWindow->mouseFunc( button, state, x, y );
}

static void __entryFunc( int state )
{
    WindowBinder &windowBinder = WindowBinder::getInstance();
    Window *activeWindow = windowBinder.getActiveWindow();
    if ( activeWindow == NULL )
    {
        throw Exception( "Active window hasn't been set on WindowBinder" );
    }
    
    activeWindow->entryFunc( state );
}

static void __motionFunc( int x, int y )
{
    WindowBinder &windowBinder = WindowBinder::getInstance();
    Window *activeWindow = windowBinder.getActiveWindow();
    if ( activeWindow == NULL )
    {
        throw Exception( "Active window hasn't been set on WindowBinder" );
    }
    
    activeWindow->motionFunc( x, y );
}

static void __passiveMotionFunc( int x, int y )
{
    WindowBinder &windowBinder = WindowBinder::getInstance();
    Window *activeWindow = windowBinder.getActiveWindow();
    if ( activeWindow == NULL )
    {
        throw Exception( "Active window hasn't been set on WindowBinder" );
    }
    
    activeWindow->passiveMotionFunc( x, y );
}

static void __idleFunc()
{
    WindowBinder &windowBinder = WindowBinder::getInstance();
    Window *activeWindow = windowBinder.getActiveWindow();
    if ( activeWindow == NULL )
    {
        throw Exception( "Active window hasn't been set on WindowBinder" );
    }
    
    activeWindow->idleFunc();
}



//////////////////////////////////////////////////
// Window class implementation
//////////////////////////////////////////////////
Window::Window() :
    _fullScreen( false ),
    _scene( NULL )
{
}

Window::~Window()
{
    glutDestroyWindow( _windowID );
    
    delete _scene;
}

void Window::quit()
{
    glutDestroyWindow( _windowID );
    delete _scene;
    std::cout << "Exiting..." << std::endl;
    exit( EXIT_SUCCESS );
}

void Window::initialize( int argc, char **argv )
{
    _applicationParameters.parseArguments( argc, argv );
    
    
    // Initialize GLUT
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH ); // | GLUT_ALPHA
    glutInitWindowSize( _applicationParameters.getWidth(), _applicationParameters.getHeight() );
    glutInitWindowPosition( -1, -1 );
	
    // Create GLUT Window
    _windowID = glutCreateWindow( _applicationParameters.getTitle().c_str() );    

    // Bind handlers
    WindowBinder &windowBinder = WindowBinder::getInstance();
    windowBinder.setActiveWindow( *this );
    
    glutDisplayFunc( __displayFunc );
    glutReshapeFunc( __reshapeFunc );
    glutKeyboardFunc( __keyboardFunc );
    glutSpecialFunc( __specialFunc );
    glutMouseFunc( __mouseFunc );
    glutMotionFunc( __motionFunc );
    glutPassiveMotionFunc( __passiveMotionFunc );
    glutVisibilityFunc( __visibilityFunc );
    glutEntryFunc( __entryFunc );
    glutIdleFunc( __idleFunc );
    
    _fullScreen = false;
    _scene = new Scene( *this );
    _scene->initialize();
}

void Window::show()
{   
    // Start GLUT event processing    
    //_timer.start();
    glutMainLoop();
}


void Window::repaint()
{
    glutPostRedisplay();
}

void Window::setFullscreen( bool on )
{
    if ( on == _fullScreen )
        return;
    
    _fullScreen = on;
    if ( _fullScreen )
    {
        glutFullScreen();
    }
    else
    {
        glutReshapeWindow( _applicationParameters.getWidth(), _applicationParameters.getHeight() );
    }
}


void Window::displayFunc()
{
    _scene->draw();
}

void Window::reshapeFunc( int width, int height )
{
    _scene->resize( width, height );
    repaint();
}

void Window::visibilityFunc( int state )
{
    if ( state == GLUT_VISIBLE )
        repaint();
}

void Window::keyboardFunc( unsigned char key )
{   
    switch ( key )
    {            
        case 27: // ESCAPE
            quit();
            break;
        default:
        {
            KeyDownEvent event( key );
            _scene->onEvent( event );
            break;
        }
    }
}

void Window::specialFunc( int key )
{
    switch ( key )
    {
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN:
        case GLUT_KEY_PAGE_UP:
        case GLUT_KEY_PAGE_DOWN:
        case GLUT_KEY_HOME:
        case GLUT_KEY_END:
        case GLUT_KEY_INSERT:            
        default:
        {
            SpecialKeyDownEvent event( key );
            _scene->onEvent( event );
            break;
        }
    }
}

void Window::mouseFunc( int button, int state, int x, int y )
{
    MousePressEvent event( button, state, x, y );
    _scene->onEvent( event );
}

void Window::entryFunc( int state )
{
    if ( state == GLUT_ENTERED )
    {
        MouseEnterEvent event;
        _scene->onEvent( event );
    }
    else if ( state == GLUT_LEFT )
    {
        MouseLeaveEvent event;
        _scene->onEvent( event );
    }
}

void Window::motionFunc( int x, int y )
{
    MouseMoveEvent event( x, y, false );
    _scene->onEvent( event );
}

void Window::passiveMotionFunc( int x, int y )
{    
    MouseMoveEvent event( x, y, true );
    _scene->onEvent( event );
}

void Window::idleFunc()
{
    static const float framesPerSecond = 30.0;
    static const float secondsPerFrame = 1.0/framesPerSecond;
    
    // Guarantee FPS if idle, so that animation runs
    if ( _timer.getSeconds()  >= secondsPerFrame )
    {
        _timer.start();
        repaint();
    }
}



GRAPHICSLAB_NAMESPACE_END



