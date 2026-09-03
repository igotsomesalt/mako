add_library(cli STATIC
    src/Graph.cpp
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