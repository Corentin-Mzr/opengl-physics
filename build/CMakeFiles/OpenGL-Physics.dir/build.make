# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Cmake\cmake-3.31.3-windows-x86_64\bin\cmake.exe

# The command to remove a file.
RM = C:\Cmake\cmake-3.31.3-windows-x86_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build

# Include any dependencies generated for this target.
include CMakeFiles/OpenGL-Physics.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OpenGL-Physics.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenGL-Physics.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenGL-Physics.dir/flags.make

CMakeFiles/OpenGL-Physics.dir/codegen:
.PHONY : CMakeFiles/OpenGL-Physics.dir/codegen

CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.obj: CMakeFiles/OpenGL-Physics.dir/flags.make
CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.obj: CMakeFiles/OpenGL-Physics.dir/includes_CXX.rsp
CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.obj: C:/Users/deads/Bureau/Jeux/github/cpp/opengl-physics/src/controller/app.cpp
CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.obj: CMakeFiles/OpenGL-Physics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.obj -MF CMakeFiles\OpenGL-Physics.dir\src\controller\app.cpp.obj.d -o CMakeFiles\OpenGL-Physics.dir\src\controller\app.cpp.obj -c C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\controller\app.cpp

CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\controller\app.cpp > CMakeFiles\OpenGL-Physics.dir\src\controller\app.cpp.i

CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\controller\app.cpp -o CMakeFiles\OpenGL-Physics.dir\src\controller\app.cpp.s

CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.obj: CMakeFiles/OpenGL-Physics.dir/flags.make
CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.obj: CMakeFiles/OpenGL-Physics.dir/includes_CXX.rsp
CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.obj: C:/Users/deads/Bureau/Jeux/github/cpp/opengl-physics/src/entity/ecs_manager.cpp
CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.obj: CMakeFiles/OpenGL-Physics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.obj -MF CMakeFiles\OpenGL-Physics.dir\src\entity\ecs_manager.cpp.obj.d -o CMakeFiles\OpenGL-Physics.dir\src\entity\ecs_manager.cpp.obj -c C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\entity\ecs_manager.cpp

CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\entity\ecs_manager.cpp > CMakeFiles\OpenGL-Physics.dir\src\entity\ecs_manager.cpp.i

CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\entity\ecs_manager.cpp -o CMakeFiles\OpenGL-Physics.dir\src\entity\ecs_manager.cpp.s

CMakeFiles/OpenGL-Physics.dir/src/glad.c.obj: CMakeFiles/OpenGL-Physics.dir/flags.make
CMakeFiles/OpenGL-Physics.dir/src/glad.c.obj: CMakeFiles/OpenGL-Physics.dir/includes_C.rsp
CMakeFiles/OpenGL-Physics.dir/src/glad.c.obj: C:/Users/deads/Bureau/Jeux/github/cpp/opengl-physics/src/glad.c
CMakeFiles/OpenGL-Physics.dir/src/glad.c.obj: CMakeFiles/OpenGL-Physics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/OpenGL-Physics.dir/src/glad.c.obj"
	C:\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OpenGL-Physics.dir/src/glad.c.obj -MF CMakeFiles\OpenGL-Physics.dir\src\glad.c.obj.d -o CMakeFiles\OpenGL-Physics.dir\src\glad.c.obj -c C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\glad.c

CMakeFiles/OpenGL-Physics.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/OpenGL-Physics.dir/src/glad.c.i"
	C:\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\glad.c > CMakeFiles\OpenGL-Physics.dir\src\glad.c.i

CMakeFiles/OpenGL-Physics.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/OpenGL-Physics.dir/src/glad.c.s"
	C:\MinGW\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\glad.c -o CMakeFiles\OpenGL-Physics.dir\src\glad.c.s

CMakeFiles/OpenGL-Physics.dir/src/main.cpp.obj: CMakeFiles/OpenGL-Physics.dir/flags.make
CMakeFiles/OpenGL-Physics.dir/src/main.cpp.obj: CMakeFiles/OpenGL-Physics.dir/includes_CXX.rsp
CMakeFiles/OpenGL-Physics.dir/src/main.cpp.obj: C:/Users/deads/Bureau/Jeux/github/cpp/opengl-physics/src/main.cpp
CMakeFiles/OpenGL-Physics.dir/src/main.cpp.obj: CMakeFiles/OpenGL-Physics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/OpenGL-Physics.dir/src/main.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL-Physics.dir/src/main.cpp.obj -MF CMakeFiles\OpenGL-Physics.dir\src\main.cpp.obj.d -o CMakeFiles\OpenGL-Physics.dir\src\main.cpp.obj -c C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\main.cpp

CMakeFiles/OpenGL-Physics.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OpenGL-Physics.dir/src/main.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\main.cpp > CMakeFiles\OpenGL-Physics.dir\src\main.cpp.i

CMakeFiles/OpenGL-Physics.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OpenGL-Physics.dir/src/main.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\main.cpp -o CMakeFiles\OpenGL-Physics.dir\src\main.cpp.s

CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.obj: CMakeFiles/OpenGL-Physics.dir/flags.make
CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.obj: CMakeFiles/OpenGL-Physics.dir/includes_CXX.rsp
CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.obj: C:/Users/deads/Bureau/Jeux/github/cpp/opengl-physics/src/systems/physics_system.cpp
CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.obj: CMakeFiles/OpenGL-Physics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.obj -MF CMakeFiles\OpenGL-Physics.dir\src\systems\physics_system.cpp.obj.d -o CMakeFiles\OpenGL-Physics.dir\src\systems\physics_system.cpp.obj -c C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\systems\physics_system.cpp

CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\systems\physics_system.cpp > CMakeFiles\OpenGL-Physics.dir\src\systems\physics_system.cpp.i

CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\systems\physics_system.cpp -o CMakeFiles\OpenGL-Physics.dir\src\systems\physics_system.cpp.s

CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.obj: CMakeFiles/OpenGL-Physics.dir/flags.make
CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.obj: CMakeFiles/OpenGL-Physics.dir/includes_CXX.rsp
CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.obj: C:/Users/deads/Bureau/Jeux/github/cpp/opengl-physics/src/systems/render_system.cpp
CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.obj: CMakeFiles/OpenGL-Physics.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.obj"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.obj -MF CMakeFiles\OpenGL-Physics.dir\src\systems\render_system.cpp.obj.d -o CMakeFiles\OpenGL-Physics.dir\src\systems\render_system.cpp.obj -c C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\systems\render_system.cpp

CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.i"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\systems\render_system.cpp > CMakeFiles\OpenGL-Physics.dir\src\systems\render_system.cpp.i

CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.s"
	C:\MinGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\src\systems\render_system.cpp -o CMakeFiles\OpenGL-Physics.dir\src\systems\render_system.cpp.s

# Object files for target OpenGL-Physics
OpenGL__Physics_OBJECTS = \
"CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.obj" \
"CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.obj" \
"CMakeFiles/OpenGL-Physics.dir/src/glad.c.obj" \
"CMakeFiles/OpenGL-Physics.dir/src/main.cpp.obj" \
"CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.obj" \
"CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.obj"

# External object files for target OpenGL-Physics
OpenGL__Physics_EXTERNAL_OBJECTS =

OpenGL-Physics.exe: CMakeFiles/OpenGL-Physics.dir/src/controller/app.cpp.obj
OpenGL-Physics.exe: CMakeFiles/OpenGL-Physics.dir/src/entity/ecs_manager.cpp.obj
OpenGL-Physics.exe: CMakeFiles/OpenGL-Physics.dir/src/glad.c.obj
OpenGL-Physics.exe: CMakeFiles/OpenGL-Physics.dir/src/main.cpp.obj
OpenGL-Physics.exe: CMakeFiles/OpenGL-Physics.dir/src/systems/physics_system.cpp.obj
OpenGL-Physics.exe: CMakeFiles/OpenGL-Physics.dir/src/systems/render_system.cpp.obj
OpenGL-Physics.exe: CMakeFiles/OpenGL-Physics.dir/build.make
OpenGL-Physics.exe: dependencies/glfw/src/libglfw3.a
OpenGL-Physics.exe: CMakeFiles/OpenGL-Physics.dir/linkLibs.rsp
OpenGL-Physics.exe: CMakeFiles/OpenGL-Physics.dir/objects1.rsp
OpenGL-Physics.exe: CMakeFiles/OpenGL-Physics.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable OpenGL-Physics.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\OpenGL-Physics.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenGL-Physics.dir/build: OpenGL-Physics.exe
.PHONY : CMakeFiles/OpenGL-Physics.dir/build

CMakeFiles/OpenGL-Physics.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\OpenGL-Physics.dir\cmake_clean.cmake
.PHONY : CMakeFiles/OpenGL-Physics.dir/clean

CMakeFiles/OpenGL-Physics.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build C:\Users\deads\Bureau\Jeux\github\cpp\opengl-physics\build\CMakeFiles\OpenGL-Physics.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/OpenGL-Physics.dir/depend

