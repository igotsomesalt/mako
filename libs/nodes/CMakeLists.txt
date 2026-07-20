add_library(nodes STATIC
	src/Node.cpp

    "include/goal_node.h"
)

target_include_directories(nodes
    PUBLIC include
)

target_link_libraries(nodes
    PUBLIC
        core
)