#
# cli
#
cmake_minimum_required(VERSION 3.0)

## usageを含めたサンプル
add_executable(main)
target_sources(main PRIVATE
    main.cpp
)
target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
target_compile_options(main PRIVATE
    -Wall
)
target_link_libraries(main PRIVATE
    simple_reversi
)
