cmake_minimum_required(VERSION 2.6)
# 
# Name the project
PROJECT(AppCG2010)
# Tell CMake to process the sub-directories
add_subdirectory(Intro)
add_subdirectory(ShootingArena)
add_subdirectory(End)

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

SET(BULLET_PHYSICS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/bullet-2.76)


LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/End/ParticleLib ${BULLET_PHYSICS_SOURCE_DIR}/src/BulletCollision
${BULLET_PHYSICS_SOURCE_DIR}/src/BulletDynamics
${BULLET_PHYSICS_SOURCE_DIR}/src/LinearMath
${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL)

include_directories(${PROJECT_SOURCE_DIR}/End/Particle
${PROJECT_SOURCE_DIR}/End 
${PROJECT_SOURCE_DIR}/Intro/include
${PROJECT_SOURCE_DIR}/ShootingArena 
${BULLET_PHYSICS_SOURCE_DIR}/src 
${BULLET_PHYSICS_SOURCE_DIR}/Demos/OpenGL 
)

aux_source_directory(${PROJECT_SOURCE_DIR}/Intro/src IntroSources)
aux_source_directory(${PROJECT_SOURCE_DIR}/ShootingArena ArenaSources)
SET(EndSources ${PROJECT_SOURCE_DIR}/End/End.cpp)
 
#LINK_LIBRARIES(
#OpenGLSupport  
#BulletDynamics
#BulletCollision
#LinearMath
#GLU
#glut
#alut
#Particle 
#)

SET(Libraries
 GL
 GLU
 glut 
 alut
 m
 pthread
 Xmu
 X11
 Xext
 Xi
 Particle
 OpenGLSupport  
 BulletDynamics
 BulletCollision
 LinearMath
)

ADD_EXECUTABLE( AppCGFinal 
${IntroSources}
${ArenaSources} 
${EndSources} 
main.cpp 
)

TARGET_LINK_LIBRARIES(AppCGFinal ${Libraries})




