#
# flipstone
#
cmake_minimum_required(VERSION 3.0)

#
# project configuration
#
project(flipstone
    VERSION 2.3.0
    DESCRIPTION "Core library of revrsi game"
    LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#
# build configuration
#
option(FLIPSTONE_USE_STL "Use both of STL and collection2 container" OFF)

#
# global dependencies
#
include(FetchContent)
FetchContent_Declare(
    collection2
    GIT_REPOSITORY https://github.com/Enchan1207/collection2
    GIT_TAG v0.3.1
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


#
# exported library configuration
#
install(TARGETS flipstone
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    DIRECTORY ${flipstone_SOURCE_DIR}/include/flipstone
    DESTINATION include
)
