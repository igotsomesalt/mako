add_library(mako_core
    src/Logger.cpp
    src/FileSystem.cpp
    src/ThreadPool.cpp
)

target_include_directories(mako_core
    PUBLIC include
)