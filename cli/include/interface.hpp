/// @file
/// @brief CLIインタフェース
///
#ifndef CLI_DUMP_H
#define CLI_DUMP_H

#include <cstddef>

#include "reversi.hpp"

/**
 * @brief フィールドの状態をコンソールにダンプする
 *
 * @param f ダンプ対象のフィールド
 * @param targetStone この引数に指定した石を置ける場所をハイライトする REVERSI_NONE を渡すとハイライトしない
 */
void dumpField(Field *f, unsigned char targetStone);

/**
 * @brief フィールドに石を置く場所をコンソールから入力する
 *
 * @param f 配置対象のフィールド
 * @param p 置く場所
 * @param targetStone 置きたい石
 */
void inputPointToPlace(Field *f, Point *p, unsigned char targetStone);

#endif /* CLI_DUMP_H */
