cmake_minimum_required(VERSION  3.23)
project(Engine)

# GLM
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)

set(GLM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm")

set(GLAD_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include")
set(GLAD_SOURCE      "${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/src/glad.c")

set(ENGINE_CORE_SOURCES
    src/Core.cpp
    include/Engine/Core.h
    include/Engine/Layer.h
    ${GLAD_SOURCE}
    include/Engine/Renderer.h
    include/Engine/WindowManager.h
    src/WindowManager.cpp
    vendor/glad/src/glad.c
    "src/Renderer.cpp"
    "include/Engine/GameObject.h"
    "include/Engine/Components/Transform.h"
    "include/Engine/Components/Sprite.h"
    "include/Engine/Components/Component.h")


add_library(Engine STATIC ${ENGINE_CORE_SOURCES})




target_include_directories(Engine PUBLIC
    include
    ${GLM_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
    )

target_include_directories(Engine PRIVATE
    src
)


target_link_libraries(Engine PUBLIC
    glfw
    SDL3::SDL3
    ${CMAKE_DL_LIBS}
)