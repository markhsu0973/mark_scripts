# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/mark/mark_scripts/cpp_practice/least_squares

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/mark_scripts/cpp_practice/least_squares/build

# Include any dependencies generated for this target.
include CMakeFiles/least_squares.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/least_squares.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/least_squares.dir/flags.make

CMakeFiles/least_squares.dir/src/least_squares.cpp.o: CMakeFiles/least_squares.dir/flags.make
CMakeFiles/least_squares.dir/src/least_squares.cpp.o: ../src/least_squares.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/mark_scripts/cpp_practice/least_squares/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/least_squares.dir/src/least_squares.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/least_squares.dir/src/least_squares.cpp.o -c /home/mark/mark_scripts/cpp_practice/least_squares/src/least_squares.cpp

CMakeFiles/least_squares.dir/src/least_squares.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/least_squares.dir/src/least_squares.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/mark_scripts/cpp_practice/least_squares/src/least_squares.cpp > CMakeFiles/least_squares.dir/src/least_squares.cpp.i

CMakeFiles/least_squares.dir/src/least_squares.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/least_squares.dir/src/least_squares.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/mark_scripts/cpp_practice/least_squares/src/least_squares.cpp -o CMakeFiles/least_squares.dir/src/least_squares.cpp.s

CMakeFiles/least_squares.dir/src/least_squares.cpp.o.requires:

.PHONY : CMakeFiles/least_squares.dir/src/least_squares.cpp.o.requires

CMakeFiles/least_squares.dir/src/least_squares.cpp.o.provides: CMakeFiles/least_squares.dir/src/least_squares.cpp.o.requires
	$(MAKE) -f CMakeFiles/least_squares.dir/build.make CMakeFiles/least_squares.dir/src/least_squares.cpp.o.provides.build
.PHONY : CMakeFiles/least_squares.dir/src/least_squares.cpp.o.provides

CMakeFiles/least_squares.dir/src/least_squares.cpp.o.provides.build: CMakeFiles/least_squares.dir/src/least_squares.cpp.o


# Object files for target least_squares
least_squares_OBJECTS = \
"CMakeFiles/least_squares.dir/src/least_squares.cpp.o"

# External object files for target least_squares
least_squares_EXTERNAL_OBJECTS =

least_squares: CMakeFiles/least_squares.dir/src/least_squares.cpp.o
least_squares: CMakeFiles/least_squares.dir/build.make
least_squares: CMakeFiles/least_squares.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/mark_scripts/cpp_practice/least_squares/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable least_squares"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/least_squares.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/least_squares.dir/build: least_squares

.PHONY : CMakeFiles/least_squares.dir/build

CMakeFiles/least_squares.dir/requires: CMakeFiles/least_squares.dir/src/least_squares.cpp.o.requires

.PHONY : CMakeFiles/least_squares.dir/requires

CMakeFiles/least_squares.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/least_squares.dir/cmake_clean.cmake
.PHONY : CMakeFiles/least_squares.dir/clean

CMakeFiles/least_squares.dir/depend:
	cd /home/mark/mark_scripts/cpp_practice/least_squares/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/mark_scripts/cpp_practice/least_squares /home/mark/mark_scripts/cpp_practice/least_squares /home/mark/mark_scripts/cpp_practice/least_squares/build /home/mark/mark_scripts/cpp_practice/least_squares/build /home/mark/mark_scripts/cpp_practice/least_squares/build/CMakeFiles/least_squares.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/least_squares.dir/depend
