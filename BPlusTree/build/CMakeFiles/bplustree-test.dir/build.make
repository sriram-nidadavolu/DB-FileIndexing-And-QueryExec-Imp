# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy/build"

# Include any dependencies generated for this target.
include CMakeFiles/bplustree-test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/bplustree-test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bplustree-test.dir/flags.make

CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.o: CMakeFiles/bplustree-test.dir/flags.make
CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.o: ../test/b_plus_tree_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.o -c "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy/test/b_plus_tree_test.cpp"

CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy/test/b_plus_tree_test.cpp" > CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.i

CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy/test/b_plus_tree_test.cpp" -o CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.s

# Object files for target bplustree-test
bplustree__test_OBJECTS = \
"CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.o"

# External object files for target bplustree-test
bplustree__test_EXTERNAL_OBJECTS =

bplustree-test: CMakeFiles/bplustree-test.dir/test/b_plus_tree_test.cpp.o
bplustree-test: CMakeFiles/bplustree-test.dir/build.make
bplustree-test: src/libBPLUSTREE.a
bplustree-test: CMakeFiles/bplustree-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bplustree-test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bplustree-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bplustree-test.dir/build: bplustree-test

.PHONY : CMakeFiles/bplustree-test.dir/build

CMakeFiles/bplustree-test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bplustree-test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bplustree-test.dir/clean

CMakeFiles/bplustree-test.dir/depend:
	cd "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy" "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy" "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy/build" "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy/build" "/common/home/vsn9/Documents/db/CS539-Fall22-main working copy/CS539-Fall22-main working copy/build/CMakeFiles/bplustree-test.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/bplustree-test.dir/depend

