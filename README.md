<!-- PROJECT LOGO -->
<div align="center">
  <a href="https://github.com/othneildrew/Best-README-Template">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">Tetris OpenGL Game</h3>

  <p align="center">
    A simple tetris game in C++ and modern OpenGL
  </p>
</div>

<!-- ABOUT THE PROJECT -->
## About The Project

[![Product Name Screen Shot][product-screenshot]]

This project is a classic Tetris game implemented in C++ using OpenGL for graphics. It demonstrates fundamental 2D game development principles using OpenGL and goes beyond by incorporating sound effects using OpenAL and rendering text using FreeType.

Project objectives:
* Practical application of OpenGL, C++, OpenAL, and FreeType knowledge.
* Creating a functional and engaging game experience.
* Demonstration of basic 2D game development in C++ using OpenGL, including sound and text rendering.

### Build

### Installing the necessary tools 
1. CMake: Download and install CMake from the official website: https://cmake.org/download. Add CMake to the PATH environment variable.
2. Visual Studio (optional, but recommended for Windows): If you are going to compile a project on Windows, you will need Visual Studio with the C++ compiler installed. You can use the free version of the Community Edition.
3. vcpkg: Download and install vcpkg following the instructions on the official website: https://github.com/microsoft/vcpkg. Add vcpkg to the PATH environment variable.

### Build project
1. Clone the repo
   ```sh
   git clone https://github.com/dryerem19/TetrisGL
   ```
2. Navigate to the root directory of the project and run the following command
   ```sh
   vcpkg integrate install
   vcpkg install --recurse
   ```
4. Open project folder in Visual Studio 2022
5. Run build project

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[product-screenshot]: images/screenshot.png
