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
include CMakeFiles/mdl2dolfinXML.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mdl2dolfinXML.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mdl2dolfinXML.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mdl2dolfinXML.dir/flags.make

CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.o: CMakeFiles/mdl2dolfinXML.dir/flags.make
CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.o: MdlToDolfinXML.cpp
CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.o: CMakeFiles/mdl2dolfinXML.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joacaldo/memoria/join/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.o -MF CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.o.d -o CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.o -c /home/joacaldo/memoria/join/format/MdlToDolfinXML.cpp

CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joacaldo/memoria/join/format/MdlToDolfinXML.cpp > CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.i

CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joacaldo/memoria/join/format/MdlToDolfinXML.cpp -o CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.s

# Object files for target mdl2dolfinXML
mdl2dolfinXML_OBJECTS = \
"CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.o"

# External object files for target mdl2dolfinXML
mdl2dolfinXML_EXTERNAL_OBJECTS = \
"/home/joacaldo/memoria/join/geometry/Point.o" \
"/home/joacaldo/memoria/join/geometry/Face.o" \
"/home/joacaldo/memoria/join/geometry/FaceContainer.o" \
"/home/joacaldo/memoria/join/read_write/ReadMdl.o" \
"/home/joacaldo/memoria/join/read_write/WriteDolfinTriangleXML.o"

mdl2dolfinXML: CMakeFiles/mdl2dolfinXML.dir/MdlToDolfinXML.cpp.o
mdl2dolfinXML: /home/joacaldo/memoria/join/geometry/Point.o
mdl2dolfinXML: /home/joacaldo/memoria/join/geometry/Face.o
mdl2dolfinXML: /home/joacaldo/memoria/join/geometry/FaceContainer.o
mdl2dolfinXML: /home/joacaldo/memoria/join/read_write/ReadMdl.o
mdl2dolfinXML: /home/joacaldo/memoria/join/read_write/WriteDolfinTriangleXML.o
mdl2dolfinXML: CMakeFiles/mdl2dolfinXML.dir/build.make
mdl2dolfinXML: CMakeFiles/mdl2dolfinXML.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joacaldo/memoria/join/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mdl2dolfinXML"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mdl2dolfinXML.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mdl2dolfinXML.dir/build: mdl2dolfinXML
.PHONY : CMakeFiles/mdl2dolfinXML.dir/build

CMakeFiles/mdl2dolfinXML.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mdl2dolfinXML.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mdl2dolfinXML.dir/clean

CMakeFiles/mdl2dolfinXML.dir/depend:
	cd /home/joacaldo/memoria/join/format && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format /home/joacaldo/memoria/join/format/CMakeFiles/mdl2dolfinXML.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mdl2dolfinXML.dir/depend
