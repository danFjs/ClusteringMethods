# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/d/stuff/G-means/G-means/include/pyclustering/ccore

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/d/stuff/G-means/G-means/include/pc_build

# Include any dependencies generated for this target.
include bvt/CMakeFiles/bvt-static.dir/depend.make

# Include the progress variables for this target.
include bvt/CMakeFiles/bvt-static.dir/progress.make

# Include the compile flags for this target's objects.
include bvt/CMakeFiles/bvt-static.dir/flags.make

bvt/CMakeFiles/bvt-static.dir/static-test.cpp.o: bvt/CMakeFiles/bvt-static.dir/flags.make
bvt/CMakeFiles/bvt-static.dir/static-test.cpp.o: /home/d/stuff/G-means/G-means/include/pyclustering/ccore/bvt/static-test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/d/stuff/G-means/G-means/include/pc_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bvt/CMakeFiles/bvt-static.dir/static-test.cpp.o"
	cd /home/d/stuff/G-means/G-means/include/pc_build/bvt && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bvt-static.dir/static-test.cpp.o -c /home/d/stuff/G-means/G-means/include/pyclustering/ccore/bvt/static-test.cpp

bvt/CMakeFiles/bvt-static.dir/static-test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bvt-static.dir/static-test.cpp.i"
	cd /home/d/stuff/G-means/G-means/include/pc_build/bvt && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/d/stuff/G-means/G-means/include/pyclustering/ccore/bvt/static-test.cpp > CMakeFiles/bvt-static.dir/static-test.cpp.i

bvt/CMakeFiles/bvt-static.dir/static-test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bvt-static.dir/static-test.cpp.s"
	cd /home/d/stuff/G-means/G-means/include/pc_build/bvt && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/d/stuff/G-means/G-means/include/pyclustering/ccore/bvt/static-test.cpp -o CMakeFiles/bvt-static.dir/static-test.cpp.s

# Object files for target bvt-static
bvt__static_OBJECTS = \
"CMakeFiles/bvt-static.dir/static-test.cpp.o"

# External object files for target bvt-static
bvt__static_EXTERNAL_OBJECTS =

/home/d/stuff/G-means/G-means/include/pyclustering/ccore/build/bvt-static: bvt/CMakeFiles/bvt-static.dir/static-test.cpp.o
/home/d/stuff/G-means/G-means/include/pyclustering/ccore/build/bvt-static: bvt/CMakeFiles/bvt-static.dir/build.make
/home/d/stuff/G-means/G-means/include/pyclustering/ccore/build/bvt-static: /home/d/stuff/G-means/G-means/include/pyclustering/ccore/build/libpyclustering-static.a
/home/d/stuff/G-means/G-means/include/pyclustering/ccore/build/bvt-static: bvt/CMakeFiles/bvt-static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/d/stuff/G-means/G-means/include/pc_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/d/stuff/G-means/G-means/include/pyclustering/ccore/build/bvt-static"
	cd /home/d/stuff/G-means/G-means/include/pc_build/bvt && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bvt-static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bvt/CMakeFiles/bvt-static.dir/build: /home/d/stuff/G-means/G-means/include/pyclustering/ccore/build/bvt-static

.PHONY : bvt/CMakeFiles/bvt-static.dir/build

bvt/CMakeFiles/bvt-static.dir/clean:
	cd /home/d/stuff/G-means/G-means/include/pc_build/bvt && $(CMAKE_COMMAND) -P CMakeFiles/bvt-static.dir/cmake_clean.cmake
.PHONY : bvt/CMakeFiles/bvt-static.dir/clean

bvt/CMakeFiles/bvt-static.dir/depend:
	cd /home/d/stuff/G-means/G-means/include/pc_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/d/stuff/G-means/G-means/include/pyclustering/ccore /home/d/stuff/G-means/G-means/include/pyclustering/ccore/bvt /home/d/stuff/G-means/G-means/include/pc_build /home/d/stuff/G-means/G-means/include/pc_build/bvt /home/d/stuff/G-means/G-means/include/pc_build/bvt/CMakeFiles/bvt-static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bvt/CMakeFiles/bvt-static.dir/depend
