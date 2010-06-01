/**
 * mouseEventHandler.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_MOUSEEVENTHANDLER_HPP
#define GRAPHICSLAB_MOUSEEVENTHANDLER_HPP

// Includes
#include "defs.hpp"
#include "opengl_includes.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

// Base structure for mouse events
struct MouseEvent
{
};


// Mouse Events

/** Structure for event when a mouse button is clicked */
struct MousePressEvent : public MouseEvent
{
    /** Enumeration for mouse button */
    enum Button
    {
        BUTTON_LEFT,
        BUTTON_MIDDLE,
        BUTTON_RIGHT
    } button;
    
    /** Button pressed or released */
    bool pressed;
    
    /** Window relative coordinates where the mouse event occured */
    int x, y;

    /** 
     * Constructor.
     *
     * @param[in]   button_     Pressed or released button
     * @param[in]   state_      If button is pressed or released
     * @param[in]   x_          Window relative x coordinate where mouse event occured
     * @param[in]   y_          Window relative y coordinate where mouse event occured
     */     
    MousePressEvent( int button_, int state_, int x_, int y_) :
        MouseEvent(),
        x( x_ ), 
        y( y_ )
    {
        switch ( button_ )
        {
            case GLUT_LEFT_BUTTON:
                button = BUTTON_LEFT;
                break;
            case GLUT_MIDDLE_BUTTON:
                button = BUTTON_MIDDLE;
                break;
            case GLUT_RIGHT_BUTTON:
                button = BUTTON_RIGHT;
                break;
        }
        
        if ( state_ == GLUT_UP )
            pressed = false;
        else
            pressed = true;
    }
};

/** Structure for event when mouse enters the window area */
struct MouseEnterEvent : public MouseEvent
{
};

/** Structure for event when mouse leaves the window area */
struct MouseLeaveEvent : public MouseEvent
{
};

/** Structure for event when mouse moves */
struct MouseMoveEvent : public MouseEvent
{
    /** When no button is pressed, motion is passive */
    bool passive;
    
    /** Window relative coordinates where the mouse event occured */
    int x, y;

    /**
     * Constructor.
     *
     * @param[in]   x_          Window relative x coordinate where mouse event occured
     * @param[in]   y_          Window relative y coordinate where mouse event occured
     * @param[in]   passive_    Whether motion is passive -meaning no button is pressed- or not
     */
    MouseMoveEvent( int x_, int y_, bool passive_ = true ) : 
        MouseEvent(),
        passive( passive_ ),
        x( x_ ),
        y( y_ )
    {}
};


/**
 * Abstract class for providing interface to handle mouse events.
 */
class MouseEventHandler
{
public:
    virtual ~MouseEventHandler() {}
    
    virtual void onEvent( const MousePressEvent &event ) = 0;
    virtual void onEvent( const MouseEnterEvent &event ) = 0;
    virtual void onEvent( const MouseLeaveEvent &event ) = 0;
    virtual void onEvent( const MouseMoveEvent &event ) = 0;
    
}; // class MouseEventHandler

GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_MOUSEEVENTHANDLER_HPP


