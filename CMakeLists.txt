#
# Cmake
#

## 環境設定

# バージョン
cmake_minimum_required(VERSION 3.21)

# プロジェクト名, 言語
project(linear_search C)

## 生成する実行ファイルの構成
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(main.out src/main.c src/Field.h src/Field.c src/Search.c src/Point.h)
target_link_libraries(main.out urandom)
