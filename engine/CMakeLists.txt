cmake_minimum_required(VERSION  3.23)
project(Engine)


include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.0
    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL"
)

FetchContent_MakeAvailable(SDL3)

# GLM
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set(GLM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm")


set(STB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/STB")

set(GLAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include")
set(GLAD_SOURCE      "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c")

set(ENGINE_CORE_SOURCES
    src/Core.cpp
    include/Engine/Core.h
    
    ${GLAD_SOURCE}
    include/Engine/Renderer.h
    include/Engine/WindowManager.h
    src/WindowManager.cpp
    vendor/glad/src/glad.c
    "src/Renderer.cpp"
    "include/Engine/GameObject.h"
    "include/Engine/Components/Transform.h"
    "include/Engine/Components/Sprite.h"
    "include/Engine/Components/Component.h" "include/Engine/Shader.h" "include/Engine/InputManager.h"
    src/InputManager.cpp "include/Engine/EventManager.h" "src/EventManager.cpp"
    src/InputManager.cpp "include/Engine/SoundManager.h" "src/SoundManager.cpp"
     "src/Components/Sprite.cpp" "src/Components/Transform.cpp"
     "include/Engine/Time.h"  
     "include/Engine/Engine.h" "include/Engine/Scene.h" "include/Engine/AssetManager.h" "src/AssetManager.cpp" "include/Engine/Texture.h"   "include/Engine/Components/RenderComponent.h" "include/Engine/Components/Model.h" "include/Engine/Mesh.h" "include/Engine/Material.h")
    

add_library(Engine STATIC ${ENGINE_CORE_SOURCES})




target_include_directories(Engine PUBLIC
    include
    ${GLM_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
    ${STB_INCLUDE_DIR}
    )

target_include_directories(Engine PRIVATE
    src
)


target_link_libraries(Engine PUBLIC
    SDL3::SDL3
    ${CMAKE_DL_LIBS}
)