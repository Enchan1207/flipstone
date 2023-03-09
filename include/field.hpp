/// @file
/// @brief フィールド
///

#ifndef FLIPSTONE_FIELD_H
#define FLIPSTONE_FIELD_H

#include <cstddef>
#include <cstdint>

#include "cell.hpp"
#include "direction.hpp"
#include "fieldslice.hpp"
#include "point.hpp"

namespace flipstone {

/// @brief フィールド
class Field {
   private:
    /// @brief 内部データ管理領域
    Cell internalFieldData[64] = {Cell::Empty};

   public:
    /**
     * @brief 座標からセルへのポインタを取得
     *
     * @param point 座標
     * @return Cell* セルへのポインタ
     * @note 範囲外の座標に対してはnullptrが返ります。
     */
    Cell* referCell(const Point& point);

    /**
     * @brief セルへのポインタから座標を取得
     *
     * @param cell セル
     * @param point 座標
     * @return bool ポインタがフィールドの範囲外を指している場合はfalseが返ります。
     *
     * @note ポインタに不正な値が渡された場合、pointの値は更新されません。
     */
    bool referPoint(const Cell* cell, Point& point) const;

    /**
     * @brief 指定された状態が占めるフィールド上のマスの合計数を求める
     *
     * @param state 対象の状態
     * @return uint8_t 合計
     *
     * @note どちらの石がより多く置かれているか計算するために使うことを想定しています。
     */
    uint8_t totalizeCell(const Cell state) const;

    /**
     * @brief 開始点と方向を指定してフィールド内の石の状態をサンプリングする
     *
     * @param point 開始点
     * @param direction 方向
     * @param slice 結果格納先
     * @return int8_t 探索できた長さ
     *
     * @note フィールド端に到達するまで探索は続きます(探索結果の最大長は8となります)。
     */
    int8_t sample(const Point& point, const Direction& direction, FieldSlice& slice);
};

}  // namespace flipstone

#endif
