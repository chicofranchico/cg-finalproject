# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/cmake-gui

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/juanpi/Desktop/Computer Graphics Lab/Final Project/ShootingArena"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/juanpi/Desktop/Computer Graphics Lab/Final Project/ShootingArena"

# Include any dependencies generated for this target.
include CMakeFiles/AppShootingDemo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AppShootingDemo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AppShootingDemo.dir/flags.make

CMakeFiles/AppShootingDemo.dir/main.cpp.o: CMakeFiles/AppShootingDemo.dir/flags.make
CMakeFiles/AppShootingDemo.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/juanpi/Desktop/Computer Graphics Lab/Final Project/ShootingArena/CMakeFiles" $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/AppShootingDemo.dir/main.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppShootingDemo.dir/main.cpp.o -c main.cpp

CMakeFiles/AppShootingDemo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppShootingDemo.dir/main.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E main.cpp > CMakeFiles/AppShootingDemo.dir/main.cpp.i

CMakeFiles/AppShootingDemo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppShootingDemo.dir/main.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S main.cpp -o CMakeFiles/AppShootingDemo.dir/main.cpp.s

CMakeFiles/AppShootingDemo.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/AppShootingDemo.dir/main.cpp.o.requires

CMakeFiles/AppShootingDemo.dir/main.cpp.o.provides: CMakeFiles/AppShootingDemo.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/AppShootingDemo.dir/build.make CMakeFiles/AppShootingDemo.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/AppShootingDemo.dir/main.cpp.o.provides

CMakeFiles/AppShootingDemo.dir/main.cpp.o.provides.build: CMakeFiles/AppShootingDemo.dir/main.cpp.o
.PHONY : CMakeFiles/AppShootingDemo.dir/main.cpp.o.provides.build

CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o: CMakeFiles/AppShootingDemo.dir/flags.make
CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o: ShootingDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report "/home/juanpi/Desktop/Computer Graphics Lab/Final Project/ShootingArena/CMakeFiles" $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o"
	g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o -c ShootingDemo.cpp

CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.i"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -E ShootingDemo.cpp > CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.i

CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.s"
	g++  $(CXX_DEFINES) $(CXX_FLAGS) -S ShootingDemo.cpp -o CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.s

CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o.requires:
.PHONY : CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o.requires

CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o.provides: CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o.requires
	$(MAKE) -f CMakeFiles/AppShootingDemo.dir/build.make CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o.provides.build
.PHONY : CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o.provides

CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o.provides.build: CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o
.PHONY : CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o.provides.build

# Object files for target AppShootingDemo
AppShootingDemo_OBJECTS = \
"CMakeFiles/AppShootingDemo.dir/main.cpp.o" \
"CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o"

# External object files for target AppShootingDemo
AppShootingDemo_EXTERNAL_OBJECTS =

AppShootingDemo: CMakeFiles/AppShootingDemo.dir/main.cpp.o
AppShootingDemo: CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o
AppShootingDemo: CMakeFiles/AppShootingDemo.dir/build.make
AppShootingDemo: CMakeFiles/AppShootingDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppShootingDemo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AppShootingDemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AppShootingDemo.dir/build: AppShootingDemo
.PHONY : CMakeFiles/AppShootingDemo.dir/build

CMakeFiles/AppShootingDemo.dir/requires: CMakeFiles/AppShootingDemo.dir/main.cpp.o.requires
CMakeFiles/AppShootingDemo.dir/requires: CMakeFiles/AppShootingDemo.dir/ShootingDemo.cpp.o.requires
.PHONY : CMakeFiles/AppShootingDemo.dir/requires

CMakeFiles/AppShootingDemo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AppShootingDemo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AppShootingDemo.dir/clean

CMakeFiles/AppShootingDemo.dir/depend:
	cd "/home/juanpi/Desktop/Computer Graphics Lab/Final Project/ShootingArena" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/juanpi/Desktop/Computer Graphics Lab/Final Project/ShootingArena" "/home/juanpi/Desktop/Computer Graphics Lab/Final Project/ShootingArena" "/home/juanpi/Desktop/Computer Graphics Lab/Final Project/ShootingArena" "/home/juanpi/Desktop/Computer Graphics Lab/Final Project/ShootingArena" "/home/juanpi/Desktop/Computer Graphics Lab/Final Project/ShootingArena/CMakeFiles/AppShootingDemo.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/AppShootingDemo.dir/depend
