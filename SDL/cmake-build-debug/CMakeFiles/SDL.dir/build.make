# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Asus\CLionProjects\SDL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Asus\CLionProjects\SDL\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/SDL.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/SDL.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SDL.dir/flags.make

CMakeFiles/SDL.dir/main.cpp.obj: CMakeFiles/SDL.dir/flags.make
CMakeFiles/SDL.dir/main.cpp.obj: CMakeFiles/SDL.dir/includes_CXX.rsp
CMakeFiles/SDL.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Asus\CLionProjects\SDL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SDL.dir/main.cpp.obj"
	C:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SDL.dir\main.cpp.obj -c C:\Users\Asus\CLionProjects\SDL\main.cpp

CMakeFiles/SDL.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SDL.dir/main.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Asus\CLionProjects\SDL\main.cpp > CMakeFiles\SDL.dir\main.cpp.i

CMakeFiles/SDL.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SDL.dir/main.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Asus\CLionProjects\SDL\main.cpp -o CMakeFiles\SDL.dir\main.cpp.s

CMakeFiles/SDL.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/SDL.dir/main.cpp.obj.requires

CMakeFiles/SDL.dir/main.cpp.obj.provides: CMakeFiles/SDL.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\SDL.dir\build.make CMakeFiles/SDL.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/SDL.dir/main.cpp.obj.provides

CMakeFiles/SDL.dir/main.cpp.obj.provides.build: CMakeFiles/SDL.dir/main.cpp.obj


CMakeFiles/SDL.dir/Display.cpp.obj: CMakeFiles/SDL.dir/flags.make
CMakeFiles/SDL.dir/Display.cpp.obj: CMakeFiles/SDL.dir/includes_CXX.rsp
CMakeFiles/SDL.dir/Display.cpp.obj: ../Display.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Asus\CLionProjects\SDL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SDL.dir/Display.cpp.obj"
	C:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SDL.dir\Display.cpp.obj -c C:\Users\Asus\CLionProjects\SDL\Display.cpp

CMakeFiles/SDL.dir/Display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SDL.dir/Display.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Asus\CLionProjects\SDL\Display.cpp > CMakeFiles\SDL.dir\Display.cpp.i

CMakeFiles/SDL.dir/Display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SDL.dir/Display.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Asus\CLionProjects\SDL\Display.cpp -o CMakeFiles\SDL.dir\Display.cpp.s

CMakeFiles/SDL.dir/Display.cpp.obj.requires:

.PHONY : CMakeFiles/SDL.dir/Display.cpp.obj.requires

CMakeFiles/SDL.dir/Display.cpp.obj.provides: CMakeFiles/SDL.dir/Display.cpp.obj.requires
	$(MAKE) -f CMakeFiles\SDL.dir\build.make CMakeFiles/SDL.dir/Display.cpp.obj.provides.build
.PHONY : CMakeFiles/SDL.dir/Display.cpp.obj.provides

CMakeFiles/SDL.dir/Display.cpp.obj.provides.build: CMakeFiles/SDL.dir/Display.cpp.obj


CMakeFiles/SDL.dir/Shader.cpp.obj: CMakeFiles/SDL.dir/flags.make
CMakeFiles/SDL.dir/Shader.cpp.obj: CMakeFiles/SDL.dir/includes_CXX.rsp
CMakeFiles/SDL.dir/Shader.cpp.obj: ../Shader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Asus\CLionProjects\SDL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SDL.dir/Shader.cpp.obj"
	C:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SDL.dir\Shader.cpp.obj -c C:\Users\Asus\CLionProjects\SDL\Shader.cpp

CMakeFiles/SDL.dir/Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SDL.dir/Shader.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Asus\CLionProjects\SDL\Shader.cpp > CMakeFiles\SDL.dir\Shader.cpp.i

CMakeFiles/SDL.dir/Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SDL.dir/Shader.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Asus\CLionProjects\SDL\Shader.cpp -o CMakeFiles\SDL.dir\Shader.cpp.s

CMakeFiles/SDL.dir/Shader.cpp.obj.requires:

.PHONY : CMakeFiles/SDL.dir/Shader.cpp.obj.requires

CMakeFiles/SDL.dir/Shader.cpp.obj.provides: CMakeFiles/SDL.dir/Shader.cpp.obj.requires
	$(MAKE) -f CMakeFiles\SDL.dir\build.make CMakeFiles/SDL.dir/Shader.cpp.obj.provides.build
.PHONY : CMakeFiles/SDL.dir/Shader.cpp.obj.provides

CMakeFiles/SDL.dir/Shader.cpp.obj.provides.build: CMakeFiles/SDL.dir/Shader.cpp.obj


CMakeFiles/SDL.dir/Mesh.cpp.obj: CMakeFiles/SDL.dir/flags.make
CMakeFiles/SDL.dir/Mesh.cpp.obj: CMakeFiles/SDL.dir/includes_CXX.rsp
CMakeFiles/SDL.dir/Mesh.cpp.obj: ../Mesh.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Asus\CLionProjects\SDL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SDL.dir/Mesh.cpp.obj"
	C:\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\SDL.dir\Mesh.cpp.obj -c C:\Users\Asus\CLionProjects\SDL\Mesh.cpp

CMakeFiles/SDL.dir/Mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SDL.dir/Mesh.cpp.i"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Asus\CLionProjects\SDL\Mesh.cpp > CMakeFiles\SDL.dir\Mesh.cpp.i

CMakeFiles/SDL.dir/Mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SDL.dir/Mesh.cpp.s"
	C:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Asus\CLionProjects\SDL\Mesh.cpp -o CMakeFiles\SDL.dir\Mesh.cpp.s

CMakeFiles/SDL.dir/Mesh.cpp.obj.requires:

.PHONY : CMakeFiles/SDL.dir/Mesh.cpp.obj.requires

CMakeFiles/SDL.dir/Mesh.cpp.obj.provides: CMakeFiles/SDL.dir/Mesh.cpp.obj.requires
	$(MAKE) -f CMakeFiles\SDL.dir\build.make CMakeFiles/SDL.dir/Mesh.cpp.obj.provides.build
.PHONY : CMakeFiles/SDL.dir/Mesh.cpp.obj.provides

CMakeFiles/SDL.dir/Mesh.cpp.obj.provides.build: CMakeFiles/SDL.dir/Mesh.cpp.obj


# Object files for target SDL
SDL_OBJECTS = \
"CMakeFiles/SDL.dir/main.cpp.obj" \
"CMakeFiles/SDL.dir/Display.cpp.obj" \
"CMakeFiles/SDL.dir/Shader.cpp.obj" \
"CMakeFiles/SDL.dir/Mesh.cpp.obj"

# External object files for target SDL
SDL_EXTERNAL_OBJECTS =

SDL.exe: CMakeFiles/SDL.dir/main.cpp.obj
SDL.exe: CMakeFiles/SDL.dir/Display.cpp.obj
SDL.exe: CMakeFiles/SDL.dir/Shader.cpp.obj
SDL.exe: CMakeFiles/SDL.dir/Mesh.cpp.obj
SDL.exe: CMakeFiles/SDL.dir/build.make
SDL.exe: C:/mingw64/lib/libglew32.dll.a
SDL.exe: C:/mingw64/lib/libSDL2main.a
SDL.exe: C:/mingw64/lib/libSDL2.dll.a
SDL.exe: CMakeFiles/SDL.dir/linklibs.rsp
SDL.exe: CMakeFiles/SDL.dir/objects1.rsp
SDL.exe: CMakeFiles/SDL.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Asus\CLionProjects\SDL\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable SDL.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\SDL.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SDL.dir/build: SDL.exe

.PHONY : CMakeFiles/SDL.dir/build

CMakeFiles/SDL.dir/requires: CMakeFiles/SDL.dir/main.cpp.obj.requires
CMakeFiles/SDL.dir/requires: CMakeFiles/SDL.dir/Display.cpp.obj.requires
CMakeFiles/SDL.dir/requires: CMakeFiles/SDL.dir/Shader.cpp.obj.requires
CMakeFiles/SDL.dir/requires: CMakeFiles/SDL.dir/Mesh.cpp.obj.requires

.PHONY : CMakeFiles/SDL.dir/requires

CMakeFiles/SDL.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\SDL.dir\cmake_clean.cmake
.PHONY : CMakeFiles/SDL.dir/clean

CMakeFiles/SDL.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Asus\CLionProjects\SDL C:\Users\Asus\CLionProjects\SDL C:\Users\Asus\CLionProjects\SDL\cmake-build-debug C:\Users\Asus\CLionProjects\SDL\cmake-build-debug C:\Users\Asus\CLionProjects\SDL\cmake-build-debug\CMakeFiles\SDL.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/SDL.dir/depend

