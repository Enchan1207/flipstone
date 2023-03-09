/// @file
/// @brief 方向ベクトル
///

#ifndef SIMPLE_REVERSI_DIRECTION_H
#define SIMPLE_REVERSI_DIRECTION_H

#include <cstdint>

namespace simple_reversi {

/// @brief 方向ベクトルを扱う構造体
struct Direction {
   private:
    /// @brief 方向成分を管理するメモリ
    /// @note 成分は __DxSx__DySy の形式で格納されます。
    ///       'D' ビットはベクトルの大きさを、'S' ビットはベクトルの方向を格納します。
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
        const int8_t vecX = static_cast<int8_t>(vx > 0) - static_cast<int8_t>(vx < 0);
        const int8_t vecY = static_cast<int8_t>(vy > 0) - static_cast<int8_t>(vy < 0);

        // 値を設定していく
        uint8_t v = 0x00;
        v |= static_cast<uint8_t>(vecX > 0) << 5;
        v |= static_cast<uint8_t>(vecX != 0) << 4;
        v |= static_cast<uint8_t>(vecY > 0) << 1;
        v |= static_cast<uint8_t>(vecY != 0) << 0;
        vector = v;
    }

    /**
     * @brief x方向
     *
     * @return int8_t
     */
    int8_t vx() const {
        // ビット列をばらして大きさと方向の成分を抽出
        bool hasMagnitude = vector & (1 << 4);
        bool isPositive = vector & (1 << 5);
        if (!hasMagnitude) {
            return 0;
        }
        return isPositive ? 1 : -1;
    }

    /**
     * @brief y方向
     *
     * @return int8_t
     */
    int8_t vy() const {
        // ビット列をばらして大きさと方向の成分を抽出
        bool hasMagnitude = vector & (1 << 0);
        bool isPositive = vector & (1 << 1);
        if (!hasMagnitude) {
            return 0;
        }
        return isPositive ? 1 : -1;
    }
};

}  // namespace simple_reversi

#endif
