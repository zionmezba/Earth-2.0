# Earth-2.0

A small computer-graphics demo written in C++ that renders a textured Earth.

![screenshot](https://github.com/zionmezba/Earth-2.0/assets/65642391/135e3525-1702-4195-801a-32e41f9f6d62)

## Table of contents
- [Features](#features)
- [Requirements](#requirements)
- [Build](#build)
  - [Using CMake (recommended)](#using-cmake-recommended)
  - [Simple compile (single-file demo)](#simple-compile-single-file-demo)
  - [Windows / Visual Studio](#windows--visual-studio)
- [Run](#run)
- [Controls](#controls)
- [Assets](#assets)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Features
- Real-time textured globe rendering
- Basic camera controls
- (Add lighting, atmosphere, rotation, LOD, etc. as applicable)

## Requirements
Minimum (adjust to your project):
- C++17 compatible compiler (GCC, Clang, MSVC)
- CMake >= 3.10 (if using CMake)
- OpenGL (desktop)
- GLFW (or SDL) for windowing/input
- GLAD or GLEW for loading OpenGL functions
- stb_image (or another image loader) for textures


## Build

Note: Replace <executable-name> below with the actual produced binary name (for example `earth`, `Earth-2.0`, etc.).

### Using CMake (recommended)
1. Clone:
   git clone https://github.com/zionmezba/Earth-2.0.git
   cd Earth-2.0

2. Create build directory and compile:
   mkdir build
   cd build
   cmake .. 
   cmake --build . --config Release

3. Run the binary:
   On Linux/macOS:
     ./<executable-name>
   On Windows (PowerShell):
     .\Release\<executable-name>.exe

### Simple compile (single-file demo)
If the project is a single .cpp file and uses no heavy build system, you can try:
g++ -std=c++17 -O2 -I/path/to/include -L/path/to/lib src/main.cpp -lGL -lglfw -ldl -o <executable-name>

Adjust include and library flags for your platform.

### Windows / Visual Studio
- If a CMakeLists.txt exists: open a Developer Command Prompt:
  mkdir build && cd build
  cmake -G "Visual Studio 17 2022" ..
  cmake --build . --config Release
- Or open the provided solution (.sln) in Visual Studio and build Release.

## Run
- Ensure any required asset folders (e.g., `assets/`, `textures/`) are next to the binary or in the expected path.
- Example:
  ./<executable-name> --assets ../assets
- If the program accepts command-line args, list them here (e.g., --width, --height, --no-vsync).

## Controls
(Replace with the actual controls used by your app)
- W / A / S / D — move camera
- Mouse — look around
- Scroll wheel — zoom
- Space — toggle auto-rotation
- Esc — quit

## Assets
Put textures and other data into an `assets/` folder at the repository root (or wherever the program expects them). Common files:
- textures/earth_diffuse.png
- textures/earth_normal.png
- shaders/vertex.glsl
- shaders/fragment.glsl

## Troubleshooting
- Missing OpenGL headers: install appropriate dev packages (Linux: libgl1-mesa-dev; macOS: Xcode / Command Line Tools).
- Linker errors: verify that you linked GLFW/GL/other libs and that library paths are correct.
- Textures don’t load: check asset paths and working directory when running the binary.
- If using CMake, run cmake with -DCMAKE_BUILD_TYPE=Release or Debug as appropriate.

## Contributing
Contributions welcome.
1. Fork the repo
2. Create a branch: git checkout -b feature/my-change
3. Commit your changes and push
4. Open a pull request describing the change

## Contact
Maintainer: @zionmezba
