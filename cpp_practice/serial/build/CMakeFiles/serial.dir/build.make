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
include CMakeFiles/serial.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/serial.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serial.dir/flags.make

CMakeFiles/serial.dir/src/Serial_TX.cpp.o: CMakeFiles/serial.dir/flags.make
CMakeFiles/serial.dir/src/Serial_TX.cpp.o: ../src/Serial_TX.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/mark_scripts/cpp_practice/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/serial.dir/src/Serial_TX.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/serial.dir/src/Serial_TX.cpp.o -c /home/mark/mark_scripts/cpp_practice/serial/src/Serial_TX.cpp

CMakeFiles/serial.dir/src/Serial_TX.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/serial.dir/src/Serial_TX.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mark/mark_scripts/cpp_practice/serial/src/Serial_TX.cpp > CMakeFiles/serial.dir/src/Serial_TX.cpp.i

CMakeFiles/serial.dir/src/Serial_TX.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/serial.dir/src/Serial_TX.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mark/mark_scripts/cpp_practice/serial/src/Serial_TX.cpp -o CMakeFiles/serial.dir/src/Serial_TX.cpp.s

CMakeFiles/serial.dir/src/Serial_TX.cpp.o.requires:

.PHONY : CMakeFiles/serial.dir/src/Serial_TX.cpp.o.requires

CMakeFiles/serial.dir/src/Serial_TX.cpp.o.provides: CMakeFiles/serial.dir/src/Serial_TX.cpp.o.requires
	$(MAKE) -f CMakeFiles/serial.dir/build.make CMakeFiles/serial.dir/src/Serial_TX.cpp.o.provides.build
.PHONY : CMakeFiles/serial.dir/src/Serial_TX.cpp.o.provides

CMakeFiles/serial.dir/src/Serial_TX.cpp.o.provides.build: CMakeFiles/serial.dir/src/Serial_TX.cpp.o


# Object files for target serial
serial_OBJECTS = \
"CMakeFiles/serial.dir/src/Serial_TX.cpp.o"

# External object files for target serial
serial_EXTERNAL_OBJECTS =

serial: CMakeFiles/serial.dir/src/Serial_TX.cpp.o
serial: CMakeFiles/serial.dir/build.make
serial: CMakeFiles/serial.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/mark_scripts/cpp_practice/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable serial"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serial.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serial.dir/build: serial

.PHONY : CMakeFiles/serial.dir/build

CMakeFiles/serial.dir/requires: CMakeFiles/serial.dir/src/Serial_TX.cpp.o.requires

.PHONY : CMakeFiles/serial.dir/requires

CMakeFiles/serial.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serial.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serial.dir/clean

CMakeFiles/serial.dir/depend:
	cd /home/mark/mark_scripts/cpp_practice/serial/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/mark_scripts/cpp_practice/serial /home/mark/mark_scripts/cpp_practice/serial /home/mark/mark_scripts/cpp_practice/serial/build /home/mark/mark_scripts/cpp_practice/serial/build /home/mark/mark_scripts/cpp_practice/serial/build/CMakeFiles/serial.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serial.dir/depend

