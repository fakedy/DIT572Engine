
set(SERVER_SOURCES
    src/main.cpp "src/Level.cpp")

set(SERVER_INCLUDES  "include/Server/Level.h")


add_executable(Server
    ${SERVER_SOURCES}
    ${SERVER_INCLUDES})


target_include_directories(Server PUBLIC
    include
    )




target_link_libraries(Server PRIVATE Engine)


