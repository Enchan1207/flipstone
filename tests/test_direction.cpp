//
// 方向構造体のテスト
//
#include <gtest/gtest.h>

#include "direction.hpp"

TEST(DirectionTest, testInstantiate) {
    Direction dir(0, 0);
    EXPECT_EQ(dir.vx(), 0);
    EXPECT_EQ(dir.vy(), 0);
}

TEST(DirectionTest, testValidDirections) {
    Direction dir1(1, 0);
    EXPECT_EQ(dir1.vx(), 1);
    EXPECT_EQ(dir1.vy(), 0);

    Direction dir2(0, -1);
    EXPECT_EQ(dir2.vx(), 0);
    EXPECT_EQ(dir2.vy(), -1);
}

TEST(DirectionTest, testInvalidDirections) {
    Direction dir1(2, 0);
    EXPECT_EQ(dir1.vx(), 1);
    EXPECT_EQ(dir1.vy(), 0);

    Direction dir2(0, -2);
    EXPECT_EQ(dir2.vx(), 0);
    EXPECT_EQ(dir2.vy(), -1);
}
