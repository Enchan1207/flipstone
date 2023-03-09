/// @file
/// @brief 盤面状態のダンプと入出力
///

#include "interface.hpp"

void dumpField(Field *f, unsigned char targetStone) {
    // 表示
    printf("-------- Field --------\n");
    for (int8_t y = -1; y < f->height + 1; y++) {
        for (int8_t x = -1; x < f->width + 1; x++) {
            Point point(x, y);
            unsigned char *cell = getDataAt(f, point);
            if (cell == NULL) {
                printf(".");
                continue;
            }

            if (*cell != REVERSI_NONE) {
                const char *black_stone = "○";
                const char *white_stone = "●";
                const char *cellStrRepr = *cell == REVERSI_BLACK ? black_stone : white_stone;
                printf("%s", cellStrRepr);
            } else {
                // 指示があれば置ける石の数を表示
                if (targetStone != REVERSI_NONE) {
                    int togglableCount = getTogglableCount(f, point, targetStone);
                    if (togglableCount > 0) {
                        printf("\033[41m%d\033[0m", togglableCount);
                    } else {
                        printf(" ");
                    }
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("-----------------------\n");
}

void inputPointToPlace(Field *f, Point *p, unsigned char targetStone) {
    int isPlacable = REVERSI_UNPLACABLE;
    while (isPlacable == REVERSI_UNPLACABLE) {
        // コンソールから入力
        printf("Type place to put stone (format: \\d,\\d) >");
        fflush(stdout);
        char placebuffer[5] = {0};  // x,y\n\0 で入力される想定
        fgets(placebuffer, 5, stdin);

        // ガバガバリデーション
        if (placebuffer[1] != ',') {
            continue;
        }

        // 各桁を取り出して数値に変換 クソ実装すぎる
        char *invalidStrBuffer = NULL;
        unsigned char x = (unsigned char)strtol(placebuffer, &invalidStrBuffer, 10);
        if (invalidStrBuffer[0] != ',') {
            continue;
        }
        unsigned char y = (unsigned char)strtol(placebuffer + 2, &invalidStrBuffer, 10);
        if (invalidStrBuffer[0] != '\n') {
            continue;
        }

        p->x = x;
        p->y = y;

        fflush(stdin);  // クソ実装(fflush(stdin)は未定義)

        isPlacable = getTogglableCount(f, *p, targetStone);
        if (isPlacable == REVERSI_UNPLACABLE) {
            printf("Invalid place!\n");
        }
    }
}
