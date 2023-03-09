/// @file
/// @brief フィールド初期化・参照・集計
///

#include "field.hpp"

namespace simple_reversi {

void Field::initField() {
    for (size_t i = 0; i < 64; i++) {
        internalFieldData[i] = Cell::Empty;
    }
}

Cell* Field::referCell(const Point& point) {
    auto candidate = point.y * 8 + point.x;
    if (candidate < 0 || candidate > 63) {
        return nullptr;
    }
    return internalFieldData + candidate;
}

bool Field::referPoint(const Cell* cell, Point& point) const {
    auto diff = cell - internalFieldData;
    if (diff < 0 || diff > 63) {
        return false;
    }
    point.x = diff % 8;
    point.y = diff / 8;
    return true;
}

uint8_t Field::totalizeCell(const Cell state) const {
    auto sum = 0;
    for (size_t i = 0; i < 64; i++) {
        if (internalFieldData[i] != state) {
            continue;
        }
        sum++;
    }
    return sum;
}

int8_t Field::sample(const Point& point, const Direction& direction, FieldSlice& slice) {
    // sliceに情報を設定
    slice.startPoint = point;
    slice.direction = direction;

    // 端に到達するまで読む
    Point current = point;
    int8_t sampleIndex = 0;
    while (true) {
        Cell* cell = referCell(current);
        if (cell == nullptr) {
            break;
        }
        slice.sample[sampleIndex] = *cell;
        current.advance(direction);
    }
    return sampleIndex;
}

}  // namespace simple_reversi
