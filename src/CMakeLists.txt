#
# flipstone sources
#
cmake_minimum_required(VERSION 3.0)

add_library(flipstone)
target_sources(flipstone PRIVATE
    field.cpp
    reversi.cpp
)
target_include_directories(flipstone PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${collection2_SOURCE_DIR}/include
)
target_compile_options(flipstone PRIVATE
    -Wall
)
