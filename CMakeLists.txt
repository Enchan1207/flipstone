#
# simple_reversi
#
cmake_minimum_required(VERSION 3.0)

#
# project configuration
#
project(simple_reversi
    VERSION 1.0.0
    DESCRIPTION "Simple reversi game"
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# build configuration
#

# 依存関係としてビルドされている場合はヘッドレスモードを有効にする
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(SIMPLE_REVERSI_HEADLESS "Build core (without any game interfaces) only" OFF)
else()
    option(SIMPLE_REVERSI_HEADLESS "Build core (without any game interfaces) only" ON)
endif()
if(${SIMPLE_REVERSI_HEADLESS})
    message(NOTICE "simple_reversi: Headless mode enabled. only core library will be built.")
endif()

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
option(SIMPLE_REVERSI_BUILD_TESTS "Enable testing of collection2" OFF)
if(SIMPLE_REVERSI_BUILD_TESTS)
    message(NOTICE "simple_reversi: unit testing enabled.")
    set(INSTALL_GTEST OFF)
    enable_testing()
endif()

#
# subdirectories
#
add_subdirectory(src)
if(NOT ${SIMPLE_REVERSI_HEADLESS})
    add_subdirectory(cli)
endif()
if(SIMPLE_REVERSI_BUILD_TESTS)
    add_subdirectory(tests)
endif()
