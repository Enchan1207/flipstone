//
// ゲームロジックのテスト
//
#include <gtest/gtest.h>

#include "reversi.hpp"

using namespace simple_reversi;

TEST(ReversiTest, testFlipcountCalc) {
    Reversi reversi;
    reversi.initField();

    // 最初に置かれた4つの石からたどっていく

    // 左上の黒い石
    EXPECT_EQ(reversi.createFlippablePointsList(Point(2, 3), Cell::White, nullptr), 1);
    EXPECT_EQ(reversi.createFlippablePointsList(Point(3, 2), Cell::White, nullptr), 1);
    EXPECT_EQ(reversi.createFlippablePointsList(Point(2, 3), Cell::Black, nullptr), 0);

    // 左下の白い石
    EXPECT_EQ(reversi.createFlippablePointsList(Point(2, 4), Cell::Black, nullptr), 1);
    EXPECT_EQ(reversi.createFlippablePointsList(Point(3, 5), Cell::Black, nullptr), 1);
    EXPECT_EQ(reversi.createFlippablePointsList(Point(2, 4), Cell::White, nullptr), 0);
}
