#
# cli sources
#
cmake_minimum_required(VERSION 3.0)

## usageを含めたサンプル
add_executable(main)
target_sources(main PRIVATE
    main.cpp
    interface.cpp
    reversi_ai.cpp
)
target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/cli/include
)
target_compile_options(main PRIVATE
    -Wall
)
target_link_libraries(main PRIVATE
    reversi
)
