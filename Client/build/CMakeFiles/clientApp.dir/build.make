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
CMAKE_SOURCE_DIR = "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client/build"

# Include any dependencies generated for this target.
include CMakeFiles/clientApp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/clientApp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/clientApp.dir/flags.make

CMakeFiles/clientApp.dir/main.cpp.o: CMakeFiles/clientApp.dir/flags.make
CMakeFiles/clientApp.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/clientApp.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clientApp.dir/main.cpp.o -c "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client/main.cpp"

CMakeFiles/clientApp.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clientApp.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client/main.cpp" > CMakeFiles/clientApp.dir/main.cpp.i

CMakeFiles/clientApp.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clientApp.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client/main.cpp" -o CMakeFiles/clientApp.dir/main.cpp.s

# Object files for target clientApp
clientApp_OBJECTS = \
"CMakeFiles/clientApp.dir/main.cpp.o"

# External object files for target clientApp
clientApp_EXTERNAL_OBJECTS =

clientApp: CMakeFiles/clientApp.dir/main.cpp.o
clientApp: CMakeFiles/clientApp.dir/build.make
clientApp: Helpers/Src/libcalculation_helper.a
clientApp: CMakeFiles/clientApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable clientApp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clientApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/clientApp.dir/build: clientApp

.PHONY : CMakeFiles/clientApp.dir/build

CMakeFiles/clientApp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/clientApp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/clientApp.dir/clean

CMakeFiles/clientApp.dir/depend:
	cd "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client" "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client" "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client/build" "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client/build" "/mnt/c/Users/Mahmoud/Desktop/DELL C++ Task/Client/build/CMakeFiles/clientApp.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/clientApp.dir/depend

