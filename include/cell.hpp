/// @file
/// @brief フィールド上のマス
///

#ifndef SIMPLE_REVERSI_CELL_H
#define SIMPLE_REVERSI_CELL_H

#include <cstdint>

namespace simple_reversi {

/// @brief フィールド上の一つのマス
enum class Cell : uint8_t {
    /// @brief 何も置かれていない空きのマス、または範囲外
    Empty,

    /// @brief 黒い石が置かれている
    Black,

    /// @brief 白い石が置かれている
    White
};

}  // namespace simple_reversi

#endif
