add_library(graph STATIC
    src/Graph.cpp
)

target_include_directories(graph
    PUBLIC include
)

target_link_libraries(graph
    PUBLIC
        core
)

target_link_libraries(graph
    PUBLIC
        nodes
)