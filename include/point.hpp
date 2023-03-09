/// @file
/// @brief フィールド上の点
///

#ifndef FLIPSTONE_POINT_H
#define FLIPSTONE_POINT_H

#include <climits>
#include <cstdint>

#include "direction.hpp"

namespace flipstone {

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
     * @return bool オーバーフローの可能性がある場合はfalseが返ります。またその際値は変化しません。
     */
    bool advance(const Direction& direction) {
        // 各軸オーバーフロー対策
        bool isXWillInRangeAfterAdvance = (direction.vx() > 0 && x < CHAR_MAX) || (direction.vx() < 0 && x > CHAR_MIN);
        bool isYWillInRangeAfterAdvance = (direction.vy() > 0 && y < CHAR_MAX) || (direction.vy() < 0 && y > CHAR_MIN);

        // オーバーフローしない場合のみ進める
        if (isXWillInRangeAfterAdvance) {
            x += direction.vx();
        }
        if (isYWillInRangeAfterAdvance) {
            y += direction.vy();
        }

        return isXWillInRangeAfterAdvance && isYWillInRangeAfterAdvance;
    }

    bool operator==(Point point) const {
        return this->x == point.x && this->y == point.y;
    }

    bool operator!=(Point point) const {
        return !(this->operator==(point));
    }
};

}  // namespace flipstone

#endif
