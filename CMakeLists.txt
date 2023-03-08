#
# simple_reversi
#
cmake_minimum_required(VERSION 3.0)

#
# project configuration
#
project(simple_reversi
    VERSION 1.0.0
    DESCRIPTION "parse and evaluate formula"
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# subdirectories
#
add_subdirectory(src)
add_subdirectory(cli)
