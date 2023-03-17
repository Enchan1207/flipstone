/// @file
/// @brief フィールドから抽出したセル
///

#ifndef FLIPSTONE_FIELD_SLICE_H
#define FLIPSTONE_FIELD_SLICE_H

#include <cstddef>

#include "cell.hpp"
#include "direction.hpp"
#include "point.hpp"

namespace flipstone {

/// @brief フィールドスライス
class FieldSlice final {
   private:
    /// @brief 内部サンプルデータ領域
    Cell internalSampleData[9] = {Cell::Empty};

   public:
    /// @brief 開始点
    const Point startPoint = Point(-1, -1);

    /// @brief 方向
    const Direction direction = Direction(0, 0);

    /// @brief 抽出したセルの有効長
    const uint8_t sampleSize = 0;

    /**
     * @brief フィールドスライスを作成する
     *
     * @param point 開始点
     * @param direction 方向
     * @param sample サンプル結果
     * @param sampleSize sampleの長さ
     */
    FieldSlice(const Point& point,
               const Direction& direction,
               const Cell* sample,
               const uint8_t sampleSize);

    /**
     * @brief サンプルの指定インデックスにある値を返す
     *
     * @param index インデックス
     * @return Cell 該当するサンプルの値
     */
    Cell sample(uint8_t index) const;

    /**
     * @brief 指定された石を開始点に置いた場合にひっくり返せる石の数を返す
     *
     * @param stone 置く石
     * @return uint8_t ひっくり返せる石の数
     */
    uint8_t getFlippableCount(const Cell stone) const;
};

}  // namespace flipstone

#endif
