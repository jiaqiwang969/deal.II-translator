# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/runner/work/deal.II-translator/deal.II-translator/dealii

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/runner/work/deal.II-translator/deal.II-translator/dealii

# Utility rule file for build_code-gallery_h.

# Include any custom commands dependencies for this target.
include doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h.dir/compiler_depend.make

# Include the progress variables for this target.
include doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h.dir/progress.make

doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h: doc/doxygen/code-gallery/code-gallery.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/runner/work/deal.II-translator/deal.II-translator/dealii/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building code-gallery.h"

doc/doxygen/code-gallery/code-gallery.h: doc/doxygen/code-gallery/no-code-gallery.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/runner/work/deal.II-translator/deal.II-translator/dealii/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating code-gallery.h"
	cd /home/runner/work/deal.II-translator/deal.II-translator/dealii/doc/doxygen/code-gallery && /usr/local/bin/cmake -E copy /home/runner/work/deal.II-translator/deal.II-translator/dealii/doc/doxygen/code-gallery/no-code-gallery.h /home/runner/work/deal.II-translator/deal.II-translator/dealii/doc/doxygen/code-gallery/code-gallery.h

build_code-gallery_h: doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h
build_code-gallery_h: doc/doxygen/code-gallery/code-gallery.h
build_code-gallery_h: doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h.dir/build.make
.PHONY : build_code-gallery_h

# Rule to build all files generated by this target.
doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h.dir/build: build_code-gallery_h
.PHONY : doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h.dir/build

doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h.dir/clean:
	cd /home/runner/work/deal.II-translator/deal.II-translator/dealii/doc/doxygen/code-gallery && $(CMAKE_COMMAND) -P CMakeFiles/build_code-gallery_h.dir/cmake_clean.cmake
.PHONY : doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h.dir/clean

doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h.dir/depend:
	cd /home/runner/work/deal.II-translator/deal.II-translator/dealii && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runner/work/deal.II-translator/deal.II-translator/dealii /home/runner/work/deal.II-translator/deal.II-translator/dealii/doc/doxygen/code-gallery /home/runner/work/deal.II-translator/deal.II-translator/dealii /home/runner/work/deal.II-translator/deal.II-translator/dealii/doc/doxygen/code-gallery /home/runner/work/deal.II-translator/deal.II-translator/dealii/doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/doxygen/code-gallery/CMakeFiles/build_code-gallery_h.dir/depend

