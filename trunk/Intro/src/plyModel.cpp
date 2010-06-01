/**
 * plyModel.cpp
 * 
 * Author   :   Fatih Erol
 * Date     :   04.03.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "plyModel.hpp"

// Includes
#include "plyData.hpp"
#include "exception.hpp"
#include "opengl_includes.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN


PLYModel::PLYModel( Scene &scene ) : 
    Drawable( scene ),
    _plyData(NULL)
{
    _material.setAmbient( Color( 0.2, 0.2, 0.2 ) );
    _material.setDiffuse( Color( 0.8, 0.8, 0.8 ) );
    _material.setSpecular( Color( 0.4, 0.4, 0.4 ) );
    _material.setShininess( 64 );
}

PLYModel::~PLYModel()
{
    delete _plyData;
}


void PLYModel::loadModel( const std::string &fname )
{
    if ( _plyData == NULL )
    {
        _plyData = new PLYData();
    }
    
    
    try
    {
        _plyData->loadFromFile( fname );
    }
    catch ( const Exception &exc )
    {
        _plyData->reset();
        throw exc;
    }
    catch (...)
    {
        _plyData->reset();
        throw Exception( "Failed to load PLYData" );
    }
}

void PLYModel::draw( const RenderParameters &renderParameters )
{    
    if ( _plyData != NULL )
    {
		if ( renderParameters.smoothShading )      
			glShadeModel( GL_SMOOTH );       
		else
            glShadeModel( GL_FLAT );

		glEnable( GL_LIGHTING );
		_material.setActive( GL_FRONT_AND_BACK );

		if ( renderParameters.drawMode == RenderParameters::POLYGON )
			glBegin( GL_TRIANGLES );

		for ( uint i = 0; i < _plyData->numFaces; i++ )
        {        

			if ( renderParameters.drawMode == RenderParameters::WIREFRAME )
				glBegin( GL_LINE_LOOP );

			if ( false == renderParameters.smoothShading )
				glNormal3f( _plyData->faceNormals[i][0], 
							_plyData->faceNormals[i][1], 
							_plyData->faceNormals[i][2] );    // face normal

			for ( int j = 0; j < 3; j++ )
			{ 
				if ( renderParameters.smoothShading )
					glNormal3f( _plyData->normals[_plyData->faces[i][j]][0], 
								_plyData->normals[_plyData->faces[i][j]][1], 
								_plyData->normals[_plyData->faces[i][j]][2] );   // vertex normal

				glVertex3f( _plyData->vertices[_plyData->faces[i][j]][0], 
							_plyData->vertices[_plyData->faces[i][j]][1], 
							_plyData->vertices[_plyData->faces[i][j]][2] );      // vertex coordinates
            }

			if ( renderParameters.drawMode == RenderParameters::WIREFRAME )
				glEnd();
		}

		if ( renderParameters.drawMode == RenderParameters::POLYGON )
			glEnd();
	}    
}


GRAPHICSLAB_NAMESPACE_END