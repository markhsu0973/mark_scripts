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
CMAKE_SOURCE_DIR = /home/mark/mark_scripts/cpp_practice/serial

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/mark_scripts/cpp_practice/serial/build

# Include any dependencies generated for this target.
include CMakeFiles/prac.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/prac.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prac.dir/flags.make

CMakeFiles/prac.dir/src/prac.cpp.o: CMakeFiles/prac.dir/flags.make
CMakeFiles/prac.dir/src/prac.cpp.o: ../src/prac.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/mark_scripts/cpp_practice/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/prac.dir/src/prac.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prac.dir/src/prac.cpp.o -c /home/mark/mark_scripts/cpp_practice/serial/src/prac.cpp

CMakeFiles/prac.dir/src/prac.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prac.dir/src/prac.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/mark_scripts/cpp_practice/serial/src/prac.cpp > CMakeFiles/prac.dir/src/prac.cpp.i

CMakeFiles/prac.dir/src/prac.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prac.dir/src/prac.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/mark_scripts/cpp_practice/serial/src/prac.cpp -o CMakeFiles/prac.dir/src/prac.cpp.s

CMakeFiles/prac.dir/src/prac.cpp.o.requires:

.PHONY : CMakeFiles/prac.dir/src/prac.cpp.o.requires

CMakeFiles/prac.dir/src/prac.cpp.o.provides: CMakeFiles/prac.dir/src/prac.cpp.o.requires
	$(MAKE) -f CMakeFiles/prac.dir/build.make CMakeFiles/prac.dir/src/prac.cpp.o.provides.build
.PHONY : CMakeFiles/prac.dir/src/prac.cpp.o.provides

CMakeFiles/prac.dir/src/prac.cpp.o.provides.build: CMakeFiles/prac.dir/src/prac.cpp.o


# Object files for target prac
prac_OBJECTS = \
"CMakeFiles/prac.dir/src/prac.cpp.o"

# External object files for target prac
prac_EXTERNAL_OBJECTS =

prac: CMakeFiles/prac.dir/src/prac.cpp.o
prac: CMakeFiles/prac.dir/build.make
prac: CMakeFiles/prac.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/mark_scripts/cpp_practice/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable prac"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prac.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prac.dir/build: prac

.PHONY : CMakeFiles/prac.dir/build

CMakeFiles/prac.dir/requires: CMakeFiles/prac.dir/src/prac.cpp.o.requires

.PHONY : CMakeFiles/prac.dir/requires

CMakeFiles/prac.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prac.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prac.dir/clean

CMakeFiles/prac.dir/depend:
	cd /home/mark/mark_scripts/cpp_practice/serial/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/mark_scripts/cpp_practice/serial /home/mark/mark_scripts/cpp_practice/serial /home/mark/mark_scripts/cpp_practice/serial/build /home/mark/mark_scripts/cpp_practice/serial/build /home/mark/mark_scripts/cpp_practice/serial/build/CMakeFiles/prac.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/prac.dir/depend

