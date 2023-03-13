/// @file
/// @brief リバーシのメインロジック
///

#include "reversi.hpp"

using namespace collection2;

namespace simple_reversi {

void Reversi::initField() {
    // 石をひっぺがす
    for (int8_t y = 0; y < 8; y++) {
        for (int8_t x = 0; x < 8; x++) {
            *field.referCell(Point(x, y)) = Cell::Empty;
        }
    }

    // 初期状態の石を配置
    *field.referCell(Point(3, 3)) = Cell::Black;
    *field.referCell(Point(4, 3)) = Cell::White;
    *field.referCell(Point(3, 4)) = Cell::White;
    *field.referCell(Point(4, 4)) = Cell::Black;
}

Cell Reversi::referCell(const Point& point) const {
    Cell cell;
    field.readCell(point, cell);
    return cell;
}

uint8_t Reversi::createFlippablePointsList(
    const Point& point,
    const Cell& cell,
    const Direction& direction,
    List<Point>* flippablePointsList) const {
    // スライスを作成し、サンプル
    FieldSlice slice;

    // サンプル結果が3未満 -> 端に到達するまで1マスしかない = ひっくり返せる石はない
    if (field.sample(point, direction, slice) < 3) {
        return 0;
    }

    // 開始点にすでに石が置かれている -> ひっくり返しようがない
    if (slice.sample[0] != Cell::Empty) {
        return 0;
    }

    // 置けるのは白か黒だけ
    if (cell == Cell::Empty) {
        return 0;
    }

    // 開始点の次から順に調べていく
    const Cell opposite = (cell == Cell::Black) ? Cell::White : Cell::Black;
    uint8_t flippableCount = 0;
    for (int8_t index = 1; index < 9; index++) {
        Cell currentCell = slice.sample[index];

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

    // ひっくり返せないなら、何もしない
    if (flippableCount == 0) {
        return 0;
    }

    // リスト追加はスキップできる
    if (flippablePointsList == nullptr) {
        return flippableCount;
    }

    // ひっくり返せる石の位置をリストに追加
    Point candidatePoint = slice.startPoint;
    candidatePoint.advance(slice.direction);  // 一つ次から
    for (uint8_t i = 0; i < flippableCount; i++) {
        flippablePointsList->append(candidatePoint);
        candidatePoint.advance(slice.direction);
    }
    return flippableCount;
}

uint8_t Reversi::createFlippablePointsList(
    const Point& point,
    const Cell& cell,
    List<Point>* flippablePointsList) const {
    // 探索方向を定義
    Direction directions[8] = {
        Direction(1, 0), Direction(-1, 0), Direction(0, 1), Direction(0, -1),
        Direction(1, 1), Direction(-1, 1), Direction(1, -1), Direction(-1, -1)};

    uint8_t allTogglableCount = 0;
    for (uint8_t i = 0; i < 8; i++) {
        const Direction direction = directions[i];
        allTogglableCount += createFlippablePointsList(point, cell, direction, flippablePointsList);
    }
    return allTogglableCount;
}

void Reversi::putStone(const Point& point, const Cell& cell) {
    const uint8_t pointsListSize = 20;
    Node<Point> flipPointsData[pointsListSize];
    List<Point> flipPointsList(flipPointsData, pointsListSize);
    if (createFlippablePointsList(point, cell, &flipPointsList) == 0) {
        return;
    }

    auto* listCursor = flipPointsList.head();
    while (listCursor != nullptr) {
        flipStone(listCursor->element);
        listCursor = listCursor->next;
    }
}

Cell Reversi::flipStone(const Point& point) {
    auto cellPtr = field.referCell(point);
    if (cellPtr == nullptr || *cellPtr == Cell::Empty) {
        return Cell::Empty;
    }
    auto opposite = (*cellPtr == Cell::Black) ? Cell::White : Cell::Black;
    *cellPtr = opposite;
    return opposite;
}

}  // namespace simple_reversi
