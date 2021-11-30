//
// 二次元配列を直線探索したい
//
#include <liburandom.h>
#include <stdio.h>
#include <stdlib.h>

#include "Field.h"
#include "Point.h"

void dumpField(Field *f);

int main(int argc, char const *argv[]) {
    // フィールド初期化
    Field field, *F;
    F = &field;
    initField(F, 8, 8);

    dumpField(F);

    deinitField(F);
    return 0;
}

void dumpField(Field *f) {
    // 表示
    printf("-------- Field --------\n");
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            Point point;
            point.x = x;
            point.y = y;
            unsigned char *cell = getDataAt(f, point);
            if (cell != NULL) {
                printf("%02X ", *cell);
            } else {
                printf(".. ");
            }
        }
        printf("\n");
    }
    printf("-----------------------\n");
}
