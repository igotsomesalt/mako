add_library(runtime STATIC
	src/Runtime.cpp
)

target_include_directories(runtime
    PUBLIC include
)