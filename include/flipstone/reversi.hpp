/// @file
/// @brief リバーシ
///

#ifndef FLIPSTONE_REVERSI_H
#define FLIPSTONE_REVERSI_H

#include <collection2/list.hpp>

#include "field.hpp"

namespace flipstone {

/// @brief リバーシ
class Reversi final {
   private:
    /// @brief フィールド
    Field field;

    /**
     * @brief 指定位置の石をひっくり返す
     *
     * @param point 位置
     * @return Cell ひっくり返した後の状態
     *
     * @note この関数はルールを考慮しません(単純に石をひっくり返すだけ)。
     *       石が置かれていない場合は Cell::Empty が返ります。
     */
    Cell flipStone(const Point& point);

    /**
     * @brief ある石を置いたときに特定方向にひっくり返せる位置のリストを作成する
     *
     * @param point 石を置く位置
     * @param cell 置く石
     * @param direction 探索方向
     * @param flippablePointsList 結果格納先 (nullable)
     * @return int8_t 個数
     *
     * @note リストに追加される数は最大でも6です(オセロのルール上)。
     *       第三引数にnullptrが渡されると、ひっくり返る石の個数のみが返ります。
     */
    uint8_t createFlippablePointsList(
        const Point& point,
        const Cell& cell,
        const Direction& direction,
        collection2::List<Point>* flippablePointsList) const;

   public:
    /**
     * @brief フィールドをゲーム開始可能な状態に初期化する
     *
     * @note フィールド上に置かれているすべての石が削除され、初期状態の4つの石が配置されます。
     */
    void initField();

    /**
     * @brief 指定位置の状態を取得
     *
     * @param point 位置
     * @return Cell 状態
     * @note 範囲外の位置に対してはCell::Emptyが返ります。
     */
    Cell referCell(const Point& point) const;

    /**
     * @brief ある石を置いたときに全方向についてひっくり返せる位置のリストを作成する
     *
     * @param point 位置
     * @param cell 置く石の種類
     * @param flippablePointsList 結果格納先 (nullable)
     * @return int8_t 個数
     *
     * @note リストに追加される数は最大でも18です(オセロのルール上)。
     *       第三引数にnullptrが渡されると、ひっくり返る石の個数のみが返ります。
     */
    uint8_t createFlippablePointsList(
        const Point& point,
        const Cell& cell,
        collection2::List<Point>* flippablePointsList) const;

    /**
     * @brief 特定位置に石を置く
     *
     * @param point 位置
     * @param cell 置く石の種類
     *
     * @note この関数により、オセロのルールに従い盤面が更新されます。
     */
    void putStone(const Point& point, const Cell& cell);

    /**
     * @brief 特定の石を置ける場所があるか調べる
     *
     * @param cell 置く石の種類
     * @return bool
     *
     * @note この関数はオセロのルールに従い評価を行います。フィールドに空きマスがあっても、
     *       ルール上置ける箇所がない場合はfalseが返ります。
     */
    bool hasPlacablePoint(const Cell& cell) const;

    /**
     * @brief 指定された状態が占めるフィールド上のマスの合計数を求める
     *
     * @param state 対象の状態
     * @return uint8_t 合計
     */
    uint8_t totalizeCell(const Cell state) const;
};

}  // namespace flipstone

#endif /* FLIPSTONE_REVERSI_H */