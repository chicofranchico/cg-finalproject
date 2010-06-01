cmake_minimum_required(VERSION 2.6)
PROJECT(Intro)
SET(CMAKE_VERBOSE_MAKEFILE on)
SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_C_COMPILER g++)
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
SET(CMAKE_USE_RELATIVE_PATHS on)

SET (CMAKE_BUILD_TYPE Release)

SET(CMAKE_C_FLAGS_DEBUG "-Wall")
SET(CMAKE_C_FLAGS_RELEASE "-O3 -ffast-math -Wall")
SET(CMAKE_CXX_FLAGS_DEBUG "-Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math -Wall")


INCLUDE_DIRECTORIES(./include)

SET(Libraries
 GL
 GLU
 glut 
 alut
 m
 pthread 
 )
SET(Headers
include/defs.hpp
include/opengl_includes.hpp
include/exception.hpp
include/types.hpp
include/vector.hpp
include/utils.hpp
include/timer.hpp
include/keyboardEventHandler.hpp
include/mouseEventHandler.hpp
include/applicationParameters.hpp
include/window.hpp
include/scene.hpp
include/camera.hpp
include/camera2D.hpp
include/camera3D.hpp
include/material.hpp
include/texture.hpp
include/screenTexture.hpp
include/light.hpp
include/positionalLight.hpp
include/directionalLight.hpp
include/spotLight.hpp
include/drawable.hpp
include/text.hpp
include/plyData.hpp
include/plyModel.hpp
include/monitor.hpp
include/stage.hpp
include/text3d.h
include/soundClass.hpp
)
SET(Sources
src/main.cpp
src/types.cpp
src/utils.cpp
src/timer.cpp
src/applicationParameters.cpp
src/window.cpp
src/scene.cpp
src/camera.cpp
src/camera2D.cpp
src/camera3D.cpp
src/material.cpp
src/texture.cpp
src/screenTexture.cpp
src/light.cpp
src/positionalLight.cpp
src/directionalLight.cpp
src/spotLight.cpp
src/text.cpp
src/plyData.cpp
src/plyModel.cpp
src/monitor.cpp
src/stage.cpp
src/text3d.cpp
src/soundClass.cpp
)
ADD_EXECUTABLE( AppIntro 
 ${Headers}
 ${Sources}
)

TARGET_LINK_LIBRARIES(AppIntro ${Libraries})


