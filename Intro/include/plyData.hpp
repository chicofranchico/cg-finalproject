/*
 *  plyData.hpp
 *  Mesh Rendering
 *
 *  Created by Renato Pajarola on Wed Nov 05 2003.
 *  Copyright (c) 2008 University of Zurich. All rights reserved.
 *
 *  Modified by Fatih Erol on 11.03.2009
 */

#ifndef GRAPHICSLAB_PLYDATA_HPP
#define GRAPHICSLAB_PLYDATA_HPP

// Includes
#include "exception.hpp"
#include "vector.hpp"

#include <string>
#include <vector>

GRAPHICSLAB_NAMESPACE_BEGIN

/** Enumeration for property type */
enum PropType 
{
    FLOAT, 
    UCHAR
};

/** Exception to be thrown from PLYData related stuff */
class PLYException : public Exception
{
public:
    PLYException( const std::string &error ) : Exception( error ) {}
    
}; // class PLYException

/** Class to hold data about a ply format mesh */
class PLYData
{
public:
    /** Constructor */
    PLYData();
    /**
     * Constructor.
     *
     * @param[in]   fname   File to load mesh data from
     */
    PLYData( const std::string &fname );
    
    /**
     * Copy constructor.
     *
     * @param[in]   other   Other object to copy from
     */
    PLYData( const PLYData &other );
    
    /** Destructor */
    ~PLYData();
    
    /** Reset internal data */
    void reset();
    
    /**
     * Load mesh data from a file.
     *
     * @param[in]   fname   File name to load mesh data from
     */
    void loadFromFile( const std::string &fname );
    
    /**
     * Write mesh data to a file.
     *
     * @param[in]   fname   File name to write the data to
     */
    void write( const std::string &fname );
    
    void resize();        
    
    void setPlanarTexture();
    
    void invertNormals();
    void recalculateNormals();
        
public:
    std::string modelFileName;
    
    int numVertexProperties;                // number of vertex properties
    static const int NUM_PROPERTIES = 11;
    char vertexPropertyOrder[NUM_PROPERTIES];			// order of x,y,z, nx,ny,nz, red,green,blue, tu,tv vertex properties
    PropType vertexPropertyTypes[NUM_PROPERTIES];           // type of the vertex properties
    
    bool hasNormal, hasColor, hasTexture;
    
    uint numVertices, numFaces, numEdges;	// number of vertices, faces, edges
    
    vec3f min, max;
    
    std::vector<vec3f> vertices;	// array of point coordinates
    std::vector<vec3f> normals;     // array of point normals
    std::vector<vec3ub> colors;     // array of point colors
    
    std::vector<vec2f> texCoords;   // array of texture coords
    std::vector<vec3i> faces;       // array of face indices
    std::vector<vec3f> faceNormals;	// array of face normals
    
private:
    void checkHeader( FILE *in );
    void readVertices( FILE *in );
    void readFaces( FILE *in );
    
    
    
private:
    bool binary, bigEndian;
}; // class PLYData

GRAPHICSLAB_NAMESPACE_END

#endif  // GRAPHICSLAB_PLYDATA_HPP


