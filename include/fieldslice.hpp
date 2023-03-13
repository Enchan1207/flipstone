/// @file
/// @brief フィールドから抽出したセル
///

#ifndef FLIPSTONE_FIELD_SLICE_H
#define FLIPSTONE_FIELD_SLICE_H

#include "cell.hpp"
#include "direction.hpp"
#include "point.hpp"

namespace flipstone {

/// @brief フィールドから抽出したセル
struct FieldSlice final {
    /// @brief 開始点
    Point startPoint = Point(-1, -1);

    /// @brief 方向
    Direction direction = Direction(0, 0);

    /// @brief セル
    Cell sample[9] = {Cell::Empty};
};

}  // namespace flipstone

#endif
