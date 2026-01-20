

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