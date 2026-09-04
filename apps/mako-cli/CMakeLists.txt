add_executable(mako_cli
	src/MakoCli.cpp
)

target_include_directories(mako_cli
    PUBLIC include
)

target_link_libraries(mako_cli
    PUBLIC
        cli
        core
        graph
        nodes
        runtime
)