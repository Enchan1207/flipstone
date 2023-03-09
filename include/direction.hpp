/// @file
/// @brief 方向ベクトル
///

#ifndef SIMPLE_REVERSI_DIRECTION_H
#define SIMPLE_REVERSI_DIRECTION_H

#include <cstdint>

/// @brief 方向ベクトルを扱う構造体
struct Direction {
   private:
    /// @brief 方向成分を管理するメモリ
    /// @note 成分は __DxSx__DySy の形式で格納されます。
    uint8_t vector = 0x00;

   public:
    Direction() = default;

    /**
     * @brief 方向オブジェクトを初期化
     *
     * @param vx x方向
     * @param vy y方向
     *
     * @note 各引数には-1, 0, 1を渡すことができます。それ以外の値を渡した場合は符号のみがチェックされます。
     */
    Direction(const int8_t vx, const int8_t vy) {
        // 方向を正規化
        const int8_t vecX = (vx > 0) - (vx < 0);
        const int8_t vecY = (vy > 0) - (vy < 0);

        // 値を設定していく
        uint8_t v = 0x00;
        v |= (vecX < 0) << 5;
        v |= (vecX != 0) << 4;
        v |= (vecY < 0) << 1;
        v |= (vecY != 0) << 0;
        vector = v;
    }

    /**
     * @brief x方向
     *
     * @return int8_t
     */
    int8_t vx() const {
        // ビット列をばらして大きさと方向の成分を抽出
        bool hasXMagnitude = vector & (1 << 4);
        bool isXNegative = vector & (1 << 5);
        if (!hasXMagnitude) {
            return 0;
        }
        return isXNegative ? -1 : 1;
    }

    /**
     * @brief y方向
     *
     * @return int8_t
     */
    int8_t vy() const {
        // ビット列をばらして大きさと方向の成分を抽出
        bool hasYMagnitude = vector & (1 << 0);
        bool isYNegative = vector & (1 << 1);
        if (!hasYMagnitude) {
            return 0;
        }
        return isYNegative ? -1 : 1;
    }
};

#endif
