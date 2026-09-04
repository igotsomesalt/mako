add_library(cli STATIC
    src/Cli.cpp
    src/CommandParser.cpp
    src/CommandLexer.cpp
    src/Command.cpp
)

target_include_directories(cli
    PUBLIC include
)

target_link_libraries(cli
    PUBLIC
        core
        graph
        nodes
        runtime
)