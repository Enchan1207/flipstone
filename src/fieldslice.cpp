/// @brief フィールドの一部を切り出したクラス
///

#include "flipstone/fieldslice.hpp"

namespace flipstone {

FieldSlice::FieldSlice(const Point& point,
                       const Direction& direction,
                       const Cell* sample,
                       const uint8_t sampleSize)
    : startPoint(point), direction(direction), sampleSize(sampleSize) {
    for (size_t i = 0; i < 9; i++) {
        // 範囲外はEmptyで埋める
        internalSampleData[i] = (i < sampleSize) ? sample[i] : Cell::Empty;
    }
};

Cell FieldSlice::sample(uint8_t index) const {
    if (index > 8) {
        return Cell::Empty;
    }
    return internalSampleData[index];
}

uint8_t FieldSlice::getFlippableCount(const Cell stone) const {
    // 長さ3未満 = 端に到達するまで1マスしかない -> ひっくり返せる石はない
    if (sampleSize < 3) {
        return 0;
    }

    // 開始点にすでに石が置かれている -> ひっくり返しようがない
    if (sample(0) != Cell::Empty) {
        return 0;
    }

    // 置けるのは白か黒だけ
    if (stone == Cell::Empty) {
        return 0;
    }

    // 開始点の次から順に調べていく
    const Cell opposite = (stone == Cell::Black) ? Cell::White : Cell::Black;
    uint8_t flippableCount = 0;
    for (int8_t index = 1; index < 9; index++) {
        const Cell currentCell = sample(index);

        // 相手の石が続く限り進める
        if (currentCell == opposite) {
            flippableCount++;
            continue;
        }

        // 空白が来たらカウンタをリセットする
        if (currentCell == Cell::Empty) {
            flippableCount = 0;
        }
        break;
    }

    return flippableCount;
}

}  // namespace flipstone
