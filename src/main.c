//
// 二次元配列を直線探索したい
//
#include <liburandom.h>
#include <stdio.h>
#include <stdlib.h>

#include "Field.h"
#include "Point.h"

void dumpField(Field *f, unsigned char targetStone);

int main(int argc, char const *argv[]) {
    // フィールド初期化
    Field field, *F;
    F = &field;
    initField(F);

    dumpField(F, REVERSI_WHITE);

    Point p;
    p.x = 3;
    p.y = 2;
    putStoneAt(F, p, REVERSI_WHITE);
    dumpField(F, REVERSI_BLACK);

    p.x = 2;
    p.y = 2;
    putStoneAt(F, p, REVERSI_BLACK);
    dumpField(F, REVERSI_WHITE);

    p.x = 3;
    p.y = 1;
    putStoneAt(F, p, REVERSI_WHITE);
    dumpField(F, REVERSI_BLACK);

    deinitField(F);
    return 0;
}

void dumpField(Field *f, unsigned char targetStone) {
    // 表示
    printf("-------- Field --------\n");
    for (int y = -1; y < f->height + 1; y++) {
        for (int x = -1; x < f->width + 1; x++) {
            Point point;
            point.x = x;
            point.y = y;
            unsigned char *cell = getDataAt(f, point);
            if (cell == NULL) {
                printf(".");
                continue;
            }

            if (*cell == REVERSI_BLACK) {
                printf("○");
            } else if (*cell == REVERSI_WHITE) {
                printf("●");
            } else {
                int togglableCount = getTogglableCount(f, point, targetStone);
                if (togglableCount > 0) {
                    printf("\033[41m%d\033[0m", togglableCount);
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("-----------------------\n");
}
