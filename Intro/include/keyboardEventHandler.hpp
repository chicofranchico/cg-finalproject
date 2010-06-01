/**
 * keyboardEventHandler.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   25.02.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_KEYBOARDEVENTHANDLER_HPP
#define GRAPHICSLAB_KEYBOARDEVENTHANDLER_HPP

// Includes
#include "defs.hpp"
#include "opengl_includes.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

/**
 * Base class for keyboard events.
 * It contains the state of modifier keys SHIFT, ALT, CTRL, 
 * which is a common member for all the derived real keyboard events
 */
struct KeyEvent
{
    /** Bit vector to specify which modifier keys are pressed */
    uchar modifiers;

    /** Static constant values for modifer keys */
    static const uchar MODIFIER_SHIFT = 1;
    static const uchar MODIFIER_ALT = 1 << 1;
    static const uchar MODIFIER_CTRL = 1 << 2;

    /**
     * Update the status of modifier keys from current glut state.
     */
    void updateModifiers()
    {   
        int m = glutGetModifiers();
        if ( m & GLUT_ACTIVE_SHIFT )
            modifiers |= MODIFIER_SHIFT;
        if ( m & GLUT_ACTIVE_ALT )
            modifiers |= MODIFIER_ALT;
        if ( m & GLUT_ACTIVE_CTRL )
            modifiers |= MODIFIER_CTRL;        
    }
    
    /** Constructor */
    KeyEvent() : modifiers( 0 ) 
    {
        // Modifier keys are updated on construction
        updateModifiers();
    }
};


// Keyboard events

/** Structure for event when an ASCII key is pressed */
struct KeyDownEvent : public KeyEvent
{
    /** Pressed ASCII character, including escape, backspace and delete */
    uchar key;
    /**
     * Constructor.
     *
     * @param[in]   key_     Pressed ASCII character
     */
    KeyDownEvent( uchar key_ ) : 
        KeyEvent(),
        key( key_ ) 
    {}
};

/** Structure for event when a special key, one of function keys or arrow keys, is pressed */
struct SpecialKeyDownEvent : public KeyEvent
{
    /** Pressed special key */
    int key;
    
    /**
     * Constructor.
     *
     * @param[in]   key_    Pressed special key
     */
    SpecialKeyDownEvent( int key_ ) : 
        KeyEvent(),
        key( key_ ) 
    {}
};


/**
 * Abstract keyboard event handler class to provide interface
 * for handling keyboard events
 */
class KeyboardEventHandler
{
public:
    virtual ~KeyboardEventHandler() {}
    
    virtual void onEvent( const KeyDownEvent &event ) = 0;
    virtual void onEvent( const SpecialKeyDownEvent &event ) = 0;
    
}; // class KeyboardEventHandler


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_KEYBOARDEVENTHANDLER_HPP


