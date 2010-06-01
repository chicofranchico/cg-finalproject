/**
 * text.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   01.03.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_TEXT_HPP
#define GRAPHICSLAB_TEXT_HPP

// Base class include
#include "drawable.hpp"

// Includes
#include <string>

GRAPHICSLAB_NAMESPACE_BEGIN

/** Class representing text to draw on screen */
class Text : public Drawable
{
public:
    /**
     * Constructor.
     *
     * @param[in]   scene   Scene to which this drawable belongs
     */
    Text( Scene &scene, const char *txt = NULL );
    
    /** Destructor */
    virtual ~Text();
    
    /**
     * Draw the object to the screen.
     *
     * @param[in]   renderParameters    Parameters for drawing
     */
    virtual void draw( const RenderParameters &renderParameters );
    
    
    /**
     * Get the text.
     *
     * @return      Current text
     */
    const std::string &getText() const { return _text; }
    
    /**
     * Set the text.
     *
     * @param[in]   text    Text to set
     */
    virtual void setText( const char *text );
    
    /**
     * Get the width of current text.
     *
     * @return      Width of current text
     */
    virtual float getWidth() const { return _width; }
    
    /**
     * Get the height of current text.
     * Returns a constant value at the time.
     *
     * @return      Height of current text
     */
    virtual float getHeight() const { return _height; }
    
protected:
    /** Text value */
    std::string _text;
    
    /** Width and height of the text */
    float _width, _height;
    
    /** GLUT font */
    void *_font;

    /** Static variable for spacing between characters */
    static const int SPACING;
    
}; // class Text


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_TEXT_HPP


