cmake_minimum_required(VERSION 2.6)
# 
# Name the project
PROJECT(AppCG2010)
# Tell CMake to process the sub-directories
add_subdirectory(Intro)
add_subdirectory(ShootingArena)
add_subdirectory(End)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)
