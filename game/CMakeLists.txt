

set(GAME_SOURCES
    src/main.cpp
    src/GameLayer.cpp)

set(GAME_INCLUDES
    include/Game/GameLayer.h)


add_executable(Game
    ${GAME_SOURCES}
    ${GAME_INCLUDES})


target_include_directories(Game PUBLIC
    include
    )




target_link_libraries(Game PRIVATE Engine)

add_custom_command(TARGET Game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:Game>/assets"
    COMMENT "Copying game assets to output directory..."
)