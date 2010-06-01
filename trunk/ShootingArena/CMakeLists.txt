# This is basically the overall name of the project in Visual Studio this is the name of the Solution File


# For every executable you have with a main method you should have an add_executable line below.
# For every add executable line you should list every .cpp and .h file you have associated with that executable.  


# You shouldn't have to modify anything below this line 
########################################################
cmake_minimum_required(VERSION 2.6)
PROJECT(SHOOTINGARENA)
SET(CMAKE_VERBOSE_MAKEFILE off)
SET(CMAKE_CXX_COMPILER g++)
SET(CMAKE_C_COMPILER g++)
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)
SET(CMAKE_USE_RELATIVE_PATHS on)

SET (CMAKE_BUILD_TYPE Release)

SET(CMAKE_C_FLAGS_DEBUG "-Wall")
SET(CMAKE_C_FLAGS_RELEASE "-O3 -ffast-math -Wall")
SET(CMAKE_CXX_FLAGS_DEBUG "-Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math -Wall")

SET(BULLET_PHYSICS_SOURCE_DIR ../../bullet-2.76)

LINK_DIRECTORIES(${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision
${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics
${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath
${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL
../End/ParticleLib
../End/Particle
)

INCLUDE_DIRECTORIES(
${BULLET_PHYSICS_SOURCE_DIR}/src 
${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL 
)

LINK_LIBRARIES(
	OpenGLSupport  
BulletDynamics  BulletCollision LinearMath GLU glut alut Particle 
	)

ADD_EXECUTABLE(AppShootingDemo
		main.cpp
		ShootingDemo.cpp 
		ShootingDemo.h
		soundClass.hpp
		soundClass.cpp
		Application.h
		Application.cpp
		GlutApplication.h
		GlutApplication.cpp
		ShapeDrawer.h
		ShapeDrawer.cpp
		GlutStuffs.h
		GlutStuffs.cpp
		tga.h
		tga.c
		material.hpp
		material.cpp
		Example.cpp
	)

SET_TARGET_PROPERTIES(AppShootingDemo PROPERTIES  DEBUG_POSTFIX "_Debug")
SET_TARGET_PROPERTIES(AppShootingDemo PROPERTIES  MINSIZEREL_POSTFIX "_MinsizeRel")
SET_TARGET_PROPERTIES(AppShootingDemo PROPERTIES  RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")

TARGET_LINK_LIBRARIES(AppShootingDemo glut)
