//
// 座標構造体のテスト
//
#include <gtest/gtest.h>

#include <climits>

#include "direction.hpp"
#include "point.hpp"

using namespace flipstone;

TEST(PointTest, testAdvanceValidRange) {
    Point point(3, 3);
    EXPECT_TRUE(point.advance(Direction(1, -1)));
    EXPECT_EQ(point.x, 4);
    EXPECT_EQ(point.y, 2);
}

TEST(PointTest, testAdvanceEdgeCase) {
    Point point(CHAR_MAX, CHAR_MIN);
    EXPECT_FALSE(point.advance(Direction(1, -1)));
    EXPECT_EQ(point.x, CHAR_MAX);
    EXPECT_EQ(point.y, CHAR_MIN);
}

TEST(PointTest, testCompare) {
    Point point1(5, 7);
    Point point2(5, 7);
    Point point3(7, 5);
    EXPECT_EQ(point1, point2);
    EXPECT_NE(point1, point3);
}
