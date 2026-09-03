add_library(core STATIC
    src/Core.cpp
    src/Command.cpp
 )

target_include_directories(core
    PUBLIC include
)
