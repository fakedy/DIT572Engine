# DIT572Engine
## About
A game engine for the course DIT572. While the engine is designed for the course its entirely independent from the course in terms of code and design. All our design decisions are our own.

## Building
The project use cmake as a build system.
You can build the project by running the BUILD.bat file, this creates a visual studio project in the build folder.
Since this project use SDL3 GPUDevice shader compilation is required, as of now its using the vulkan backend and thus require the vulkan SDK to compile shaders.

## Features

* EC (Entity Component)
* Sprite components
* simple physics
* AABB collisions
* Input system
* Sound system

## Third Party Libraries
* SDL
* CMAKE


