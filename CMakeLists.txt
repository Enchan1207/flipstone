#
# Cmake
#

## 環境設定

# バージョン
cmake_minimum_required(VERSION 3.21)

# プロジェクト名, 言語
project(linear_search C)

# インクルードディレクトリ
include_directories(/usr/local/include)

# リンクディレクトリ
link_directories(/usr/local/lib)

# サブディレクトリを追加
add_subdirectory(src/Field)
add_subdirectory(src/Point)

# ターゲット生成
add_executable(main.out src/main.c)

# ターゲットにライブラリをリンク
target_link_libraries(main.out field point urandom)
