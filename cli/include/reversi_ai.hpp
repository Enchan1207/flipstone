/// @file
/// @brief リバーシAI
///
#ifndef CLI_REVERSI_AI_H
#define CLI_REVERSI_AI_H

#include <cstddef>

#include "reversi.hpp"

/**
 * @brief AIが石を置く位置を決める
 *
 * @param f 対象のフィールド
 * @param p 置く場所
 * @param value 置きたい石
 */
void decideStonePosition(Field* f, Point* p, uint8_t value);

/**
 * @brief 現時点で石を置けるすべての場所を探索
 *
 * @param f 対象のフィールド
 * @param value 置きたい石
 * @param buf 座標バッファ
 * @param bufferLength 座標バッファ長さ
 * @return 置ける場所の数
 */
unsigned int searchPlacablePosition(Field* f, uint8_t value, Point* buf, unsigned int bufferLength);

#endif /* CLI_REVERSI_AI_H */
