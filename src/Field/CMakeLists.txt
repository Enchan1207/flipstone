#
# Cmake
#

## 環境設定

# バージョン
cmake_minimum_required(VERSION 3.21)

# プロジェクト名, 言語
project(Field C)

## 生成する実行ファイルの構成
include_directories(../Point)
add_library(field Field.h Field.c Search.c Logic.c Access.c)
target_include_directories(field PUBLIC ./)
target_link_directories(field PUBLIC ./)
