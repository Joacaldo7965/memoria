# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/joacaldo/memoria/join/format

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joacaldo/memoria/join/format

# Include any dependencies generated for this target.
include CMakeFiles/joinoff.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/joinoff.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/joinoff.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/joinoff.dir/flags.make

CMakeFiles/joinoff.dir/JoinOff.cpp.o: CMakeFiles/joinoff.dir/flags.make
CMakeFiles/joinoff.dir/JoinOff.cpp.o: JoinOff.cpp
CMakeFiles/joinoff.dir/JoinOff.cpp.o: CMakeFiles/joinoff.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joacaldo/memoria/join/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/joinoff.dir/JoinOff.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/joinoff.dir/JoinOff.cpp.o -MF CMakeFiles/joinoff.dir/JoinOff.cpp.o.d -o CMakeFiles/joinoff.dir/JoinOff.cpp.o -c /home/joacaldo/memoria/join/format/JoinOff.cpp

CMakeFiles/joinoff.dir/JoinOff.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joinoff.dir/JoinOff.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joacaldo/memoria/join/format/JoinOff.cpp > CMakeFiles/joinoff.dir/JoinOff.cpp.i

CMakeFiles/joinoff.dir/JoinOff.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joinoff.dir/JoinOff.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joacaldo/memoria/join/format/JoinOff.cpp -o CMakeFiles/joinoff.dir/JoinOff.cpp.s

# Object files for target joinoff
joinoff_OBJECTS = \
"CMakeFiles/joinoff.dir/JoinOff.cpp.o"

# External object files for target joinoff
joinoff_EXTERNAL_OBJECTS = \
"/home/joacaldo/memoria/join/geometry/Point.o" \
"/home/joacaldo/memoria/join/geometry/Face.o" \
"/home/joacaldo/memoria/join/geometry/FaceContainer.o" \
"/home/joacaldo/memoria/join/read_write/ReadOff.o" \
"/home/joacaldo/memoria/join/read_write/WriteOff.o"

joinoff: CMakeFiles/joinoff.dir/JoinOff.cpp.o
joinoff: /home/joacaldo/memoria/join/geometry/Point.o
joinoff: /home/joacaldo/memoria/join/geometry/Face.o
joinoff: /home/joacaldo/memoria/join/geometry/FaceContainer.o
joinoff: /home/joacaldo/memoria/join/read_write/ReadOff.o
joinoff: /home/joacaldo/memoria/join/read_write/WriteOff.o
joinoff: CMakeFiles/joinoff.dir/build.make
joinoff: CMakeFiles/joinoff.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joacaldo/memoria/join/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable joinoff"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/joinoff.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/joinoff.dir/build: joinoff
.PHONY : CMakeFiles/joinoff.dir/build

CMakeFiles/joinoff.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/joinoff.dir/cmake_clean.cmake
.PHONY : CMakeFiles/joinoff.dir/clean

CMakeFiles/joinoff.dir/depend:
	cd /home/joacaldo/memoria/join/format && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format/CMakeFiles/joinoff.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/joinoff.dir/depend
