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
CMAKE_SOURCE_DIR = /home/mark/mark_scripts/cpp_practice/test_include

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/mark_scripts/cpp_practice/test_include/build

# Include any dependencies generated for this target.
include CMakeFiles/test_include_sub.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_include_sub.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_include_sub.dir/flags.make

CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o: CMakeFiles/test_include_sub.dir/flags.make
CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o: ../src/test_include_sub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/mark_scripts/cpp_practice/test_include/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o -c /home/mark/mark_scripts/cpp_practice/test_include/src/test_include_sub.cpp

CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/mark_scripts/cpp_practice/test_include/src/test_include_sub.cpp > CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.i

CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/mark_scripts/cpp_practice/test_include/src/test_include_sub.cpp -o CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.s

CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o.requires:

.PHONY : CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o.requires

CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o.provides: CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_include_sub.dir/build.make CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o.provides.build
.PHONY : CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o.provides

CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o.provides.build: CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o


# Object files for target test_include_sub
test_include_sub_OBJECTS = \
"CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o"

# External object files for target test_include_sub
test_include_sub_EXTERNAL_OBJECTS =

test_include_sub: CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o
test_include_sub: CMakeFiles/test_include_sub.dir/build.make
test_include_sub: CMakeFiles/test_include_sub.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/mark_scripts/cpp_practice/test_include/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_include_sub"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_include_sub.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_include_sub.dir/build: test_include_sub

.PHONY : CMakeFiles/test_include_sub.dir/build

CMakeFiles/test_include_sub.dir/requires: CMakeFiles/test_include_sub.dir/src/test_include_sub.cpp.o.requires

.PHONY : CMakeFiles/test_include_sub.dir/requires

CMakeFiles/test_include_sub.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_include_sub.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_include_sub.dir/clean

CMakeFiles/test_include_sub.dir/depend:
	cd /home/mark/mark_scripts/cpp_practice/test_include/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/mark_scripts/cpp_practice/test_include /home/mark/mark_scripts/cpp_practice/test_include /home/mark/mark_scripts/cpp_practice/test_include/build /home/mark/mark_scripts/cpp_practice/test_include/build /home/mark/mark_scripts/cpp_practice/test_include/build/CMakeFiles/test_include_sub.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_include_sub.dir/depend

