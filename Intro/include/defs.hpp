/**
 * defs.hpp
 *
 * Author   :   Fatih Erol
 * Date     :   24.02.2010
 *
 * All rights reserved.
 */

#ifndef GRAPHICSLAB_DEFS_HPP
#define GRAPHICSLAB_DEFS_HPP


#ifndef NULL
#define NULL 0
#endif


/** Namespace definitions */

#define GRAPHICSLAB_NAMESPACE_BEGIN \
namespace graphics_lab {

#define GRAPHICSLAB_NAMESPACE_END \
}

#define GRAPHICSLAB_NAMESPACE_QUALIFIER graphics_lab::
#define GRAPHICSLAB_NAMESPACE_USE using namespace graphics_lab;

/** Typedefs for shortcuts to common types */
typedef unsigned int uint;
typedef unsigned char uchar;



#endif  //  GRAPHICSLAB_DEFS_HPP


