/**
 * stage.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   28.03.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_STAGE_HPP
#define GRAPHICSLAB_STAGE_HPP

// Base class include
#include "drawable.hpp"

// Includes
#include "material.hpp"
#include "text3d.h"
#include "math3d.h"

//TEXTURE STUFF
#include <stdio.h>			// Header File For Standard Input/Output

//TEXTURE STUFF

#include <cstdlib>
#include <ctime>
#include "soundClass.hpp"


GRAPHICSLAB_NAMESPACE_BEGIN

// Forward declarations
class Camera3D;
class PLYModel;
class PositionalLight;
class DirectionalLight;
class SpotLight;

#define GRASS 	0
#define SHRUB 	1
#define TREE 	2
#define TREETOP 3
#define TREE02 	4
#define FENCE 	5
#define RAILS	6
#define MONO	7
#define BUNNY	8

/** Represents a virtual stage of objects to be rendered */
class Stage : public Drawable
{
public:
	/** 
	 * Constructor.
	 *
	 * @param[in]	scene	Owning scene
	 */
	Stage( Scene &scene );
	
	/** Destructor */
	~Stage();

    /**
     * Draw the object to the screen.
     *
     * @param[in]   renderParameters    Parameters for drawing
     */
    void draw( const RenderParameters &renderParameters );

	/** 
	 * Resize viewport.
	 *
	 * @param[in]	width	Width of the viewport
	 * @param[in]	height	Height of the viewport
	 */
	void resize( uint width, uint height );
    
    
    /** Reset data to initial values */
    void reset(); 

public:
	Material _material;

	Camera3D *_camera;

	//Scene Objects
	PLYModel *_monorail;
	PLYModel *_rails;

	PLYModel *_tree;
	PLYModel *_treeTop;

	PLYModel *_shrub1;
	PLYModel *_grass;
	PLYModel *_tree02;

	PLYModel *_fence;

	PLYModel *_bunny;

	//end 3D Objects

	// Storage For textures
	GLuint	texture[8];
	GLuint _objTextures[5];
	//GLuint	_skybox[6]; //not used

	bool listInit;
	bool texInit;
	bool objTex;

	//display lists
	GLuint _lists[9];

	// Sound synthetizer
	StageSoundClass *sounder;

	bool soundInit;

	void setupCubeWorld(void);

	void stopAllSound(void);

	void setupSound(void);

	void startSceneSound(void);

private:
    float l[3], n[3], e[3];

	void loadImage(const char *szFileName, GLuint &texid );

	void initDisplayLists( const RenderParameters &renderParameters );

	void DrawSkyBox(void);

	void loadTextures(void);

	void load3DModels( void );

	GLbyte *gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat);

	void DrawTextSign (void);

	void Draw3DObjects (void);

	void DrawTex3DObjects( void );

	void DrawTextures (void);

	void setupObjectTextures(void);

	void setupShadow(void);

	void Draw3DObjectsShadows(void);

	void glShadowProjection(float * l, float * e, float * n);

    
}; // class Stage


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_STAGE_HPP


