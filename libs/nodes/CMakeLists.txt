add_library(nodes STATIC
	src/Node.cpp
 "include/constant_node.h")

target_include_directories(nodes
    PUBLIC include
)

target_link_libraries(nodes
    PUBLIC
        core
)