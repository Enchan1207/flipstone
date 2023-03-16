/// @file
/// @brief フィールド上のマス
///

#ifndef FLIPSTONE_CELL_H
#define FLIPSTONE_CELL_H

#include <stdint.h>

namespace flipstone {

/// @brief フィールド上の一つのマス
enum class Cell : uint8_t {
    /// @brief 何も置かれていない空きのマス、または範囲外
    Empty,

    /// @brief 黒い石が置かれている
    Black,

    /// @brief 白い石が置かれている
    White
};

}  // namespace flipstone

#endif
