#
# flipstone
#
cmake_minimum_required(VERSION 3.0)

#
# project configuration
#
project(flipstone
    VERSION 1.0.0
    DESCRIPTION "Simple reversi game"
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# global dependencies
#
include(FetchContent)
FetchContent_Declare(
    collection2
    GIT_REPOSITORY https://github.com/Enchan1207/collection2
    GIT_TAG v0.3.0
)
FetchContent_MakeAvailable(collection2)

#
# unit testing configuration
#
option(FLIPSTONE_BUILD_TESTS "Enable testing of collection2" OFF)
if(FLIPSTONE_BUILD_TESTS)
    message(NOTICE "flipstone: unit testing enabled.")
    set(INSTALL_GTEST OFF)
    enable_testing()
endif()

#
# subdirectories
#
add_subdirectory(src)
if(FLIPSTONE_BUILD_TESTS)
    add_subdirectory(tests)
endif()
