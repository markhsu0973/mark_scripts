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
CMAKE_SOURCE_DIR = /home/mark/test_include_c/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mark/test_include_c/build

# Include any dependencies generated for this target.
include app/CMakeFiles/app.dir/depend.make

# Include the progress variables for this target.
include app/CMakeFiles/app.dir/progress.make

# Include the compile flags for this target's objects.
include app/CMakeFiles/app.dir/flags.make

app/CMakeFiles/app.dir/main.c.o: app/CMakeFiles/app.dir/flags.make
app/CMakeFiles/app.dir/main.c.o: /home/mark/test_include_c/src/app/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mark/test_include_c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object app/CMakeFiles/app.dir/main.c.o"
	cd /home/mark/test_include_c/build/app && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/app.dir/main.c.o   -c /home/mark/test_include_c/src/app/main.c

app/CMakeFiles/app.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/app.dir/main.c.i"
	cd /home/mark/test_include_c/build/app && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mark/test_include_c/src/app/main.c > CMakeFiles/app.dir/main.c.i

app/CMakeFiles/app.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/app.dir/main.c.s"
	cd /home/mark/test_include_c/build/app && /usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mark/test_include_c/src/app/main.c -o CMakeFiles/app.dir/main.c.s

app/CMakeFiles/app.dir/main.c.o.requires:

.PHONY : app/CMakeFiles/app.dir/main.c.o.requires

app/CMakeFiles/app.dir/main.c.o.provides: app/CMakeFiles/app.dir/main.c.o.requires
	$(MAKE) -f app/CMakeFiles/app.dir/build.make app/CMakeFiles/app.dir/main.c.o.provides.build
.PHONY : app/CMakeFiles/app.dir/main.c.o.provides

app/CMakeFiles/app.dir/main.c.o.provides.build: app/CMakeFiles/app.dir/main.c.o


# Object files for target app
app_OBJECTS = \
"CMakeFiles/app.dir/main.c.o"

# External object files for target app
app_EXTERNAL_OBJECTS =

app/app: app/CMakeFiles/app.dir/main.c.o
app/app: app/CMakeFiles/app.dir/build.make
app/app: calc/libcalc.a
app/app: app/CMakeFiles/app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mark/test_include_c/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable app"
	cd /home/mark/test_include_c/build/app && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
app/CMakeFiles/app.dir/build: app/app

.PHONY : app/CMakeFiles/app.dir/build

app/CMakeFiles/app.dir/requires: app/CMakeFiles/app.dir/main.c.o.requires

.PHONY : app/CMakeFiles/app.dir/requires

app/CMakeFiles/app.dir/clean:
	cd /home/mark/test_include_c/build/app && $(CMAKE_COMMAND) -P CMakeFiles/app.dir/cmake_clean.cmake
.PHONY : app/CMakeFiles/app.dir/clean

app/CMakeFiles/app.dir/depend:
	cd /home/mark/test_include_c/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mark/test_include_c/src /home/mark/test_include_c/src/app /home/mark/test_include_c/build /home/mark/test_include_c/build/app /home/mark/test_include_c/build/app/CMakeFiles/app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : app/CMakeFiles/app.dir/depend

