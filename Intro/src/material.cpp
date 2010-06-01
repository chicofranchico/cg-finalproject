/**
 * material.cpp
 *
 * Author   :   Fatih Erol
 * Date     :   08.03.2010
 *
 * All rights reserved.
 */


// Class declaration include
#include "material.hpp"

GRAPHICSLAB_NAMESPACE_BEGIN

Material::Material() :
    _ambient( Color( 0.2, 0.2, 0.2, 1.0 ) ),
    _diffuse( Color( 0.8, 0.8, 0.8, 1.0 ) ),
    _specular( Color( 0.0, 0.0, 0.0, 1.0 ) ),
    _emission( Color( 0.0, 0.0, 0.0, 1.0 ) ),
    _shininess( 0 )
{
}

Material::~Material()
{
}

void Material::setActive( GLenum face ) const
{
    glMaterialfv( face, GL_AMBIENT, _ambient.array );
    glMaterialfv( face, GL_DIFFUSE, _diffuse.array );
    glMaterialfv( face, GL_SPECULAR, _specular.array );
    glMaterialfv( face, GL_EMISSION, _emission.array );
    
    glMaterialf( face, GL_SHININESS, _shininess );
}


GRAPHICSLAB_NAMESPACE_END

