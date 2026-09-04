cmake_minimum_required(VERSION 3.28)

project(Mako
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(apps/mako-cli)

add_subdirectory(libs/cli)
add_subdirectory(libs/core)
add_subdirectory(libs/graph)
add_subdirectory(libs/nodes)
add_subdirectory(libs/runtime)
