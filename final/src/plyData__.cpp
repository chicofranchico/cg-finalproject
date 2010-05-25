/**
 * plyData.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   04.03.2010
 *
 * All rights reserved.
 */

// Class declaration include
#include "plyData.hpp"

// Includes
#include "exception.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

GRAPHICSLAB_NAMESPACE_BEGIN


PLYData::DataTypeStringMap &PLYData::initDataTypeStringMap()
{
    static DataTypeStringMap map;

    map["char"] = CHAR;
    map["uchar"] = UCHAR;
    map["short"] = SHORT;
    map["ushort"] = USHORT;
    map["int"] = INT;
    map["uint"] = UINT;
    map["float"] = FLOAT;
    map["double"] = DOUBLE;
    map["int8"] = INT8;
    map["uint8"] = UINT8;
    map["int16"] = INT16;
    map["uint16"] = UINT16;
    map["int32"] = INT32;
    map["uint32"] = UINT32;
    map["float32"] = FLOAT32;
    map["float64"] = FLOAT64;
 
    return map;
}
PLYData::DataTypeStringMap &PLYData::_dataTypeStringMap = PLYData::initDataTypeStringMap();

unsigned int PLYData::getDataTypeSize( DataType dataType )
{
    switch ( dataType )
    {
        case CHAR:
        case UCHAR:
        case INT8:
        case UINT8:
            return 1;
        case SHORT:
        case USHORT:
        case INT16:
        case UINT16:
            return 2;
        case INT:
        case UINT:
        case FLOAT:
        case INT32:
        case UINT32:
        case FLOAT32:
            return 4;
        case DOUBLE:
        case FLOAT64:
            return 8;
    }
    return 0;
}


PLYData::VertexPropertyStringMap &PLYData::initVertexPropertyStringMap()
{
    static VertexPropertyStringMap map;
    
    map["x"] = VERTEX_PROPERTY_X;
    map["y"] = VERTEX_PROPERTY_Y;
    map["z"] = VERTEX_PROPERTY_Z;
    map["nx"] = VERTEX_PROPERTY_NX;
    map["ny"] = VERTEX_PROPERTY_NY;
    map["nz"] = VERTEX_PROPERTY_NZ;
    map["tu"] = VERTEX_PROPERTY_TU;
    map["tv"] = VERTEX_PROPERTY_TV;
    map["red"] = VERTEX_PROPERTY_RED;
    map["green"] = VERTEX_PROPERTY_GREEN;
    map["blue"] = VERTEX_PROPERTY_BLUE;
    
    return map;
}
PLYData::VertexPropertyStringMap &PLYData::_vertexPropertyStringMap = PLYData::initVertexPropertyStringMap();



PLYData::PLYData() :
    _vertexData( NULL ),
    _faceData( NULL )
{
    reset();
}

PLYData::~PLYData()
{
	delete [] _vertexData;
	delete [] _faceData;
}


void PLYData::reset()
{
    _format = ASCII;
    _version = "1.0";
    _numVertices = 0;
    _vertexPropertyTypeVector.clear();    
    delete [] _vertexData;
    _vertexData = NULL;
    _numVertexBytes = 0;
    
    _numFaces = 0;
    _numFaceEntryType = UCHAR;
    _faceEntryDataType = INT;
    _faceEntryData = VERTEX_INDEX;
    delete [] _faceData;
    _faceData = NULL;
    _numFaceBytes = 0;
    _numFaceEntry = 0;
}

void PLYData::loadFromFile( const std::string &fileName )
{
    // Clean up data
    reset();
    
    // Start loading from file
    std::ifstream file( fileName.c_str() );
    
    if ( !file.is_open() )
    {
        std::stringstream error;
        error << "Failed to open file \"" << fileName << "\"";
        throw Exception( error.str() );
    }
    
    std::string str;
    
    // Read "ply" header
    file >> str;
    if ( str != "ply" )
    {
        std::stringstream error;
        error << "File should start with a \"ply\" line ";
        file.close();
        throw Exception( error.str() ); 
    }
    
    // Read foramat string
    file >> str;
    if ( str != "format" )
    {
        file.close();
        throw Exception( "\"format\" string expected" );
    }
    
    file >> str;
    if ( str == "ascii" )
        _format = ASCII;
    else if ( str == "binary_little_endian" )
        _format = BINARY_LITTLE_ENDIAN;
    else if ( str == "binary_big_endian" )
        _format = BINARY_BIG_ENDIAN;
    else
    {
        file.close();
        throw Exception( "Format can be \"ascii\", \"binary_little_endian\" or \"binary_big_endian\"" );
    }
    
    // Read version string
    file >> _version;

    enum ReadState
    {
        COMPONENT_CHECKING,
        ELEMENT_CHECKING,
        VERTEX_CHECKING,
        VERTEX_PROPERTY_CHECKING,
        FACE_CHECKING,
        FACE_PROPERTY_CHECKING,
        END_HEADER
    } readState;
    
    readState = COMPONENT_CHECKING;
    
    while ( !file.eof() && ( readState != END_HEADER ) )
    {
        switch ( readState )
        {
            case COMPONENT_CHECKING:
            {
                file >> str;                
                
                if ( str == "comment" ) // Ignore comment lines
                {
                    char comment[256];
                    file.getline( comment, 256 );
                }
                else if ( str == "element" )
                {
                    readState = ELEMENT_CHECKING;
                }
                else if ( str == "end_header" )
                {
                    readState = END_HEADER;
                }
                else
                {
                    file.close();
                    std::stringstream error;
                    error << "Unknown component type \"" << str << "\"";
                    throw Exception( error.str() );
                }
                break;
            }
            case ELEMENT_CHECKING:
            {
                file >> str;
                if ( str == "vertex" )
                    readState = VERTEX_CHECKING;
                else if ( str == "face" )
                    readState = FACE_CHECKING;
                else
                {
                    file.close();
                    std::stringstream error;
                    error << "Unknown element type \"" << str << "\"";
                    throw Exception( error.str() );                    
                }
                break;
            }
            case VERTEX_CHECKING:
            {
                int numVertices;
                file >> numVertices;
                
                if ( numVertices < 0 )
                {
                    file.close();
                    throw Exception( "Number of vertices should be a positive value");
                }
                _numVertices = numVertices;
                readState = VERTEX_PROPERTY_CHECKING;
                break;
            }
            case VERTEX_PROPERTY_CHECKING:
            {                
                file >> str;
                if ( str == "property" )
                {
                    std::string type, property;
                    file >> type >> property;     
                    
                    DataTypeStringMap::const_iterator typeIter = _dataTypeStringMap.find( type );
                    if ( typeIter == _dataTypeStringMap.end() )
                    {
                        file.close();
                        std::stringstream error;
                        error << "Unknown vertex property data type \"" << type << "\"";
                        throw Exception( error.str() );
                    }
                    
                    VertexPropertyStringMap::const_iterator propertyIter = _vertexPropertyStringMap.find( property );
                    if ( propertyIter == _vertexPropertyStringMap.end() )
                    {
                        file.close();
                        std::stringstream error;
                        error << "Unknow vertex property \"" << property << "\"";
                        throw Exception( error.str() ) ;
                    }
                    VertexPropertyType vpt;
                    vpt.type = typeIter->second;
                    vpt.property = propertyIter->second;
                    
                    _vertexPropertyTypeVector.push_back( vpt );                    
                }
                else if ( str == "element" )
                {
                    readState = ELEMENT_CHECKING;
                }
                else if ( str == "end_header" )
                {
                    readState = END_HEADER;
                }
                else
                {
                    file.close();
                    std::stringstream error;
                    error << "Unknown component type \"" << str << "\"";
                    throw Exception( error.str() );                    
                }
                
                break;
            }
            case FACE_CHECKING:
            {
                int numFaces;
                file >> numFaces;
                
                if ( numFaces < 0 )
                {
                    file.close();
                    throw Exception( "Number of faces should be a positive value");
                }
                _numFaces = numFaces;
                readState = FACE_PROPERTY_CHECKING;
                break;
            }
            case FACE_PROPERTY_CHECKING:
            {
                file >> str;
                if ( str == "property" )
                {
                    std::string listStr, numFaceEntryTypeStr, faceEntryDataTypeStr, faceEntryDataStr;
                    file >> listStr >> numFaceEntryTypeStr >> faceEntryDataTypeStr >> faceEntryDataStr;
                    std::stringstream error;
                    if ( listStr == "list" )
                    {                        
                        DataTypeStringMap::const_iterator numFaceEntryTypeIter = _dataTypeStringMap.find( numFaceEntryTypeStr );
                        if ( numFaceEntryTypeIter == _dataTypeStringMap.end() )
                        {
                            file.close();
                            std::stringstream error;
                            error << "Unknown face number of entries data type \"" << numFaceEntryTypeStr << "\"";
                            throw Exception( error.str() );
                        }
                        _numFaceEntryType = numFaceEntryTypeIter->second;
                        
                        
                        DataTypeStringMap::const_iterator faceEntryDataTypeIter = _dataTypeStringMap.find( faceEntryDataTypeStr );
                        if ( faceEntryDataTypeIter == _dataTypeStringMap.end() )
                        {
                            file.close();
                            std::stringstream error;
                            error << "Unknown face vertex index data type \"" << faceEntryDataTypeStr << "\"";
                            throw Exception( error.str() );
                        }
                        _faceEntryDataType = faceEntryDataTypeIter->second;
                        
                        if ( faceEntryDataStr != "vertex_index" && faceEntryDataStr != "vertex_indices" )
                        {
                            file.close();
                            std::stringstream error;
                            error << "Unknown face entry data \"" << faceEntryDataStr << "\"";
                            throw Exception( error.str() );
                        }
                        _faceEntryData = VERTEX_INDEX;
                        
                        readState = COMPONENT_CHECKING;
                    }
                }
                else
                {                    
                    file.close();
                    std::stringstream error;
                    error << "Unexpected component \"" << str << "\", property expected for face element";
                    throw Exception( error.str() );   
                }
                break;
            }
            case END_HEADER:
            {
                break;
            }
        } // switch
    } // while
    
    
    
    // Now allocate memory and read the list of vertices
    _numVertexBytes = 0;   // Number of bytes for a vertex
    for ( VertexPropertyTypeVector::const_iterator iter = _vertexPropertyTypeVector.begin();
         iter != _vertexPropertyTypeVector.end();
         ++iter )
    {
        const VertexPropertyType &vpt = *iter;
        _numVertexBytes += getDataTypeSize( vpt.type );
    }
    
    _vertexData = new unsigned char[_numVertexBytes*_numVertices];
    
    for ( unsigned int vertexID = 0; vertexID < _numVertices; vertexID++ )
    {
        unsigned char *ptr = &( _vertexData[vertexID*_numVertexBytes] );
        for ( VertexPropertyTypeVector::const_iterator iter = _vertexPropertyTypeVector.begin();
             iter != _vertexPropertyTypeVector.end();
             ++iter )
        {
            const VertexPropertyType &vpt = *iter;
            
            readData( vpt.type, file, ptr );
            ptr += getDataTypeSize( vpt.type );
        }
        
    }
    
    // Now allocate memory and read in faces
    file >> _numFaceEntry;
    _numFaceBytes = _numFaceEntry*getDataTypeSize( _faceEntryDataType );
    
    _faceData = new unsigned char[_numFaceBytes*_numFaces];
    
    bool begin = true;
    for ( unsigned int faceID = 0; faceID < _numFaces; faceID++ )
    {
        if ( !begin )
        {
            file >> _numFaceEntry;
        }
        else
            begin = false;
        
        unsigned char *ptr = &( _faceData[faceID*_numFaceBytes] );
        for ( unsigned int i = 0; i < _numFaceEntry; i++ )
        {
            readData( _faceEntryDataType, file,  ptr );
            ptr += getDataTypeSize( _faceEntryDataType );
        }
    }

    
    for ( unsigned int faceID = 0; faceID < _numFaces; faceID++ )
    {
        unsigned char *ptr = &( _faceData[faceID*_numFaceBytes] );
        //std::cout << _numFaceEntry << " ";
        for ( unsigned int i = 0; i < _numFaceEntry; i++ )
        {
            unsigned int val = getValue<unsigned int>( _faceEntryDataType, ptr );
            ptr += getDataTypeSize( _faceEntryDataType );
            //std::cout << val << " ";
        }
        //std::cout << std::endl;
    }
    
    
    
}


void PLYData::readData( DataType type, std::ifstream &file, unsigned char *ptr )
{
    switch ( type )
    {                    
        case CHAR:
        case INT8:
        {
            char data;
            char *dataPtr = reinterpret_cast<char*> ( ptr );
            file >> data;
            *dataPtr = data;
            break;
        }
        case UCHAR:
        case UINT8:
        {
            unsigned char data;
            unsigned char *dataPtr = reinterpret_cast<unsigned char*> ( ptr );
            file >> data;
            *dataPtr = data;
            break;
        }
        case SHORT:
        case INT16:
        {
            short data;
            short *dataPtr = reinterpret_cast<short*> ( ptr );
            file >> data;
            *dataPtr = data;
            break;
        }
        case USHORT:
        case UINT16:
        {
            unsigned short data;
            unsigned short *dataPtr = reinterpret_cast<unsigned short*> ( ptr );
            file >> data;
            *dataPtr = data;
            break;
        }
        case INT:
        case INT32:
        {
            int data;
            int *dataPtr = reinterpret_cast<int*> ( ptr );
            file >> data;
            *dataPtr = data;
            break;
        }
        case UINT:
        case UINT32:
        {                    
            unsigned int data;
            unsigned int *dataPtr = reinterpret_cast<unsigned int*> ( ptr );
            file >> data;
            *dataPtr = data;
            break;
        }
        case FLOAT:
        case FLOAT32:
        {
            float data;
            float *dataPtr = reinterpret_cast<float*> ( ptr );
            file >> data;
            *dataPtr = data;
            break;
        }
        case DOUBLE:
        case FLOAT64:
        {                    
            double data;
            double *dataPtr = reinterpret_cast<double*> ( ptr );
            file >> data;
            *dataPtr = data;
            break;
        }
    }    
}


void PLYData::getVertexPoint( unsigned int vertexIndex, Point &point ) const
{
    unsigned char *ptr = &( _vertexData[vertexIndex*_numVertexBytes] );
    for ( VertexPropertyTypeVector::const_iterator iter = _vertexPropertyTypeVector.begin();
         iter != _vertexPropertyTypeVector.end();
         ++iter )
    {
        const VertexPropertyType &vpt = *iter;
        
        switch ( vpt.property )
        {
            case VERTEX_PROPERTY_X:
                point.x = getValue<float>( vpt.type, ptr );
                break;
            case VERTEX_PROPERTY_Y:
                point.y = getValue<float>( vpt.type, ptr );
                break;
            case VERTEX_PROPERTY_Z:
                point.z = getValue<float>( vpt.type, ptr );
                break;
            default:
                break;
        }
                
        
        ptr += getDataTypeSize( vpt.type );
    }
}


void PLYData::getFaceIndices( unsigned int faceIndex, vec3ui &indices ) const
{
	unsigned char *ptr = &( _faceData[faceIndex*_numFaceBytes] );

	for ( unsigned int i = 0; i < _numFaceEntry; i++ )
	{
		unsigned int val = getValue<unsigned int>( _faceEntryDataType, ptr );
		ptr += getDataTypeSize( _faceEntryDataType );
		indices[i] = val;
	}

}

GRAPHICSLAB_NAMESPACE_END

