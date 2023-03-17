//
// ゲームロジックのテスト
//
#include <gtest/gtest.h>

#include <collection2/list.hpp>
#include <vector>

#include "flipstone/reversi.hpp"

using namespace flipstone;
using namespace collection2;

TEST(ReversiTest, testFlipcountCalc) {
    Reversi reversi;
    reversi.initField();

    // 最初に置かれた4つの石からたどっていく

    // 左上の黒い石
    EXPECT_EQ(reversi.getFlippableStonesCount(Point(2, 3), Cell::White), 1);
    EXPECT_EQ(reversi.getFlippableStonesCount(Point(3, 2), Cell::White), 1);
    EXPECT_EQ(reversi.getFlippableStonesCount(Point(2, 3), Cell::Black), 0);

    // 左下の白い石
    EXPECT_EQ(reversi.getFlippableStonesCount(Point(2, 4), Cell::Black), 1);
    EXPECT_EQ(reversi.getFlippableStonesCount(Point(3, 5), Cell::Black), 1);
    EXPECT_EQ(reversi.getFlippableStonesCount(Point(2, 4), Cell::White), 0);
}

TEST(ReversiTest, testCreateFlippablePointList) {
    Reversi reversi;
    reversi.initField();

    const uint8_t pointsListSize = 20;
    Node<Point> flipPointsData[pointsListSize];
    List<Point> flipPointsList(flipPointsData, pointsListSize);
    reversi.createFlippablePointsList(Point(2, 3), Cell::White, flipPointsList);

    EXPECT_EQ(flipPointsList.amount(), 1);
    EXPECT_EQ(reversi.referCell(flipPointsList.head()->element), Cell::Black);
}

TEST(ReversiTest, testCreateFlippablePointVector) {
    Reversi reversi;
    reversi.initField();

    std::vector<Point> pointVector;
    reversi.createFlippablePointsVector(Point(2, 3), Cell::White, pointVector);

    EXPECT_EQ(pointVector.size(), 1);
    EXPECT_EQ(reversi.referCell(pointVector[0]), Cell::Black);
}

TEST(ReversiTest, testPutStone) {
    Reversi reversi;
    reversi.initField();

    EXPECT_TRUE(reversi.putStone(Point(2, 3), Cell::White));
    EXPECT_EQ(reversi.referCell(Point(2, 3)), Cell::White);
}
