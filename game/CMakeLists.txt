

set(GAME_SOURCES
    src/main.cpp)



add_executable(Game ${GAME_SOURCES})


target_link_libraries(Game PRIVATE Engine)