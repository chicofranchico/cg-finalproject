/**
 * texture.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   22.03.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "texture.hpp"


GRAPHICSLAB_NAMESPACE_BEGIN

Texture::Texture( GLenum target ) :
	_target( target ),
	_rectangle( Rectangle( 0.0, 0.0, 1.0, 1.0 ) )
{    
    glGenTextures( 1, &_id );
}

Texture::~Texture()
{
    glDeleteTextures( 1, &_id );
}

void Texture::reset()
{
}


void Texture::setActive( bool on ) const
{
    if ( on )
    {
        glEnable( _target );
        glBindTexture( _target, _id );
        glTexParameterf( _target, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameterf( _target, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameterf( _target, GL_TEXTURE_WRAP_S, GL_CLAMP );
		glTexParameterf( _target, GL_TEXTURE_WRAP_T, GL_CLAMP );
    }
    else
    {
        glDisable( _target );
    }
    
}

/////////////////////////////////////////////////////////////////////////
// ImageTexture
/////////////////////////////////////////////////////////////////////////
ImageTexture::ImageTexture() :
    Texture( GL_TEXTURE_RECTANGLE_ARB )
{
}

void ImageTexture::init()
{
}

uchar *ImageTexture::getImage() const
{    
	glBindTexture( _target, _id );
	GLint width, height;
	glGetTexLevelParameteriv( _target, 0, GL_TEXTURE_WIDTH, &width );
	glGetTexLevelParameteriv( _target, 0, GL_TEXTURE_HEIGHT, &height);
	uchar *data = new uchar[height*width*4];
	glGetTexImage( _target, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );

	return data;
}
void ImageTexture::setImage( const uchar *image, uint width, uint height )
{
	_rectangle = Rectangle( 0.0, 0.0, width, height );
	glBindTexture( _target, _id );
    glTexImage2D( _target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );
}
/////////////////////////////////////////////////////////////////////////
// CheckerTexture
/////////////////////////////////////////////////////////////////////////
void CheckerTexture::init()
{    
    reset();
    
    GLint width = 512;
    GLint height = 512;
    uint bytesPerPixel = 4;
    
    uchar *data = new uchar[height*width*bytesPerPixel];
    
    for ( int i = 0; i < height; i++ )
    {
        for ( int j = 0; j < width; j++ )
        {
            uint index = i*width*bytesPerPixel + j*bytesPerPixel;
            uint size = 32;
            bool white = ( ( i % (2*size) ) > size ) && ( ( j % (2*size) ) > size );
            for ( uint k = 0; k < bytesPerPixel; k++ )
            {
                data[index + k] = ( white ? 255 : 0 );
            }
        }
    }
    
    glBindTexture( _target, _id );
    glTexImage2D( _target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );
    
    delete [] data;
}

uchar *CheckerTexture::getImage() const
{    
	glBindTexture( _target, _id );
	GLint width, height;
	glGetTexLevelParameteriv( _target, 0, GL_TEXTURE_WIDTH, &width );
	glGetTexLevelParameteriv( _target, 0, GL_TEXTURE_HEIGHT, &height);
	uchar *data = new uchar[height*width*4];
	glGetTexImage( _target, 0, GL_RGBA, GL_UNSIGNED_BYTE, data );

	return data;
}

GRAPHICSLAB_NAMESPACE_END

