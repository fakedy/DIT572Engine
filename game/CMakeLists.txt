

set(GAME_SOURCES
    src/main.cpp "src/GameScene.cpp")

set(GAME_INCLUDES "include/Game/GameScene.h")


add_executable(Game
    ${GAME_SOURCES}
    ${GAME_INCLUDES})


target_include_directories(Game PUBLIC
    include
    )




target_link_libraries(Game PRIVATE Engine)

add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Assets"
        "$<TARGET_FILE_DIR:Game>/Assets"
    COMMENT "Copying game assets..."
)

add_dependencies(Game copy_assets)