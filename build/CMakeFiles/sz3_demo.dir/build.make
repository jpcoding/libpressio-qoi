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
CMAKE_COMMAND = /home/pjiao/.local/lib/python3.10/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/pjiao/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pjiao/test/vldbtests

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pjiao/test/vldbtests/build

# Include any dependencies generated for this target.
include CMakeFiles/sz3_demo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sz3_demo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sz3_demo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sz3_demo.dir/flags.make

CMakeFiles/sz3_demo.dir/sz3_demo.cpp.o: CMakeFiles/sz3_demo.dir/flags.make
CMakeFiles/sz3_demo.dir/sz3_demo.cpp.o: ../sz3_demo.cpp
CMakeFiles/sz3_demo.dir/sz3_demo.cpp.o: CMakeFiles/sz3_demo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pjiao/test/vldbtests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sz3_demo.dir/sz3_demo.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sz3_demo.dir/sz3_demo.cpp.o -MF CMakeFiles/sz3_demo.dir/sz3_demo.cpp.o.d -o CMakeFiles/sz3_demo.dir/sz3_demo.cpp.o -c /home/pjiao/test/vldbtests/sz3_demo.cpp

CMakeFiles/sz3_demo.dir/sz3_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sz3_demo.dir/sz3_demo.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pjiao/test/vldbtests/sz3_demo.cpp > CMakeFiles/sz3_demo.dir/sz3_demo.cpp.i

CMakeFiles/sz3_demo.dir/sz3_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sz3_demo.dir/sz3_demo.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pjiao/test/vldbtests/sz3_demo.cpp -o CMakeFiles/sz3_demo.dir/sz3_demo.cpp.s

# Object files for target sz3_demo
sz3_demo_OBJECTS = \
"CMakeFiles/sz3_demo.dir/sz3_demo.cpp.o"

# External object files for target sz3_demo
sz3_demo_EXTERNAL_OBJECTS =

sz3_demo: CMakeFiles/sz3_demo.dir/sz3_demo.cpp.o
sz3_demo: CMakeFiles/sz3_demo.dir/build.make
sz3_demo: /home/pjiao/.local/lib64/liblibpressio.so
sz3_demo: /home/pjiao/git/spack/opt/spack/linux-fedora36-skylake/gcc-12.1.1/libstdcompat-0.0.15-jy7h6njv7f36whpzgg42hkske4x4ehqh/lib64/libstd_compat.so
sz3_demo: CMakeFiles/sz3_demo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pjiao/test/vldbtests/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sz3_demo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sz3_demo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sz3_demo.dir/build: sz3_demo
.PHONY : CMakeFiles/sz3_demo.dir/build

CMakeFiles/sz3_demo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sz3_demo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sz3_demo.dir/clean

CMakeFiles/sz3_demo.dir/depend:
	cd /home/pjiao/test/vldbtests/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pjiao/test/vldbtests /home/pjiao/test/vldbtests /home/pjiao/test/vldbtests/build /home/pjiao/test/vldbtests/build /home/pjiao/test/vldbtests/build/CMakeFiles/sz3_demo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sz3_demo.dir/depend

