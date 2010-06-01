/**
 * stage.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   28.03.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "stage.hpp"

// Includes
#include "opengl_includes.hpp"
#include "camera3D.hpp"
#include "plyData.hpp"
#include "plyModel.hpp"
#include "scene.hpp"
#include "window.hpp"
#include "positionalLight.hpp"
#include "directionalLight.hpp"
#include "spotLight.hpp"
#include "utils.hpp"

#include <cmath>
#include <iostream>
#include <fstream>

GRAPHICSLAB_NAMESPACE_BEGIN

Stage::Stage( Scene &scene ) :
	Drawable( scene )
{

	const Camera::Viewport &viewport = scene.getViewport();
	_camera = new Camera3D( scene );
	_camera->setViewport( viewport );
	_camera->setFrustum( Camera3D::Frustum( 90, viewport.width*1.0/viewport.height, 1.0, 30.0 ) );
	_camera->setLookAtData( Camera::LookAtData( Point( 0.0, 0.0, 10.0 ), Point( 0.0, 0.0, 0.0 ), vec3f( 0.0, 1.0, 0.0 ) ) );

	std::cout << "Loading 3D Models..." << std::endl;
	load3DModels(  );
	//std::cout << "Done!" << std::endl;

	//glDisable(GL_LIGHTING);

	//display lists
	listInit = false;

	//loaded textures
	texInit = false;
	objTex 	= false;

	l[0] = 10.0; l[1] = 40.0; l[2] = 10; // Coordinates of the light source
	n[0] = 0.0; n[1] = -1.0; n[2] = 0.0; // Normal vector for the plane
    e[0] = 0.0; e[1] = 0.0; e[2] = 0.0; // Point of the plane

    //initialize text 3d api
    t3dInit();

    //soundInit = false;

    sounder = new StageSoundClass();

    soundInit = true;

}

Stage::~Stage()
{
	/*delete _positionalLight;
	delete _directionalLight;
	delete _spotLight;*/

	delete _camera;
	
	delete _monorail;
	delete _rails;

	delete _tree;
	delete _treeTop;

	delete _shrub1;
	delete _grass;
	delete _tree02;

	delete _fence;

	delete _bunny;

	sounder->deleteData();

	delete sounder;

	glDeleteTextures(8, texture);
	glDeleteTextures(5, _objTextures);

	glDeleteLists(_lists[0], 9);

}

/*
 * Should only be called after the object was destroyed by stopAllSound
 */
void Stage::setupSound( )
{

	sounder = new StageSoundClass();

}

void Stage::startSceneSound( )
{

	sounder->playSound(START);

	sounder->playSound(WALK);
}

void Stage::stopAllSound( )
{
	sounder->deleteData();

	delete sounder;
}

void Stage::resize( uint width, uint height )
{
	_camera->setViewport( Camera::Viewport( width, height ) );
	_camera->setFrustum( Camera3D::Frustum( 90, width*1.0/height, 1.0, 30.0 ) );
}

void Stage::reset()
{

	_camera->_lookAtData.center = Point( 0.0, 0.0, 0.0 );
	_camera->_lookAtData.position = Point( 0.0, 0.0, 10.0 );

}

void Stage::load3DModels()
{

	const std::string &rails 	= "../models/rails.ply";
	const std::string &monorail = "../models/monorail.ply";

	const std::string &tree  	= "../models/trunk.ply";
	const std::string &treeTop  = "../models/treeTop.ply";
	const std::string &shrub1   = "../models/calathea.ply";

	const std::string &grass    = "../models/grass.ply";
	const std::string &tree02   = "../models/tree02.ply";

	const std::string &fence 	= "../models/fence.ply";

	const std::string &bunny 	= "../models/bunny.ply";

	_monorail = new PLYModel( _scene );
	_monorail->loadModel( monorail );

	_rails = new PLYModel ( _scene );
	_rails->loadModel( rails );

	_tree = new PLYModel( _scene );
	_tree->loadModel( tree );

	_treeTop = new PLYModel( _scene );
	_treeTop->loadModel( treeTop );

	_shrub1 = new PLYModel( _scene );
	_shrub1->loadModel( shrub1 );

	_grass = new PLYModel ( _scene );
	_grass->loadModel( grass );

	_tree02 = new PLYModel ( _scene );
	_tree02->loadModel( tree02 );

	_fence = new PLYModel ( _scene );
	_fence->loadModel( fence );

	_bunny = new PLYModel(_scene);
	_bunny->loadModel(bunny);

}

void Stage::loadTextures()
{

	loadImage( "../tex/NewPlank.tga", texture[0] );

	loadImage( "../tex/brick1.tga", texture[1] );

	loadImage( "../tex/wornwood.tga", texture[2] );

	loadImage( "../tex/sky.tga", texture[3] );

	loadImage( "../tex/floor.tga", texture[4] );

	loadImage( "../tex/oldroof.tga", texture[5] );

	loadImage( "../tex/plank01.tga", texture[6] );

	loadImage( "../tex/Soupcan.tga", texture[7] );

	texInit = true;

}

void Stage::initDisplayLists( const RenderParameters &renderParameters )
{

	int dlID = glGenLists( 9 );

	_lists[0] = dlID;

	//grass display list
	glNewList( _lists[0], GL_COMPILE );
		_grass->draw( renderParameters );
	glEndList();

	_lists[1] = dlID + 1;

	//shrub display list
	glNewList( _lists[1], GL_COMPILE );
		_shrub1->draw( renderParameters );
	glEndList();

	_lists[2] = dlID + 2;

	//tree display list
	glNewList( _lists[2], GL_COMPILE );
		_tree->draw( renderParameters );
	glEndList();

	_lists[3] = dlID + 3;

	//tree display list
	glNewList( _lists[3], GL_COMPILE );
		_treeTop->draw(renderParameters);
	glEndList();

	_lists[4] = dlID + 4;

	//tree display list
	glNewList( _lists[4], GL_COMPILE );
		_tree02->draw(renderParameters);
	glEndList();

	_lists[5] = dlID + 5;

	//fence display list
	glNewList( _lists[5], GL_COMPILE );
		_fence->draw(renderParameters);
	glEndList();

	_lists[6] = dlID + 6;
	glNewList( _lists[6], GL_COMPILE );
		_rails->draw(renderParameters);
	glEndList();

	_lists[7] = dlID + 7;
	glNewList( _lists[7], GL_COMPILE );
		_monorail->draw(renderParameters);
	glEndList();
	
	_lists[8] = dlID + 8;
	glNewList( _lists[8], GL_COMPILE );
		_bunny->draw(renderParameters);
	glEndList();


	listInit = true;

}

// Creates Texture From A TGA File
void Stage::loadImage(const char *szFileName, GLuint &texid )
{

	glGenTextures(1, &texid);

	glBindTexture(GL_TEXTURE_2D, texid);

	//filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Mag Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;

    pBytes = gltLoadTGA(szFileName, &iWidth, &iHeight, &iComponents, &eFormat);    
    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
    free(pBytes);

}

#pragma pack(1)
typedef struct
{
    GLbyte	identsize;              // Size of ID field that follows header (0)
    GLbyte	colorMapType;           // 0 = None, 1 = paletted
    GLbyte	imageType;              // 0 = none, 1 = indexed, 2 = rgb, 3 = grey, +8=rle
    unsigned short	colorMapStart;          // First colour map entry
    unsigned short	colorMapLength;         // Number of colors
    unsigned char 	colorMapBits;   // bits per palette entry
    unsigned short	xstart;                 // image x origin
    unsigned short	ystart;                 // image y origin
    unsigned short	width;                  // width in pixels
    unsigned short	height;                 // height in pixels
    GLbyte	bits;                   // bits per pixel (8 16, 24, 32)
    GLbyte	descriptor;             // image descriptor
} TGAHEADER;
#pragma pack(8)

// Creates Texture From A TGA File
GLbyte* Stage::gltLoadTGA(const char *szFileName, GLint *iWidth, GLint *iHeight, GLint *iComponents, GLenum *eFormat)
{

    FILE *pFile;			// File pointer
    TGAHEADER tgaHeader;		// TGA file header
    unsigned long lImageSize;		// Size in bytes of image
    short sDepth;			// Pixel depth;
    GLbyte	*pBits = NULL;          // Pointer to bits
    
    // Default/Failed values
    *iWidth = 0;
    *iHeight = 0;
    *eFormat = GL_BGR_EXT;
    *iComponents = GL_RGB8;
    
    // Attempt to open the file
	//fopen_s(&pFile, szFileName, "rb");
	pFile = fopen(szFileName, "rb");
    if(pFile == NULL)
        return NULL;
	
    // Read in header (binary)
    fread(&tgaHeader, 18/* sizeof(TGAHEADER)*/, 1, pFile);
    
    // Do byte swap for big vs little endian
#ifdef __APPLE__
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapStart);
    LITTLE_ENDIAN_WORD(&tgaHeader.colorMapLength);
    LITTLE_ENDIAN_WORD(&tgaHeader.xstart);
    LITTLE_ENDIAN_WORD(&tgaHeader.ystart);
    LITTLE_ENDIAN_WORD(&tgaHeader.width);
    LITTLE_ENDIAN_WORD(&tgaHeader.height);
#endif
	
	
    // Get width, height, and depth of texture
    *iWidth = tgaHeader.width;
    *iHeight = tgaHeader.height;
    sDepth = tgaHeader.bits / 8;
    
    // Put some validity checks here. Very simply, I only understand
    // or care about 8, 24, or 32 bit targa's.
    if(tgaHeader.bits != 8 && tgaHeader.bits != 24 && tgaHeader.bits != 32)
        return NULL;
	
    // Calculate size of image buffer
    lImageSize = tgaHeader.width * tgaHeader.height * sDepth;
    
    // Allocate memory and check for success
    pBits = (GLbyte*)malloc(lImageSize * sizeof(GLbyte));
    if(pBits == NULL)
        return NULL;
    
    // Read in the bits
    // Check for read error. This should catch RLE or other 
    // weird formats that I don't want to recognize
    if(fread(pBits, lImageSize, 1, pFile) != 1)
		{
        free(pBits);
        return NULL;
		}
    
    // Set OpenGL format expected
    switch(sDepth)
		{
        case 3:     // Most likely case
            *eFormat = GL_BGR_EXT;
            *iComponents = GL_RGB8;
            break;
        case 4:
            *eFormat = GL_BGRA_EXT;
            *iComponents = GL_RGBA8;
            break;
        case 1:
            *eFormat = GL_LUMINANCE;
            *iComponents = GL_LUMINANCE8;
            break;
		};
	
    
    // Done with File
    fclose(pFile);
	
    // Return pointer to image data
    return pBits;
}

/**
* http://developer.nvidia.com/object/cube_map_ogl_tutorial.html
* http://www.informit.com/articles/article.aspx?p=770639&seqNum=4
* 
**/
void Stage::setupCubeWorld(  )
{

	const char *szCubeFaces[6] = { "../skybox/pos_x.tga", "../skybox/neg_x.tga", 
	"../skybox/pos_y.tga", "../skybox/neg_y.tga", "../skybox/pos_z.tga", 
	"../skybox/neg_z.tga" };

	GLenum  cube[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                     GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                     GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                     GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                     GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                     GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;
    int i;
       
    // Cull backs of polygons
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
        
    // Set up texture maps        
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);        
  
    // Load Cube Map images
    for(i = 0; i < 6; i++)
    {        
        // Load this texture map
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);
        pBytes = gltLoadTGA(szCubeFaces[i], &iWidth, &iHeight, &iComponents, &eFormat);
        glTexImage2D(cube[i], 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
        free(pBytes);
    }
        
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    
    // Enable cube mapping, and set texture environment to decal
    glEnable(GL_TEXTURE_CUBE_MAP);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
}

/**
* http://www.starstonesoftware.com/OpenGL/
*
* The main draw function
*/
void Stage::draw( const RenderParameters &renderParameters )
{

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//no lighting effect on the cube map
	glDisable(GL_LIGHTING);

	// Sky Box is manually textured
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);
    DrawSkyBox();

	//renormalize stuff
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	//disable cube map for drawing other textures
	glDisable(GL_TEXTURE_CUBE_MAP_EXT);

	//draw the sign with sweet 3d text
	DrawTextSign();

	//if the display lists are not initialized, do it
	if ( !listInit )
	{
		std::cout << "Initializing Display lists" << std::endl;
		initDisplayLists( renderParameters );
		std::cout << "Done!" << std::endl;
	}

	//if the objects' textures haven't been loaded
	if ( !objTex )
	{
		//setup 3D object textures
		setupObjectTextures();
	}
	else
	{
		//no need to load the files again so just enable texturing
		//this was giving a HUUUUUUUGE memory leak of like 100MB per second
		glEnable(GL_TEXTURE_2D);
	}

	//draw objects with textures
	DrawTex3DObjects( );

	glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);

	glDisable( GL_LIGHTING );

	/////////////////
	// shadow part //
	/////////////////

	//enable stuff for shadows
	setupShadow( );

	//draw scene textures, not world
	DrawTextures( );

	//draw the fences and shruberries shadows on the ground
	Draw3DObjectsShadows( );

	//draw the other scene 3D objects with display lists
	Draw3DObjects( );

	//enable world textures again
	glEnable(GL_TEXTURE_CUBE_MAP_EXT);


}

void Stage::Draw3DObjectsShadows( )
{

	//shearing: http://www.j3d.org/matrix_faq/matrfaq_latest.html#Q43

	glMatrixMode(GL_MODELVIEW);

	float m[] = { 1, 0, 0, 0, 
				  0, 1, 0, 0,
				  -1, 0, 1, 0,
				  0, 0, 0, 1 };

	glMultMatrixf(m);

	//blend effect for transparency in the floor
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	float posx = -22.0;

	//fences shadowws
	for ( int i = 0; i < 7; i++ )
	{

		glPushMatrix();
			glShadowProjection(l,e,n); 
			glTranslatef(posx, 0.0, 7);
			glRotatef(-0, 1,0,0);
			glScalef(4.0,6.0,4.0);
			glColor4f(0.1,0.1,0.1,0.4);
			glCallList(_lists[5]);
		glPopMatrix();

		glPushMatrix();
			glShadowProjection(l,e,n); 
			glTranslatef(posx, 0.0, 7);
			glRotatef(-0, 1,0,0);
			glScalef(4.0,6.0,4.0);
			glColor4f(0.1,0.1,0.1,0.4);
			glCallList(_lists[5]);
		glPopMatrix();

		posx += 8.0;

	}

	posx = -15.0;

	//shruberries shadows
	for ( int i = 0; i < 7; i++ )
	{

		glPushMatrix();
			glShadowProjection(l,e,n); 
			glTranslatef(posx+1.5,0.0, 10);
			glRotatef(-180, 1,0,0);
			glScalef(3.0,5,3.0);
			glColor4f(0.1,0.1,0.1,0.4);
			glCallList(_lists[4]);
		glPopMatrix();

		posx += 8.0;

	}

	glDisable(GL_BLEND);

}

void Stage::setupShadow( )
{

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);

	glLightfv(GL_LIGHT0, GL_POSITION, l);
	glDisable(GL_LIGHTING);

}

void Stage::glShadowProjection(float * l, float * e, float * n)
{
  float d, c;
  float mat[16];

  // These are c and d (corresponding to the tutorial)
  
  d = n[0]*l[0] + n[1]*l[1] + n[2]*l[2];
  c = e[0]*n[0] + e[1]*n[1] + e[2]*n[2] - d;

  // Create the matrix. OpenGL uses column by column
  // ordering

  mat[0]  = l[0]*n[0]+c; 
  mat[4]  = n[1]*l[0]; 
  mat[8]  = n[2]*l[0]; 
  mat[12] = -l[0]*c-l[0]*d;
  
  mat[1]  = n[0]*l[1];        
  mat[5]  = l[1]*n[1]+c;
  mat[9]  = n[2]*l[1]; 
  mat[13] = -l[1]*c-l[1]*d;
  
  mat[2]  = n[0]*l[2];        
  mat[6]  = n[1]*l[2]; 
  mat[10] = l[2]*n[2]+c; 
  mat[14] = -l[2]*c-l[2]*d;
  
  mat[3]  = n[0];        
  mat[7]  = n[1]; 
  mat[11] = n[2]; 
  mat[15] = -d;

  // Finally multiply the matrices together *plonk*
  glMultMatrixf(mat);
}

void Stage::setupObjectTextures( )
{

	GLbyte *pBytes;                     // Texture bytes
    GLint iComponents, iWidth, iHeight; // Texture sizes
    GLenum eFormat;                     // Texture format
    
    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    
    // Decal texture environment
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    
    glGenTextures(6, _objTextures);

	//texture for the tree trunk
    glBindTexture(GL_TEXTURE_2D, _objTextures[0]);
    pBytes = gltLoadTGA("textures/scratched.tga", &iWidth, &iHeight, &iComponents, &eFormat);    
    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
    free(pBytes);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);

	//texture for the tree leaves
	glBindTexture(GL_TEXTURE_2D, _objTextures[1]);
    pBytes = gltLoadTGA("textures/grass.tga", &iWidth, &iHeight, &iComponents, &eFormat);    
    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
    free(pBytes);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glEnable(GL_TEXTURE_2D);

	//texture for the fence
	glBindTexture(GL_TEXTURE_2D, _objTextures[2]);
    pBytes = gltLoadTGA("textures/marble.tga", &iWidth, &iHeight, &iComponents, &eFormat);
    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
    free(pBytes);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glEnable(GL_TEXTURE_2D);

	//another texture for the fence
	glBindTexture(GL_TEXTURE_2D, _objTextures[3]);
    pBytes = gltLoadTGA("textures/marble02.tga", &iWidth, &iHeight, &iComponents, &eFormat);    
    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
    free(pBytes);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glEnable(GL_TEXTURE_2D);

	//texture for the small plants
	glBindTexture(GL_TEXTURE_2D, _objTextures[4]);
    pBytes = gltLoadTGA("textures/thinleaves.tga", &iWidth, &iHeight, &iComponents, &eFormat);    
    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, (void *)pBytes);
    free(pBytes);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glEnable(GL_TEXTURE_2D);

	// Turn on texture coordinate generation
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);

    objTex = true;

}

void Stage::DrawTex3DObjects(  )
{

	// Projection plane
    GLfloat sPlane[] = { 0.5f, 0.0f, 0.0f, 0.5f };
	GLfloat tPlane[] = { 0.0f, 0.5f, 0.0f, 0.5f };

	// Object linear (texture doesn't change)
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
    glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

	glMatrixMode(GL_MODELVIEW);

    // Turn texgen and depth writing back on
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glDepthMask(GL_TRUE);

    //randomly place the trees in the scene
	const int MAX_TREES = 20;

	srand(35465146);

	int _angles[MAX_TREES];

	int lowest, highest, range;
	lowest = 1; highest = 360;
	range = (highest-lowest);

	for ( int a = 0; a < MAX_TREES; a++ )
		_angles[a] = lowest + int(range*rand()/(RAND_MAX + 1.0));

	srand(64226799);

	float _zs[MAX_TREES];

	for ( int z = 0; z < MAX_TREES; z++ )
		_zs[z] = 15.0 + float((25.0-15.0)*rand()/(RAND_MAX + 1.0));

	srand(89753780);

	float _xs[MAX_TREES];

	for ( int x = 0; x < MAX_TREES; x++ )
		_xs[x] = -30.0 + float((30.0+30.0)*rand()/(RAND_MAX + 1.0));


	for ( int i = 0; i < MAX_TREES; i++ )
	{

		glBindTexture(GL_TEXTURE_2D, _objTextures[0]);

		glPushMatrix();
			glTranslatef(_xs[i], 0.0, _zs[i] );
			glRotatef(-90,1,0,0);
			glRotatef(_angles[i],0,0,1);
			glScalef(5.0,7.5,5.0);
			glCallList(_lists[TREE]);
		glPopMatrix();
	
		glBindTexture(GL_TEXTURE_2D, _objTextures[1]);

		glPushMatrix();
			glTranslatef(_xs[i], 0.25, _zs[i]);
			glRotatef(-90, 1,0,0);
			glRotatef(_angles[i],0,0,1);
			glScalef(5.0,7.5,5.0);
			glCallList(_lists[TREETOP]);
		glPopMatrix();

	}

	//place the shruberries and the fences
	float posx = -32.0;

	for ( int i = 0; i < 7; i++ )
	{

		glBindTexture(GL_TEXTURE_2D, _objTextures[2]);

		glPushMatrix();
			glTranslatef(posx, 0.0, 10);
			glRotatef(-90, 1,0,0);
			glScalef(4.0,6.0,4.0);
			glCallList(_lists[FENCE]);
		glPopMatrix();

		glBindTexture(GL_TEXTURE_2D, _objTextures[3]);

		glPushMatrix();
			glTranslatef(posx, 0.0, 10);
			glRotatef(-90, 1,0,0);
			glScalef(4.0,6.0,4.0);
			glCallList(_lists[FENCE]);
		glPopMatrix();

		posx += 8.0;

	}

	posx = -23.5;

	for ( int i = 0; i < 7; i++ )
	{

		glBindTexture(GL_TEXTURE_2D, _objTextures[4]);

		glPushMatrix();
			glTranslatef(posx,0.0, 10.0);
			glRotatef(-90, 1,0,0);
			glScalef(3.0,2.5,3.0);
			glCallList(_lists[TREE02]);
		glPopMatrix();

		posx += 8.0;

	}
	
	//some stupid bunnies
	glBindTexture(GL_TEXTURE_2D, _objTextures[3]);

	glPushMatrix();
		glTranslatef(-14.0, 3.0, -6.0);
		glRotatef(45, 0,1,0);
		glScalef(7.0, 7.0, 7.0);
		glCallList(_lists[BUNNY]);
	glPopMatrix();


}

void Stage::DrawTextures( )
{

	glDisable(GL_CULL_FACE);

	glColor3f(0.8,0.8,0.8);

	glEnable(GL_TEXTURE_2D);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	if ( !texInit )
		loadTextures( );

	//plank texture
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -16.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -12.0f, 0.0f, -16.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -12.0f, 7.0f, -16.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -16.0f, 7.0f, -4.0f);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -6.0f, 0.0f,  -16.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -6.0f, 7.0f,  -16.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -2.0f, 7.0f, -4.0f);
	glEnd();

	//brick texture
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -48.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -32.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -32.0f, 6.0f, -4.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -48.0f, 6.0f, -4.0f);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -32.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -16.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -16.0f, 6.0f, -4.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -32.0f, 6.0f, -4.0f);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 14.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 14.0f, 6.0f, -4.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -2.0f, 6.0f, -4.0f);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 14.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 30.0f, 0.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 30.0f, 6.0f, -4.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 14.0f, 6.0f, -4.0f);
	glEnd();

	//worn wood texture
	glBindTexture(GL_TEXTURE_2D, texture[2]);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -18.0f, 6.0f,  -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -9.0f, 6.0f,   -4.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -9.0f, 10.0f,  -4.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -18.0f, 10.0f, -4.0f);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -9.0f, 6.0f,  -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f, 6.0f,   -4.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f, 10.0f,  -4.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -9.0f, 10.0f, -4.0f);
	glEnd();

	//floor 
	glBindTexture(GL_TEXTURE_2D, texture[4]);

	float zs [6]  = { 15.0, 10.0, 5.0, 0.0, -5.0, -10.0 };
	float xs [13] = { -30.0, -25.0, -20.0, -15.0, -10.0, -5.0, 0.0, 5.0, 10.0, 15.0, 20.0, 25.0, 30.0 };

	glBegin(GL_QUADS);

	for ( int i = 1; i <= 6; i++ )
	{
		for ( int j = 1; j <= 13; j++ )
		{
			glNormal3f(0.0,1.0,0.0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( xs[j], 	   e[1]-0.1f,  zs[i] );
			glTexCoord2f(1.0f, 0.0f); glVertex3f( xs[j] - 5.0, e[1]-0.1f,  zs[i] );
			glTexCoord2f(1.0f, 1.0f); glVertex3f( xs[j] - 5.0, e[1]-0.1f,  zs[i] - 5.0 );
			glTexCoord2f(0.0f, 1.0f); glVertex3f( xs[j], 	   e[1]-0.1f,  zs[i] - 5.0 );

		}
	}

	glEnd();

	//roof texture
	glBindTexture(GL_TEXTURE_2D, texture[5]);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -16.0f, 7.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -12.0f, 7.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -12.0f, 7.0f, -16.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -16.0f, 7.0f, -16.0f);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -2.0f, 7.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -6.0f, 7.0f,  -4.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -6.0f, 7.0f,  -16.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -2.0f, 7.0f, -16.0f);
	glEnd();

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -12.0f, 7.0f, -4.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -6.0f, 7.0f, -4.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -6.0f, 7.0f, -16.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -12.0f, 7.0f, -16.0f);
	glEnd();

	//back texture
	glBindTexture(GL_TEXTURE_2D, texture[6]);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -12.0f, 0.0f, -16.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -6.0f, 0.0f, -16.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -6.0f, 7.0f, -16.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -12.0f, 7.0f, -16.0f);
	glEnd();

	//soup cans
	glBindTexture(GL_TEXTURE_2D, texture[7]);

	glBegin(GL_QUADS);

	for ( int i = 1; i <= 6; i++ )
	{
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -4.0f -i , 0.0f, -8.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -4.5f-i, 0.0f, -8.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -4.5f-i, 1.0f, -8.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -4.0f-i, 1.0f, -8.0f);
	}

	for ( int i = 1; i <= 5; i++ )
	{
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -4.5f -i , 0.0f, -10.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -5.0f-i, 0.0f, -10.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -5.0f-i, 1.0f, -10.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -4.5f-i, 1.0f, -10.0f);
	}

	for ( int i = 1; i <= 7; i++ )
	{
		glTexCoord2f(0.0f, 0.0f); glVertex3f( -5.0f -i , 0.0f, -12.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( -5.5f-i, 0.0f, -12.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( -5.5f-i, 1.0f, -12.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( -5.0f-i, 1.0f, -12.0f);
	}

	glEnd();


	glDisable(GL_TEXTURE_2D);

}

void Stage::Draw3DObjects( )
{

	/*glPushMatrix();
		glTranslatef(-40.0,0.0, -4.0);
		glRotatef(-90, 1,0,0);
		glScalef(5.0,0.5,-3.0);
		glCallList(_lists[0]);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-25.0,0.0, -4.0);
		glRotatef(-90, 1,0,0);
		glScalef(5.0,0.5,-3.0);
		glCallList(_lists[0]);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(25.0, 5.0, 4.0);
		glRotatef(-90, 1,0,0);
		glScalef(5.0, 5.0, 3.0);
		glCallList(_lists[6]);
	glPopMatrix();*/

	glColor3f(0.7,0.0,0.0);

	glPushMatrix();
		glTranslatef(-14.0, 0.0, -6.0);
		glRotatef(45, 0,1,0);
		glScalef(7.0, 7.0, 7.0);
		glCallList(_lists[BUNNY]);
	glPopMatrix();


}

void Stage::DrawTextSign( )
{
	const char* ARENA[5] = { "A", "R", "E", "N", "A" };
	const char* BOOM_BOOM[11] = { "B", "O", "O", "M", "!", " ", "B", "O", "O", "M", "!" };
	const char* BOOM2[9] = { "B", "O", "O", "O", "O", "M", "M", "M", "!" };

	float space = 0.0;


	for ( int i = 0; i < 11; i++ )
	{

		glColor3f( 1.0f * ((float)random()/RAND_MAX),
					   1.0f * ((float)random()/RAND_MAX),
					   1.0f * ((float)random()/RAND_MAX) );

		glPushMatrix();
			//glRotatef(90 * i, 0, 1, 0);
			glTranslatef(-17 + space, 9.0, -4.0);
			t3dDraw3D(BOOM_BOOM[i], 0, 0, 0.15f);
		glPopMatrix();

		space += 1.0;

	}

	space = 0.0;

	for ( int i = 0; i < 9; i++ )
	{
		glColor3f( 1.0f * ((float)random()/RAND_MAX),
					   1.0f * ((float)random()/RAND_MAX),
					   1.0f * ((float)random()/RAND_MAX) );
		glPushMatrix();
			//glRotatef(90 * i, 0, 1, 0);
			glTranslatef(-17 + space, 7.0, -4.0);
			t3dDraw3D(BOOM2[i], 0, 0, 0.15f);
		glPopMatrix();

		space += 1.5;

	}

	space = 0.0;
	glColor3f(1.0,0.0,0.0);

	for ( int i = 0; i < 5; i++ )
	{

		glPushMatrix();

			glTranslatef(-4.0 + space , 9.5 - space, -4.0);
			glRotatef(-45, 0, 0, 1);
			t3dDraw3D(ARENA[i], 0, 0, 0.15f);
		glPopMatrix();

		space += 0.6;

	}


}

void Stage::DrawSkyBox(void)
{
    GLfloat fExtent = 40.0f;
    
    glBegin(GL_QUADS);
        //////////////////////////////////////////////
        // Negative X
        glTexCoord3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-fExtent, -0.2, fExtent);
        
        glTexCoord3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-fExtent, -0.2, -fExtent);
        
        glTexCoord3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-fExtent, fExtent, -fExtent);
        
        glTexCoord3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-fExtent, fExtent, fExtent);


        ///////////////////////////////////////////////
        //  Postive X
        glTexCoord3f(1.0f, -1.0f, -1.0f);
        glVertex3f(fExtent, -0.2, -fExtent);
        
        glTexCoord3f(1.0f, -1.0f, 1.0f);
        glVertex3f(fExtent, -0.2, fExtent);
        
        glTexCoord3f(1.0f, 1.0f, 1.0f);
        glVertex3f(fExtent, fExtent, fExtent);
        
        glTexCoord3f(1.0f, 1.0f, -1.0f);
        glVertex3f(fExtent, fExtent, -fExtent);
 

        ////////////////////////////////////////////////
        // Negative Z 
        glTexCoord3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-fExtent, -0.2, -fExtent);
        
        glTexCoord3f(1.0f, -1.0f, -1.0f);
        glVertex3f(fExtent, -0.2, -fExtent);
        
        glTexCoord3f(1.0f, 1.0f, -1.0f);
        glVertex3f(fExtent, fExtent, -fExtent);
        
        glTexCoord3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-fExtent, fExtent, -fExtent);


        ////////////////////////////////////////////////
        // Positive Z 
        glTexCoord3f(1.0f, -1.0f, 1.0f);
        glVertex3f(fExtent, -0.2, fExtent);
        
        glTexCoord3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-fExtent, -0.2, fExtent);
        
        glTexCoord3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-fExtent, fExtent, fExtent);
        
        glTexCoord3f(1.0f, 1.0f, 1.0f);
        glVertex3f(fExtent, fExtent, fExtent);


        //////////////////////////////////////////////////
        // Positive Y
        glTexCoord3f(-1.0f, 1.0f, 1.0f);
        glVertex3f(-fExtent, fExtent, fExtent);
        
        glTexCoord3f(-1.0f, 1.0f, -1.0f);
        glVertex3f(-fExtent, fExtent, -fExtent);
        
        glTexCoord3f(1.0f, 1.0f, -1.0f);
        glVertex3f(fExtent, fExtent, -fExtent);
        
        glTexCoord3f(1.0f, 1.0f, 1.0f);
        glVertex3f(fExtent, fExtent, fExtent);
  
    
        ///////////////////////////////////////////////////
        // Negative Y
        glTexCoord3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-fExtent, -0.2, -fExtent);
        
        glTexCoord3f(-1.0f, -1.0f, 1.0f);
        glVertex3f(-fExtent, -0.2, fExtent);
        
        glTexCoord3f(1.0f, -1.0f, 1.0f);
        glVertex3f(fExtent, -0.2, fExtent);
        
        glTexCoord3f(1.0f, -1.0f, -1.0f);
        glVertex3f(fExtent, -0.2, -fExtent);
    glEnd();
}

GRAPHICSLAB_NAMESPACE_END

