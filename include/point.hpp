/// @file
/// @brief フィールド上の点
///

#ifndef SIMPLE_REVERSI_POINT_H
#define SIMPLE_REVERSI_POINT_H

#include <cstdint>

namespace simple_reversi {

/// @brief フィールド上の点を表す構造体
struct Point {
    int8_t x = 0;
    int8_t y = 0;

    Point() = default;

    /**
     * @brief 座標を指定してPointオブジェクトを初期化
     *
     * @param x x座標
     * @param y y座標
     */
    Point(int8_t x, int8_t y) : x(x), y(y){};

    /**
     * @brief 指定方向に座標を進める
     *
     * @param direction 方向
     */
    void advance(const Direction& direction) {
        x += direction.vx();
        y += direction.vy();
    }
};

}  // namespace simple_reversi

#endif
