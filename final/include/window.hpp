/**
 * window.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_WINDOW_HPP
#define GRAPHICSLAB_WINDOW_HPP

// Includes
#include "defs.hpp"
#include "applicationParameters.hpp"
#include "timer.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

// Forward declarations
class Scene;

/** GLUT window class */
class Window
{
public:
    /** Constructor */
    Window();
    
    /** Destructor */
    virtual ~Window();
    
    /**
     * Initialize the window and GLUT bindings from arguments.
     *
     * @param[in]   argc    Number of arguments
     * @param[in]   argv    List of arguments
     */
    virtual void initialize( int argc, char **argv );
    
    /** Display the window and start handling events */
    virtual void show();

    /** Repaint the window contents */
    virtual void repaint();
    
    /**
     * Check if the window is in full screen mode.
     *
     * @return      True if in full screen mode, false otherwise
     */
    bool getFullscreen() const { return _fullScreen; }
    /**
     * Set the full screen mode on or off.
     *
     * @param[in]   on  Whether full screen mode is to be set on
     */
    virtual void setFullscreen( bool on );
    
    const ApplicationParameters &getApplicationParameters() const { return _applicationParameters; }
    
    // GLUT binding functions
    virtual void displayFunc();
    virtual void reshapeFunc( int width, int height );
    virtual void visibilityFunc( int state );
    virtual void keyboardFunc( unsigned char key);
    virtual void specialFunc( int key );
    virtual void mouseFunc( int button, int state, int x, int y );
    virtual void entryFunc( int state );
    virtual void motionFunc( int x, int y );
    virtual void passiveMotionFunc( int x, int y );
    virtual void idleFunc();
    
    /** Function to clean up and quit application */
    virtual void quit();
    
protected:
    /** Parameters to the application for creating the window */
    ApplicationParameters _applicationParameters;

    /** GLUT window ID */
    int _windowID;

    /** Whether full screen mode is on */
    bool _fullScreen;
    
    /** Scene data which has contents of the screen to display */
    Scene *_scene;
    
    /** Timer to keep track of update rate */
    Timer _timer;
    
}; // class Window


/** Helper singleton class to set the GLUT bindings for Window class */
class WindowBinder
{
public:
    /**
     * Get the singleton instance.
     *
     * @return      Singleton instance reference
     */
    static WindowBinder &getInstance();
    
    /**
     * Set the active window for binding GLUT functions.
     *
     * @param[in, out]  window      Window to bind GLUT functions to
     */
    void setActiveWindow( Window &window )
    {
        _activeWindow = &window;
    }
    
    /**
     * Get the current active window to bind GLUT functions to.
     *
     * @return      Current active window to bind GLUT functions
     */
    Window *getActiveWindow() const { return _activeWindow; }
    
private:
    /** Constructor */
    WindowBinder() :
        _activeWindow( NULL ) 
    {}
    
    /** Destructor */
    ~WindowBinder()
    {
        delete _instance;
        _instance = NULL;
        _activeWindow = NULL;
    }
        
private:
    /** Singleton instance */
    static WindowBinder *_instance;
    
    /** Current active window to bind GLUT functions to */
    Window *_activeWindow;
    
    
}; // class WindowBinder

GRAPHICSLAB_NAMESPACE_END

#endif  //  GRAPHICSLAB_WINDOW_HPP


