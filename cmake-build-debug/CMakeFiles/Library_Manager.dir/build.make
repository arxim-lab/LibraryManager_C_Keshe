# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /var/workspace/Library_Manager

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /var/workspace/Library_Manager/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Library_Manager.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Library_Manager.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Library_Manager.dir/flags.make

CMakeFiles/Library_Manager.dir/main.c.o: CMakeFiles/Library_Manager.dir/flags.make
CMakeFiles/Library_Manager.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/var/workspace/Library_Manager/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Library_Manager.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Library_Manager.dir/main.c.o -c /var/workspace/Library_Manager/main.c

CMakeFiles/Library_Manager.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Library_Manager.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /var/workspace/Library_Manager/main.c > CMakeFiles/Library_Manager.dir/main.c.i

CMakeFiles/Library_Manager.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Library_Manager.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /var/workspace/Library_Manager/main.c -o CMakeFiles/Library_Manager.dir/main.c.s

# Object files for target Library_Manager
Library_Manager_OBJECTS = \
"CMakeFiles/Library_Manager.dir/main.c.o"

# External object files for target Library_Manager
Library_Manager_EXTERNAL_OBJECTS =

Library_Manager: CMakeFiles/Library_Manager.dir/main.c.o
Library_Manager: CMakeFiles/Library_Manager.dir/build.make
Library_Manager: CMakeFiles/Library_Manager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/var/workspace/Library_Manager/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Library_Manager"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Library_Manager.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Library_Manager.dir/build: Library_Manager

.PHONY : CMakeFiles/Library_Manager.dir/build

CMakeFiles/Library_Manager.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Library_Manager.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Library_Manager.dir/clean

CMakeFiles/Library_Manager.dir/depend:
	cd /var/workspace/Library_Manager/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /var/workspace/Library_Manager /var/workspace/Library_Manager /var/workspace/Library_Manager/cmake-build-debug /var/workspace/Library_Manager/cmake-build-debug /var/workspace/Library_Manager/cmake-build-debug/CMakeFiles/Library_Manager.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Library_Manager.dir/depend

