#
# simple_reversi sources
#
cmake_minimum_required(VERSION 3.0)

add_library(reversi)
target_sources(reversi PRIVATE
    access.cpp
    count.cpp
    field.cpp
    logic.cpp
    search.cpp
)
target_include_directories(reversi PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_compile_options(reversi PRIVATE
    -Wall
)
