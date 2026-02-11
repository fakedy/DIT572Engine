find_program(GLSLC_BIN glslc)

set(GAME_SOURCES
    src/main.cpp "src/GameScene.cpp" "src/World.cpp")

set(GAME_INCLUDES "include/Game/GameScene.h" "include/Game/World.h")


add_executable(Game
    ${GAME_SOURCES}
    ${GAME_INCLUDES})


target_include_directories(Game PUBLIC
    include
    )



if(GLSLC_BIN)

    message(STATUS "Compiling shaders...")
    # find shaders
    file(GLOB_RECURSE SHADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/Assets/shaders/*.vert"
    "${CMAKE_CURRENT_SOURCE_DIR}/Assets/shaders/*.frag"
    )

    message(STATUS "Found Shaders: ${SHADERS}")

    set(COMPILED_SHADERS "")

    foreach(SHADER ${SHADERS})
        # get filename of shader
        get_filename_component(SHADER_NAME ${SHADER} NAME_WE)

        # create shader out variable
        set(SHADER_OUT "${CMAKE_CURRENT_SOURCE_DIR}/Assets/shaders/${SHADER_NAME}.spv")

        add_custom_command(
            OUTPUT "${SHADER_OUT}"
            COMMAND "${GLSLC_BIN}" "${SHADER}" -o "${SHADER_OUT}"
            DEPENDS "${SHADER}"
            COMMENT "Compiling ${SHADER_NAME} to ${SHADER_OUT}"
        )

        list(APPEND COMPILED_SHADERS ${SHADER_OUT})

    endforeach()

    message(STATUS "List of compiled Shaders: ${COMPILED_SHADERS}")

    add_custom_target(compile_shaders ALL DEPENDS ${COMPILED_SHADERS})

else()
    message(WARNING "GLSLC_BIN NOT FOUND")

endif()

target_link_libraries(Game PRIVATE Engine)



add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:Game>/Assets"
    COMMENT "Copying game assets..."
)

if(TARGET compile_shaders)
    add_dependencies(copy_assets compile_shaders)
endif()

add_dependencies(Game copy_assets)