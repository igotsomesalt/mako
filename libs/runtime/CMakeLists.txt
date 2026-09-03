add_library(runtime STATIC
	src/Runtime.cpp
)

target_include_directories(runtime
    PUBLIC include
)

target_link_libraries(runtime
    PUBLIC
        core
        graph
        nodes
)