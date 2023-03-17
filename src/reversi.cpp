/// @file
/// @brief リバーシのメインロジック
///

#include "flipstone/reversi.hpp"

using namespace collection2;

namespace flipstone {

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

uint8_t Reversi::getFlippableStonesCount(const Point& point, const Cell& cell) const {
    uint8_t summary = 0;
    for (uint8_t i = 0; i < 8; i++) {
        const Direction direction = allDirections[i];
        const FieldSlice slice = field.slice(point, direction);
        summary += slice.getFlippableCount(cell);
    }
    return summary;
}

uint8_t Reversi::createFlippablePointsList(
    const Point& point,
    const Cell& cell,
    List<Point>& flippablePointsList) const {
    uint8_t summary = 0;
    for (uint8_t i = 0; i < 8; i++) {
        // 指定方向にスライス
        const Direction direction = allDirections[i];
        const FieldSlice slice = field.slice(point, direction);
        const uint8_t flippableCount = slice.getFlippableCount(cell);
        summary += flippableCount;

        // 得られた結果をリストに追加していく
        Point startPoint = slice.startPoint;
        startPoint.advance(slice.direction);
        for (uint8_t j = 0; j < flippableCount; j++) {
            flippablePointsList.append(startPoint);
            startPoint.advance(slice.direction);
        }
    }
    return summary;
}

bool Reversi::putStone(const Point& point, const Cell& cell) {
    // ひっくり返せる場所のリストを取得
    const uint8_t pointsListSize = 20;
    Node<Point> flipPointsData[pointsListSize];
    List<Point> flipPointsList(flipPointsData, pointsListSize);
    if (createFlippablePointsList(point, cell, flipPointsList) == 0) {
        return false;
    }

    // 足元に石を置き
    *field.referCell(point) = cell;

    // リストを順番に辿ってひっくり返していく
    auto* listCursor = flipPointsList.head();
    while (listCursor != nullptr) {
        flipStone(listCursor->element);
        listCursor = listCursor->next;
    }
    return true;
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

bool Reversi::hasPlacablePoint(const Cell& cell) const {
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            const flipstone::Point point(x, y);
            if (getFlippableStonesCount(point, cell) > 0) {
                return true;
            }
        }
    }
    return false;
}

uint8_t Reversi::totalizeCell(const Cell state) const {
    return field.totalizeCell(state);
}

}  // namespace flipstone
