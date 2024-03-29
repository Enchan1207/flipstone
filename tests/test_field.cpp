//
// フィールドのテスト
//
#include <gtest/gtest.h>
#include <stdint.h>

#include <iostream>

#include "flipstone/field.hpp"
#include "flipstone/fieldslice.hpp"

using namespace flipstone;

TEST(FieldTest, testReferenceCell) {
    Field field;

    Point insideField1(0, 0);
    EXPECT_NE(field.referCell(insideField1), nullptr);

    Point insideField2(7, 7);
    EXPECT_NE(field.referCell(insideField2), nullptr);

    Point outsideField1(0, -1);
    EXPECT_EQ(field.referCell(outsideField1), nullptr);

    Point outsideField2(-1, 0);
    EXPECT_EQ(field.referCell(outsideField2), nullptr);

    Point outsideField3(8, 0);
    EXPECT_EQ(field.referCell(outsideField3), nullptr);

    Point outsideField4(0, 8);
    EXPECT_EQ(field.referCell(outsideField4), nullptr);
}

TEST(FieldTest, testReferencePoint) {
    Field field;

    const Point point(2, 2);
    const Cell* cellPtr = field.referCell(point);
    EXPECT_NE(field.referCell(point), nullptr);

    Point referredValidPoint(0, 0);
    EXPECT_TRUE(field.referPoint(cellPtr, referredValidPoint));
    EXPECT_EQ(point, referredValidPoint);

    Point referredInvalidPoint(0, 0);
    Cell cell = Cell::Black;
    EXPECT_FALSE(field.referPoint(&cell, referredInvalidPoint));
}

TEST(FieldTest, testReferenceConversion) {
    Field field;

    for (int8_t y = 0; y < 8; y++) {
        for (int8_t x = 0; x < 8; x++) {
            const Point point1(x, y);
            const auto* cellPtr = field.referCell(point1);
            EXPECT_NE(cellPtr, nullptr);

            Point point2(0, 0);
            EXPECT_TRUE(field.referPoint(cellPtr, point2));
            EXPECT_EQ(point1, point2);
        }
    }
}

TEST(FieldTest, testTotalize) {
    // それっぽいフィールドを作る
    Field field;
    for (int8_t y = 0; y < 8; y++) {
        for (int8_t x = 0; x < 8; x++) {
            auto* cellPtr = field.referCell(Point(x, y));
            EXPECT_NE(cellPtr, nullptr);
            *cellPtr = ((x + y) % 2 == 0) ? Cell::Black : Cell::White;
        }
    }

    // それぞれ1:1になっているはず
    EXPECT_EQ(field.totalizeCell(Cell::Black), 32);
    EXPECT_EQ(field.totalizeCell(Cell::White), 32);
    EXPECT_EQ(field.totalizeCell(Cell::Empty), 0);
}

TEST(FieldTest, testSample) {
    // それっぽいフィールドを作る
    Field field;
    for (int8_t y = 0; y < 8; y++) {
        for (int8_t x = 0; x < 8; x++) {
            auto* cellPtr = field.referCell(Point(x, y));
            EXPECT_NE(cellPtr, nullptr);
            *cellPtr = ((x + y) % 2 == 0) ? Cell::Black : Cell::White;
        }
    }

    // いろんな方向から切り出してみる
    FieldSlice fieldSlice1 = field.slice(Point(0, 0), Direction(0, 1));
    EXPECT_EQ(fieldSlice1.sampleSize, 8);
    for (size_t i = 0; i < 8; i++) {
        EXPECT_EQ(fieldSlice1.sample(i), (i % 2 == 0) ? Cell::Black : Cell::White);
    }
    EXPECT_EQ(fieldSlice1.sample(8), Cell::Empty);

    FieldSlice fieldSlice2 = field.slice(Point(1, 0), Direction(0, 1));
    EXPECT_EQ(fieldSlice2.sampleSize, 8);
    for (size_t i = 0; i < 8; i++) {
        EXPECT_EQ(fieldSlice2.sample(i), (i % 2 == 0) ? Cell::White : Cell::Black);
    }
    EXPECT_EQ(fieldSlice2.sample(8), Cell::Empty);

    FieldSlice fieldSlice3 = field.slice(Point(0, 0), Direction(1, 1));
    EXPECT_EQ(fieldSlice3.sampleSize, 8);
    for (size_t i = 0; i < 8; i++) {
        EXPECT_EQ(fieldSlice3.sample(i), Cell::Black);
    }
    EXPECT_EQ(fieldSlice3.sample(8), Cell::Empty);

    FieldSlice fieldSlice4 = field.slice(Point(1, 0), Direction(1, 1));
    EXPECT_EQ(fieldSlice4.sampleSize, 7);
    for (size_t i = 0; i < 7; i++) {
        EXPECT_EQ(fieldSlice4.sample(i), Cell::White);
    }
    EXPECT_EQ(fieldSlice4.sample(7), Cell::Empty);
}
