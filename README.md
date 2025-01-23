# OpenGL Physics Engine

Physics Engine using OpenGL.  

## Installation

### Prerequisites

- C++/C compiler (gcc, g++, cl, clang)
- CMake 3.16 or newer
- OpenGL

### Clone the repository

```bash
git clone https://github.com/Corentin-Mzr/opengl-physics
```

### Update submodules

From the root folder, execute the following commands

```bash
cd dependencies
git submodule update --init --recursive
```

### Build the project

From the root folder, execute the following commands

```bash
mkdir build
cmake ..
cmake --build build
```

### Run the program

To run the program, launch it from the build folder

```bash
cd build
./OpenGL-Physics.exe
```
