# DIT572Engine
## About
A game engine for the course DIT572. While the engine is designed for the course its entirely independent from the course in terms of code and design. All our design decisions are our own.

## Building from Source
### Prerequisites
Before building, ensure you have the following installed:
* **CMAKE**
* **C++ Compiler**
* **Vulkan SDK** - Can be skipped but you wont be able to compile shaders and are therefore required to use the precompiled ones.


**Clone the repository:**
   ```bash
  # Clone and enter the repository
  git clone https://github.com/fakedy/DIT572Engine.git
  cd DIT572Engine
```

### Windows
Simply run the Build.Bat file included.

### Linux
```bash
mkdir build
cd build
cmake ..
cmake --build .
```


## Features

* EC (Entity Component)
* Sprite components
* simple physics
* AABB collisions
* Input system
* Sound system
* Camera system

## Third Party Libraries
* **CMAKE**
* **SDL3**
* **GLM**
* **STB**


