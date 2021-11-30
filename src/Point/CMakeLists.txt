#
# Cmake
#

## 環境設定

# バージョン
cmake_minimum_required(VERSION 3.21)

# プロジェクト名, 言語
project(Point C)

## 生成する実行ファイルの構成
add_library(point Point.h Point.c)
target_include_directories(point PUBLIC ./)
target_link_directories(point PUBLIC ./)
