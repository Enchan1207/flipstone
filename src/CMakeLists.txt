#
# flipstone sources
#
cmake_minimum_required(VERSION 3.0)

add_library(flipstone)
target_sources(flipstone PRIVATE
    field.cpp
    fieldslice.cpp
    reversi.cpp
)
target_include_directories(flipstone PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${collection2_SOURCE_DIR}/include
)
target_compile_options(flipstone PRIVATE
    -Wall
)
if(FLIPSTONE_USE_STL OR FLIPSTONE_BUILD_TESTS)
    target_compile_definitions(flipstone PRIVATE
        FLIPSTONE_USE_STL=1
    )
endif()
