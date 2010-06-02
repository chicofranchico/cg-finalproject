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


include_directories(${PROJECT_SOURCE_DIR}/include)

SET(Libraries
 GL
 GLU
 glut 
 alut
 m
 pthread 
 )

aux_source_directory(${PROJECT_SOURCE_DIR}/src Sources)

ADD_EXECUTABLE( AppIntro ${Sources} main.cpp)

TARGET_LINK_LIBRARIES(AppIntro ${Libraries})

add_library(Intro STATIC ${Sources})

