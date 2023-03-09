#
# flipstone tests
#
cmake_minimum_required(VERSION 3.0)

# GoogleTestのフェッチと有効化
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

## 外部依存関係を追加...

# テストターゲットの構成
add_executable(flipstone_test)
target_sources(flipstone_test PRIVATE
    test_direction.cpp
    test_field.cpp
    test_point.cpp
    test_reversi.cpp
)
target_link_libraries(flipstone_test PRIVATE
    GTest::gtest_main
    collection2
    reversi
)
target_include_directories(flipstone_test
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${GTEST_INCLUDE_DIRS}
)

# テストの実行
gtest_discover_tests(flipstone_test)
