/**
 * plyData.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   04.03.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_PLYDATA_HPP
#define GRAPHICSLAB_PLYDATA_HPP

// Includes
#include "defs.hpp"

#include "types.hpp"

#include <string>
#include <vector>
#include <map>
#include <fstream>

GRAPHICSLAB_NAMESPACE_BEGIN

/** Class to hold data for a ply model mesh */
class PLYData
{
public:
    /** Constructor  */
    PLYData();
    
    /** Destructor */
    ~PLYData();
    
    /** Empty the data */
    void reset();
    
    /**
     * Load PLY file.
     *
     * @param[in]   fileName    Name of the file to load from
     */
    void loadFromFile( const std::string &fileName );
    
    void getVertexPoint( unsigned int vertexIndex, Point &point ) const;
	void getFaceIndices( unsigned int faceIndex, vec3ui &indices ) const;
    

	unsigned int getNumVertices() const { return _numVertices; }
	unsigned int getNumFaces() const { return _numFaces; }

private:
    /** Enumeration for file format */
    enum Format
    {
        ASCII,
        BINARY_LITTLE_ENDIAN,
        BINARY_BIG_ENDIAN
    };
    
    /** File format */
    Format _format;
    
    /** PLY file version */
    std::string _version;
    
    /** Enumeration for data types */
    enum DataType
    {
        CHAR,
        UCHAR,
        SHORT,
        USHORT,
        INT,
        UINT,
        FLOAT,
        DOUBLE,
        INT8,
        UINT8,
        INT16,
        UINT16,
        INT32,
        UINT32,
        FLOAT32,
        FLOAT64
    };
    typedef std::map<std::string, DataType> DataTypeStringMap;
    static DataTypeStringMap &_dataTypeStringMap;
    static DataTypeStringMap &initDataTypeStringMap();

    void readData( DataType type, std::ifstream &file, unsigned char *ptr );
    
    template <typename T>
    T getValue( DataType type, void *ptr ) const
    {
        switch ( type )
        {                    
            case CHAR:
            case INT8:
            {
                char data;
                char *dataPtr = reinterpret_cast<char*> ( ptr );
                data = *dataPtr;
                return (T)data;
                break;
            }
            case UCHAR:
            case UINT8:
            {
                unsigned char data;
                unsigned char *dataPtr = reinterpret_cast<unsigned char*> ( ptr );
                data = *dataPtr;
                return (T)data;
                break;
            }
            case SHORT:
            case INT16:
            {
                short data;
                short *dataPtr = reinterpret_cast<short*> ( ptr );
                data = *dataPtr;
                return (T)data;
                break;
            }
            case USHORT:
            case UINT16:
            {
                unsigned short data;
                unsigned short *dataPtr = reinterpret_cast<unsigned short*> ( ptr );
                data = *dataPtr;
                return (T)data;
                break;
            }
            case INT:
            case INT32:
            {
                int data;
                int *dataPtr = reinterpret_cast<int*> ( ptr );
                data = *dataPtr;
                return (T)data;
                break;
            }
            case UINT:
            case UINT32:
            {                    
                unsigned int data;
                unsigned int *dataPtr = reinterpret_cast<unsigned int*> ( ptr );
                data = *dataPtr;
                return (T)data;
                break;
            }
            case FLOAT:
            case FLOAT32:
            {
                float data;
                float *dataPtr = reinterpret_cast<float*> ( ptr );
                data = *dataPtr;
                return (T)data;
                break;
            }
            case DOUBLE:
            case FLOAT64:
            default:
            {                    
                double data;
                double *dataPtr = reinterpret_cast<double*> ( ptr );
                data = *dataPtr;
                return (T)data;
                break;
            }
        }
        
    }
    
    
    static unsigned int getDataTypeSize( DataType dataType );
    
    /** Enumeration for propertes for a vertex */
    enum VertexProperty
    {
        VERTEX_PROPERTY_X,
        VERTEX_PROPERTY_Y,
        VERTEX_PROPERTY_Z,
        VERTEX_PROPERTY_NX,
        VERTEX_PROPERTY_NY,
        VERTEX_PROPERTY_NZ,
        VERTEX_PROPERTY_TU,
        VERTEX_PROPERTY_TV,
        VERTEX_PROPERTY_RED,
        VERTEX_PROPERTY_GREEN,
        VERTEX_PROPERTY_BLUE
    };
    typedef std::map<std::string, VertexProperty> VertexPropertyStringMap;
    static VertexPropertyStringMap &_vertexPropertyStringMap;
    static VertexPropertyStringMap &initVertexPropertyStringMap();

    
    /** Number of vertices */
    unsigned int _numVertices;
    
    /** Structure for pair of property-data type for a vertex property */
    struct VertexPropertyType
    {
        VertexProperty property;
        DataType type;
    };
    /** Type definition for a vector of vertex property-data type pairs */
    typedef std::vector<VertexPropertyType> VertexPropertyTypeVector;
    /** Vector of properties and their types to be listed for vertices */
    VertexPropertyTypeVector _vertexPropertyTypeVector;
    /** Buffer to hold vertex data */
    unsigned char *_vertexData;
    unsigned int _numVertexBytes;
    
    /** Number of polygon faces */
    unsigned int _numFaces;
    /** Data type of the number of entries in face listing */
    DataType _numFaceEntryType;
    /** Data type of the entries in the face listing */
    DataType _faceEntryDataType;
    /** Enumeration for what to list for a face */
    enum FaceEntryData
    {
        VERTEX_INDEX
    };
    /** What to be listed for a face */
    FaceEntryData _faceEntryData;
    /** Buffer to hold face data */
    unsigned char *_faceData;
    unsigned int _numFaceBytes;
    unsigned int _numFaceEntry;
    
}; // class PLYData


GRAPHICSLAB_NAMESPACE_END


#endif  // GRAPHICSLAB_PLYDATA_HPP


