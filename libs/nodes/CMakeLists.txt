add_library(nodes STATIC
	src/Node.cpp
    src/GoalNode.cpp
)

target_include_directories(nodes
    PUBLIC include
)

target_link_libraries(nodes
    PUBLIC
        core
)