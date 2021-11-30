//
// 二次元配列を直線探索したい
//
#include <liburandom.h>
#include <stdio.h>
#include <stdlib.h>

#include "Field.h"
#include "Point.h"

int main(int argc, char const *argv[]) {
    // フィールド初期化
    const unsigned char width = 8, height = 8;
    Field field, *F;
    F = &field;
    initField(F, width, height);

    // 適当な乱数を生成してフィールドを汚しておく
    unsigned char *randomArray = (unsigned char *)calloc(sizeof(char), F->size);
    if (randomArray == NULL) {
        perror("memory allocation failed");
        return 1;
    }
    if (urandom(randomArray, F->size) != URANDOM_OK) {
        return 1;
    }
    F->field = randomArray;

    // 表示
    printf("-------- Field --------\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Point point;
            point.x = x;
            point.y = y;
            unsigned char *cell = getDataAt(F, point);
            if (cell != NULL) {
                printf("%02X ", *cell);
            } else {
                printf(".. ");
            }
        }
        printf("\n");
    }
    printf("-----------------------\n");

    // 位置と方向を指定して探索
    const unsigned char sx = 3, sy = 5;  // 探索開始点xy
    const char vx = 1, vy = -1;          // 探索方向xy (-1~1)
    Point start;                         // 現在読んでいる場所
    start.x = sx;
    start.y = sy;

    unsigned char searchResult[8] = {0};
    int readBytes = search(F, start, vx, vy, searchResult);

    for (int i = 0; i < readBytes; i++) {
        printf("%02X ", searchResult[i]);
    }
    printf("\n");

    deinitField(F);
    return 0;
}