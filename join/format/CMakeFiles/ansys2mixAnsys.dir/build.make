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
include CMakeFiles/ansys2mixAnsys.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ansys2mixAnsys.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ansys2mixAnsys.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ansys2mixAnsys.dir/flags.make

CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.o: CMakeFiles/ansys2mixAnsys.dir/flags.make
CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.o: AnsysToMixAnsys.cpp
CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.o: CMakeFiles/ansys2mixAnsys.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joacaldo/memoria/join/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.o -MF CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.o.d -o CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.o -c /home/joacaldo/memoria/join/format/AnsysToMixAnsys.cpp

CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joacaldo/memoria/join/format/AnsysToMixAnsys.cpp > CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.i

CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joacaldo/memoria/join/format/AnsysToMixAnsys.cpp -o CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.s

# Object files for target ansys2mixAnsys
ansys2mixAnsys_OBJECTS = \
"CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.o"

# External object files for target ansys2mixAnsys
ansys2mixAnsys_EXTERNAL_OBJECTS = \
"/home/joacaldo/memoria/join/geometry/Point.o" \
"/home/joacaldo/memoria/join/geometry/Element.o" \
"/home/joacaldo/memoria/join/geometry/Hexahedra.o" \
"/home/joacaldo/memoria/join/geometry/Prism.o" \
"/home/joacaldo/memoria/join/geometry/Pyramid.o" \
"/home/joacaldo/memoria/join/geometry/Tetrahedra.o" \
"/home/joacaldo/memoria/join/geometry/Face.o" \
"/home/joacaldo/memoria/join/geometry/FaceContainer.o" \
"/home/joacaldo/memoria/join/read_write/ReadAnsys.o" \
"/home/joacaldo/memoria/join/read_write/AnsysFormat.o"

ansys2mixAnsys: CMakeFiles/ansys2mixAnsys.dir/AnsysToMixAnsys.cpp.o
ansys2mixAnsys: /home/joacaldo/memoria/join/geometry/Point.o
ansys2mixAnsys: /home/joacaldo/memoria/join/geometry/Element.o
ansys2mixAnsys: /home/joacaldo/memoria/join/geometry/Hexahedra.o
ansys2mixAnsys: /home/joacaldo/memoria/join/geometry/Prism.o
ansys2mixAnsys: /home/joacaldo/memoria/join/geometry/Pyramid.o
ansys2mixAnsys: /home/joacaldo/memoria/join/geometry/Tetrahedra.o
ansys2mixAnsys: /home/joacaldo/memoria/join/geometry/Face.o
ansys2mixAnsys: /home/joacaldo/memoria/join/geometry/FaceContainer.o
ansys2mixAnsys: /home/joacaldo/memoria/join/read_write/ReadAnsys.o
ansys2mixAnsys: /home/joacaldo/memoria/join/read_write/AnsysFormat.o
ansys2mixAnsys: CMakeFiles/ansys2mixAnsys.dir/build.make
ansys2mixAnsys: CMakeFiles/ansys2mixAnsys.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joacaldo/memoria/join/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ansys2mixAnsys"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ansys2mixAnsys.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ansys2mixAnsys.dir/build: ansys2mixAnsys
.PHONY : CMakeFiles/ansys2mixAnsys.dir/build

CMakeFiles/ansys2mixAnsys.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ansys2mixAnsys.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ansys2mixAnsys.dir/clean

CMakeFiles/ansys2mixAnsys.dir/depend:
	cd /home/joacaldo/memoria/join/format && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format/CMakeFiles/ansys2mixAnsys.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ansys2mixAnsys.dir/depend
