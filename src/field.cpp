/// @file
/// @brief フィールド初期化・参照・集計
///

#include "flipstone/field.hpp"

namespace flipstone {

bool Field::convertPointToInternalDataIndex(const Point& point, uint8_t& index) const {
    if (point.x < 0 || point.x > 7 || point.y < 0 || point.y > 7) {
        return false;
    }
    const auto candidate = point.y * 8 + point.x;
    if (candidate < 0 || candidate > 63) {
        return false;
    }
    index = static_cast<uint8_t>(candidate);
    return true;
}

Cell* Field::referCell(const Point& point) {
    uint8_t index = 0;
    if (!convertPointToInternalDataIndex(point, index)) {
        return nullptr;
    }
    return internalFieldData + index;
}

bool Field::readCell(const Point& point, Cell& cell) const {
    uint8_t index = 0;
    if (!convertPointToInternalDataIndex(point, index)) {
        return false;
    }
    cell = internalFieldData[index];
    return true;
}

bool Field::referPoint(const Cell* cell, Point& point) const {
    auto diff = cell - internalFieldData;
    if (diff < 0 || diff > 63) {
        return false;
    }
    point.x = diff % 8;
    point.y = static_cast<int8_t>(diff / 8);
    return true;
}

uint8_t Field::totalizeCell(const Cell state) const {
    uint8_t sum = 0;
    for (uint8_t i = 0; i < 64; i++) {
        if (internalFieldData[i] != state) {
            continue;
        }
        sum++;
    }
    return sum;
}

FieldSlice Field::slice(const Point& point, const Direction& direction) const {
    // 端または石が置かれているところまで読む
    Cell sample[9];
    Point samplePoint = point;
    uint8_t availableSampleSize = 0;
    Cell cell = Cell::Empty;
    while (readCell(samplePoint, cell)) {
        sample[availableSampleSize] = cell;
        samplePoint.advance(direction);
        availableSampleSize++;
    }

    // 結果を生成してreturn
    return FieldSlice(point, direction, sample, availableSampleSize);
}

}  // namespace flipstone
