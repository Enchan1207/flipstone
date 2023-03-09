/// @file
/// @brief フィールドから抽出したセル
///

#ifndef SIMPLE_REVERSI_FIELD_SLICE_H
#define SIMPLE_REVERSI_FIELD_SLICE_H

#include "cell.hpp"
#include "direction.hpp"
#include "point.hpp"

namespace simple_reversi {

/// @brief フィールドから抽出したセル
struct FieldSlice {
    /// @brief 開始点
    Point startPoint;

    /// @brief 方向
    Direction direction;

    /// @brief セル
    Cell sample[9] = {Cell::Empty};

    FieldSlice() : startPoint(-1, -1), direction(0, 0){};
};

}  // namespace simple_reversi

#endif
