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
CMAKE_SOURCE_DIR = /home/mark/mark_scripts/cpp_practice/thread

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/mark_scripts/cpp_practice/thread/build

# Include any dependencies generated for this target.
include CMakeFiles/thread_practice.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/thread_practice.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/thread_practice.dir/flags.make

CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o: CMakeFiles/thread_practice.dir/flags.make
CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o: ../src/thread_practice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/mark_scripts/cpp_practice/thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o -c /home/mark/mark_scripts/cpp_practice/thread/src/thread_practice.cpp

CMakeFiles/thread_practice.dir/src/thread_practice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/thread_practice.dir/src/thread_practice.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/mark_scripts/cpp_practice/thread/src/thread_practice.cpp > CMakeFiles/thread_practice.dir/src/thread_practice.cpp.i

CMakeFiles/thread_practice.dir/src/thread_practice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/thread_practice.dir/src/thread_practice.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/mark_scripts/cpp_practice/thread/src/thread_practice.cpp -o CMakeFiles/thread_practice.dir/src/thread_practice.cpp.s

CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o.requires:

.PHONY : CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o.requires

CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o.provides: CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o.requires
	$(MAKE) -f CMakeFiles/thread_practice.dir/build.make CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o.provides.build
.PHONY : CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o.provides

CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o.provides.build: CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o


# Object files for target thread_practice
thread_practice_OBJECTS = \
"CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o"

# External object files for target thread_practice
thread_practice_EXTERNAL_OBJECTS =

thread_practice: CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o
thread_practice: CMakeFiles/thread_practice.dir/build.make
thread_practice: CMakeFiles/thread_practice.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/mark_scripts/cpp_practice/thread/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable thread_practice"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/thread_practice.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/thread_practice.dir/build: thread_practice

.PHONY : CMakeFiles/thread_practice.dir/build

CMakeFiles/thread_practice.dir/requires: CMakeFiles/thread_practice.dir/src/thread_practice.cpp.o.requires

.PHONY : CMakeFiles/thread_practice.dir/requires

CMakeFiles/thread_practice.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/thread_practice.dir/cmake_clean.cmake
.PHONY : CMakeFiles/thread_practice.dir/clean

CMakeFiles/thread_practice.dir/depend:
	cd /home/mark/mark_scripts/cpp_practice/thread/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/mark_scripts/cpp_practice/thread /home/mark/mark_scripts/cpp_practice/thread /home/mark/mark_scripts/cpp_practice/thread/build /home/mark/mark_scripts/cpp_practice/thread/build /home/mark/mark_scripts/cpp_practice/thread/build/CMakeFiles/thread_practice.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/thread_practice.dir/depend

