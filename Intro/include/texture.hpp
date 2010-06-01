/**
 * texture.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   22.03.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_TEXTURE_HPP
#define GRAPHICSLAB_TEXTURE_HPP

// Includes
#include "defs.hpp"
#include "types.hpp"
#include "opengl_includes.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN


/** Texture to load from an image */
class Texture
{
public:
    /** Constructor */
    Texture( GLenum target = GL_TEXTURE_2D );
    
    /** Destructor */
    virtual ~Texture();

    /** Reset data */
    virtual void reset();
    
    /** Initialize texture data */
    virtual void init() = 0;

	/** 
	 * Get image data for the texture.
	 *
	 * @return	Image data array in RGBA format with uchar for each component
	 */
	virtual uchar *getImage() const = 0;

    
    /** 
     * Set the texture as current active texture.
     * One has to activate this to true before using the texture,
     * and then deactivate it after usage.
     *
     * @param[in]   on      Whether to turn on or off
     */
    virtual void setActive( bool on = true ) const;
    
	/**
	 * Get the texture rectangular area.
	 *
	 * @return	Current rectangular texture area
	 */
	const Rectangle &getRectangle() const { return _rectangle; }

protected:
    /** Texture ID */
    GLuint _id;
    
	/** Texture target */
	GLenum _target;

	/** Rectangular area of the screen */
	Rectangle _rectangle;

}; // class Texture


class ImageTexture : public Texture
{
public:
    ImageTexture();
	void init();
	uchar *getImage() const;

	/**
	 * Set texture image.
	 *
	 * @param[in]	image	Image data
	 * @param[in]	width	Image width
	 * @param[in]	height	Image height
	 */
	virtual void setImage( const uchar *image, uint width, uint height );

};	// class ImageTexture

/** A sample teture to produce checker effect */
class CheckerTexture : public Texture
{
public:
    void init();
	uchar *getImage() const;
    
};  // class CheckerTexture


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_TEXTURE_HPP


