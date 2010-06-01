/*
 *  plyData.cpp
 *  Mesh Rendering
 *
 *  Created by Renato Pajarola on Wed Nov 05 2003.
 *  Copyright (c) 2008 University of Zurich. All rights reserved.
 *
 *  Modified by Fatih Erol on 11.03.2009
 */

// Class declaration include
#include "plyData.hpp"

// Includes
#include "utils.hpp"
#include <sstream>
#include <limits>
#include <iostream>
#include <cstring>

#include <fstream>
#include <stdio.h>

GRAPHICSLAB_NAMESPACE_BEGIN    

//const int PLYData::NUM_PROPERTIES;


#define FOPEN( a, b, c ) \
a = fopen( b, c ); \
if ( a == NULL ) \
{ \
	std::stringstream error; \
	error << "Failed to open file \"" << b << "\""; \
	throw PLYException( error.str() ); \
}

#define FSCANF	fscanf
#define SSCANF	sscanf


PLYData::PLYData() :
    modelFileName( "" ),
    numVertexProperties( 0 ),
    hasNormal( false ), hasColor( false ), hasTexture( false ),
    numVertices( 0 ), numFaces( 0 ), numEdges( 0 ),
    min( std::numeric_limits<float>::min() ), max( -std::numeric_limits<float>::max() ),
    binary( false ), bigEndian( false )
{
}


PLYData::PLYData( const PLYData &other ) :
    modelFileName( other.modelFileName ),
    numVertexProperties( other.numVertexProperties ),
    hasNormal( other.hasNormal ), hasColor( other.hasColor ), hasTexture( other.hasTexture ),
    numVertices( other.numVertices ), numFaces( other.numFaces ), numEdges( other.numEdges ),
    min( other.min ), max( other.max ),
    vertices( other.vertices ), normals( other.normals ), colors( other.colors ),
    texCoords( other.texCoords), faces( other.faces ), faceNormals( other.faceNormals ),
    binary( other.binary ), bigEndian( other.bigEndian )
{
    memcpy( vertexPropertyOrder, other.vertexPropertyOrder, NUM_PROPERTIES * sizeof( char ) );
    memcpy( vertexPropertyTypes, other.vertexPropertyTypes, NUM_PROPERTIES * sizeof( PropType ) );
}

PLYData::PLYData( const std::string &fname )
{
    loadFromFile( fname );
}

void PLYData::reset()
{
    modelFileName = "";
    numVertexProperties = 0;
    hasNormal = hasColor = hasTexture = false;
    numVertices = numFaces = numEdges = 0;
    min = std::numeric_limits<float>::min();
    max = -std::numeric_limits<float>::max();
    vertices.clear(); normals.clear(); colors.clear();
    texCoords.clear(); faces.clear(); faceNormals.clear();
    binary = bigEndian = false;
}

void PLYData::loadFromFile( const std::string &fname )
{
    // Clear old data
    reset();

    FILE *file = NULL;
	FOPEN( file, fname.c_str(), "r" );
	//fopen_s( &file, fname.c_str(), "r" );
    
    modelFileName = fname;
    
    // Initialize default order
    for ( int i = 0; i < NUM_PROPERTIES; i++)
        vertexPropertyOrder[i] = -1;
    
    
    try
    {
        checkHeader( file );
        readVertices( file );
        readFaces( file );
    }
    catch ( const PLYException &e )
    {
        fclose( file );
        throw e;
    }
    catch (...)
    {
        std::stringstream error;
        error << "Unknown exception during processing of file \"" << fname << "\"";
        throw PLYException( error.str() );
    }
	
	fclose( file );
}


PLYData::~PLYData()
{
    reset();
}


void PLYData::checkHeader( FILE *in )
{
    char buf[128], type[128], c[32];
    
    
    // Read ply file header
    
    // Read file type
    FSCANF( in, "%s\n", buf );

    if ( strcmp( buf, "ply" ) != 0 ) 
    {
        throw PLYException( "Input file is not of .ply type" );
    }
    
    // Read format : binary/ascii, bigEndian/littleEndian
    fgets( buf, 128, in );
    if ( strncmp( buf, "format ascii", 12 ) == 0 ) 
    {
        binary = false;
    }
    else if ( strncmp( buf, "format binary", 13 ) == 0 ) 
    {
        binary = true;
        if ( strstr( buf, "big_endian" ) != 0 )
            bigEndian = true;
        else
            bigEndian = false;
    }
    else 
    {
        throw PLYException( "Input file is not recognized either as ASCII or binary format" );
    }
    
    // Ignore comment lines
    do
    {
        fgets( buf, 128, in );
    }
    while ( strncmp( buf, "comment", 7 ) == 0 );
    
    
    // Read number of vertices
    if ( strncmp( buf, "element vertex", 14 ) == 0 )
    {
		SSCANF( buf, "element vertex %d\n", &numVertices );
    }
    else 
    {
        throw PLYException( "Number of vertices expected" );
    }
    
    // Read vertex properties order
    int propertyIndex = 0;
    fgets( buf, 128, in );
    while ( strncmp( buf, "property", 8 ) == 0 ) 
    {
		SSCANF( buf, "property %s %s\n", type, c );

		if ( strncmp( type, "uchar", 5 ) == 0 )
            vertexPropertyTypes[propertyIndex] = UCHAR;
        else
            vertexPropertyTypes[propertyIndex] = FLOAT;
        
        if ( strncmp( c, "x", 1 ) == 0 )
            vertexPropertyOrder[0] = propertyIndex;
        else if ( strncmp( c, "y", 1 ) == 0 )
            vertexPropertyOrder[1] = propertyIndex;
        else if ( strncmp( c, "z", 1 ) == 0 )
            vertexPropertyOrder[2] = propertyIndex;
        
        else if ( strncmp( c, "nx", 2 ) == 0 )
            vertexPropertyOrder[3] = propertyIndex;
        else if ( strncmp( c, "ny", 2 ) == 0 )
            vertexPropertyOrder[4] = propertyIndex;
        else if ( strncmp( c, "nz", 2 ) == 0 )
            vertexPropertyOrder[5] = propertyIndex;
        
        else if ( strncmp( c, "red", 3 ) == 0 )
            vertexPropertyOrder[6] = propertyIndex;
        else if ( strncmp( c, "green", 5 ) == 0 )
            vertexPropertyOrder[7] = propertyIndex;
        else if ( strncmp( c, "blue", 4 ) == 0 )
            vertexPropertyOrder[8] = propertyIndex;
        
        else if ( strncmp( c, "tu", 2 ) == 0 )
            vertexPropertyOrder[9] = propertyIndex;
        else if ( strncmp( c, "tv", 2 ) == 0 )
            vertexPropertyOrder[10] = propertyIndex;
        
        propertyIndex++;
        fgets( buf, 128, in );
    }
    numVertexProperties = propertyIndex;
    
    for (int i = 0; i < 3; i++ )
    {
        if ( vertexPropertyOrder[i] < 0 ) 
        {
            throw PLYException( "Not enough vertex coordinate fields (nx, ny, nz)" );
        }
    }
    
    
    hasNormal = true;
    for ( int i = 3; i < 6; i++ )
    {
        if ( vertexPropertyOrder[i] < 0 )
            hasNormal = false;
    }
    
    
    hasColor = true;
    for ( int i = 6; i < 9; i++ )
    {
        if ( vertexPropertyOrder[i] < 0 )
            hasColor = false;
    }
    
    hasTexture = true;
    for ( int i = 9; i < NUM_PROPERTIES; i++ )
    {
        if ( vertexPropertyOrder[i] < 0 )
            hasTexture = false;
    }
    
    if ( !hasNormal )
        std::cerr << "WARNING: No normal coordinates used from file." << std::endl;
    if ( !hasColor )
        std::cerr << "WARNING: No color used from file." << std::endl;
    if ( !hasTexture )
        std::cerr << "WARNING: No texture coordinates used from file." << std::endl;
    
    // Number of faces and face properties
    if ( strncmp( buf, "element face", 12 ) == 0 )
		SSCANF( buf, "element face %d\n", &numFaces );
    else
    {
        throw PLYException( "Number of faces expected" );
    }
    
    numEdges = 3 * numFaces;
    
    fgets( buf, 128, in );
    if ( strncmp( buf, "property list uchar int", 23 ) != 0 )
    {
        throw PLYException( "Face property list with integer indices expected" );
    }
    
    do
    {
        fgets( buf, 128, in );
    }
    while ( strncmp( buf, "end_header", 10 ) != 0 );
    
    // Setup arrays to hold appropriate number of elements
    vertices.resize( numVertices );
    normals.resize( numVertices );
    if ( hasColor )
        colors.resize( numVertices );
    if ( hasTexture )
        texCoords.resize( numVertices );
    
    faces.resize( numFaces );
    faceNormals.resize( numFaces );
}


void PLYData::readVertices( FILE *in )
{
    char buf[128];
    uchar uc;
    float values[32];
    
    // Read in vertex attributes
    for ( uint i = 0; i < numVertices; i++) 
    {
        if ( binary ) 
        {
            for (int j = 0; j < numVertexProperties; j++)
            {
                if ( vertexPropertyTypes[j] == UCHAR )
                {
                    fread( &uc, sizeof( uchar ), 1, in );
                    values[j] = ( float ) uc;
                }
                else
                    fread( &values[j], sizeof( float ), 1, in );
            }
        }
        else
        {
            fgets( buf, 128, in );
            SSCANF( buf,"%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", 
                   &values[0], &values[1], &values[2], &values[3], 
                   &values[4], &values[5], &values[6], &values[7], 
                   &values[8], &values[9], &values[10], &values[11], 
                   &values[12], &values[13], &values[14], &values[15]);
        }
        
        for ( int j = 0; j < 3; j++ )
            vertices[i][j] = values[(int)vertexPropertyOrder[j]];
        
        if ( hasNormal )
            for ( int j = 0; j < 3; j++ )
                normals[i][j] = values[(int)vertexPropertyOrder[3+j]];
        
        if ( hasColor )
            for ( int j = 0; j < 3; j++ )
                colors[i][j] = (uchar)values[(int)vertexPropertyOrder[6+j]];
        
        for ( int j = 0; j < 3; j++ )
        {
            if ( vertices[i][j] < min[j] )
                min[j] = vertices[i][j];
            if ( vertices[i][j] > max[j] )
                max[j] = vertices[i][j];
        }
        
        if ( hasTexture )
            for ( int j = 0; j < 2; j++ )
                texCoords[i][j] = values[(int)vertexPropertyOrder[9+j]];
    }
}



void PLYData::readFaces( FILE *in )
{
    char buf[128];
    uchar uc;
    int k;
    
    // Read in face connectivity
    for ( uint i = 0; i < numFaces; i++ )
    {
        if ( binary )
        {
            fread( &uc, sizeof( uchar ), 1, in );
            fread( &faces[i], sizeof( int ), 3, in );
            if ( uc != 3 )
            {
                throw PLYException( "Not a triangular face" );
            }
        }
        else
        {
            fgets( buf, 128, in );
            SSCANF( buf, "%d %d %d %d", &k, &faces[i][0], &faces[i][1], &faces[i][2] );
            if ( k != 3 )
            {
                throw PLYException( "Not a triangular face" );
            }
        }
        
        // Set up face normal
        faceNormals[i] = Utils::normal(vertices[faces[i][0]], vertices[faces[i][1]], vertices[faces[i][2]]);
    }
    
    if ( !hasNormal )
    {
        recalculateNormals();
        hasNormal = true;
    }
}


void PLYData::recalculateNormals()
{
    static vec3f nullVector(0.0);
    
    for ( uint i = 0; i < numVertices; i++ )
        normals[i] = nullVector;
    
    // Accumulate normal information of each vertex
    for ( uint i = 0; i < numFaces; i++ )
    {
        for ( int j = 0; j < 3; j++ )
            normals[faces[i][j]] += faceNormals[i];
    }
    
    for ( uint i = 0; i < numVertices; i++ )
        Utils::normalize( normals[i] );
}


void PLYData::write( const std::string &fname )
{
	FILE *out = NULL;

	FOPEN( out, fname.c_str(), "w" );
    
    // Print header
    fprintf( out, "ply\n" );
    fprintf( out, "format ascii 1.0\n" );
    fprintf( out, "comment created by Renato's PLYObject\n" );
    fprintf( out, "element vertex %d\n", numVertices );
    
    fprintf( out, "property float x\n" );
    fprintf( out, "property float y\n" );
    fprintf( out, "property float z\n" );
    
    if ( hasNormal )
    {
        fprintf( out, "property float nx\n" );
        fprintf( out, "property float ny\n" );
        fprintf( out, "property float nz\n" );
    }
    
    if ( hasColor )
    {
        fprintf( out, "property uint red\n" );
        fprintf( out, "property uint green\n" );
        fprintf( out, "property uint blue\n" );
    }
    
    if ( hasTexture )
    {
        fprintf( out, "property float ut\n" );
        fprintf( out, "property float tv\n" );
    }
    
    fprintf( out, "element face %d\n", numFaces );
    fprintf( out, "property list uchar int vertex_indices\n");
    fprintf( out, "end_header\n");
    
    // Print vertices
    for ( uint i = 0; i < numVertices; i++ )
    {
        fprintf( out, "%f %f %f", vertices[i][0], vertices[i][1], vertices[i][2] );
        if ( hasNormal )
            fprintf( out, " %f %f %f", normals[i][0], normals[i][1], normals[i][2] );
        if ( hasColor )
            fprintf( out, " %d %d %d", colors[i][0], colors[i][1], colors[i][2] );
        if ( hasTexture )
            fprintf( out, " %f %f", texCoords[i][0], texCoords[i][1] );
        fprintf( out, "\n" );
    }
    
    // Print faces
    for ( uint i = 0; i < numFaces; i++ )
    {
        fprintf( out, "3 %d %d %d\n", faces[i][0], faces[i][1], faces[i][2] );
    }
    
    fclose( out );
}


void PLYData::resize()
{
    float size, scale;
    vec3f tmp, tmin, tmax;
    
    // Rescale vertex coordinates to be in [-1,1]
    size = 0.0;
    if ( size < max[0]-min[0] )
        size = max[0]-min[0];
    if ( size < max[1]-min[1] )
        size = max[1]-min[1];
    if ( size < max[2]-min[2] )
        size = max[2]-min[2];
    scale = 2.0f / size;
    
    tmp = max + min;
    tmp *= 0.5f;
    
    for ( uint i = 0; i < numVertices; i++ )
    {
        vertices[i] -= tmp;
        vertices[i] *= scale;
    }
    
    tmin = min - max;
    tmin *= ( scale * 0.5f );
    
    tmax = max - min;
    tmax *= ( scale * 0.5f );
    
    min = tmin;
    max = tmax;
}


void PLYData::invertNormals()
{
    int tmp;
    
    for ( uint i = 0; i < numVertices; i++ )
        normals[i] *= -1;
    
    for ( uint i = 0; i < numFaces; i++ )
    {
        faceNormals[i] *= -1.0;
        
        tmp = faces[i][0];
        faces[i][0] = faces[i][2];
        faces[i][2] = tmp;
    }
}


void PLYData::setPlanarTexture()
{
    if ( !hasTexture )
    {
        hasTexture = 1;
        texCoords.resize( numFaces );
    }
    
    for ( uint i = 0; i < numVertices; i++ )
    {
        texCoords[i][0] = ( vertices[i][0] - min[0] ) / ( max[0]-min[0] );
        texCoords[i][1] = ( vertices[i][1] - min[1] ) / ( max[1]-min[1] );
    }
}


} // namespace graphics_lab

