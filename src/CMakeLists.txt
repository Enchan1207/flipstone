#
# simple_reversi sources
#
cmake_minimum_required(VERSION 3.0)

add_library(simple_reversi)
target_sources(simple_reversi PRIVATE
    access.c
    ai.c
    count.c
    field.c
    logic.c
    search.c
)
target_include_directories(simple_reversi PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)
target_compile_options(simple_reversi PRIVATE
    -Wall
)
