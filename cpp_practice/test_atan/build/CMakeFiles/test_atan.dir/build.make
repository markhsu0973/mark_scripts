# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/mark/mark_scripts/cpp_practice/test_atan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/mark_scripts/cpp_practice/test_atan/build

# Include any dependencies generated for this target.
include CMakeFiles/test_atan.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_atan.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_atan.dir/flags.make

CMakeFiles/test_atan.dir/src/atan.cpp.o: CMakeFiles/test_atan.dir/flags.make
CMakeFiles/test_atan.dir/src/atan.cpp.o: ../src/atan.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/mark_scripts/cpp_practice/test_atan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_atan.dir/src/atan.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_atan.dir/src/atan.cpp.o -c /home/mark/mark_scripts/cpp_practice/test_atan/src/atan.cpp

CMakeFiles/test_atan.dir/src/atan.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_atan.dir/src/atan.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/mark_scripts/cpp_practice/test_atan/src/atan.cpp > CMakeFiles/test_atan.dir/src/atan.cpp.i

CMakeFiles/test_atan.dir/src/atan.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_atan.dir/src/atan.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/mark_scripts/cpp_practice/test_atan/src/atan.cpp -o CMakeFiles/test_atan.dir/src/atan.cpp.s

CMakeFiles/test_atan.dir/src/atan.cpp.o.requires:

.PHONY : CMakeFiles/test_atan.dir/src/atan.cpp.o.requires

CMakeFiles/test_atan.dir/src/atan.cpp.o.provides: CMakeFiles/test_atan.dir/src/atan.cpp.o.requires
	$(MAKE) -f CMakeFiles/test_atan.dir/build.make CMakeFiles/test_atan.dir/src/atan.cpp.o.provides.build
.PHONY : CMakeFiles/test_atan.dir/src/atan.cpp.o.provides

CMakeFiles/test_atan.dir/src/atan.cpp.o.provides.build: CMakeFiles/test_atan.dir/src/atan.cpp.o


# Object files for target test_atan
test_atan_OBJECTS = \
"CMakeFiles/test_atan.dir/src/atan.cpp.o"

# External object files for target test_atan
test_atan_EXTERNAL_OBJECTS =

test_atan: CMakeFiles/test_atan.dir/src/atan.cpp.o
test_atan: CMakeFiles/test_atan.dir/build.make
test_atan: CMakeFiles/test_atan.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/mark_scripts/cpp_practice/test_atan/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_atan"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_atan.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_atan.dir/build: test_atan

.PHONY : CMakeFiles/test_atan.dir/build

CMakeFiles/test_atan.dir/requires: CMakeFiles/test_atan.dir/src/atan.cpp.o.requires

.PHONY : CMakeFiles/test_atan.dir/requires

CMakeFiles/test_atan.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_atan.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_atan.dir/clean

CMakeFiles/test_atan.dir/depend:
	cd /home/mark/mark_scripts/cpp_practice/test_atan/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/mark_scripts/cpp_practice/test_atan /home/mark/mark_scripts/cpp_practice/test_atan /home/mark/mark_scripts/cpp_practice/test_atan/build /home/mark/mark_scripts/cpp_practice/test_atan/build /home/mark/mark_scripts/cpp_practice/test_atan/build/CMakeFiles/test_atan.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_atan.dir/depend

