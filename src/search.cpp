//
// フィールドを探索
//

#include "field.hpp"

int search(Field* f, Point p, char vx, char vy, unsigned char* buf) {
    Point current = p;  // 現在読んでいる場所

    unsigned char* ptr = buf;  // バッファカーソル

    unsigned char* cell = NULL;
    while (1) {
        // 指定位置のデータを取得
        cell = getDataAt(f, current);
        if (cell == NULL) {
            break;
        }

        // 開始点以外が空白でなければ
        if (((ptr - buf) > 0) && *cell == REVERSI_NONE) {
            break;
        }

        // バッファに積んでカーソルを進める
        *ptr = *cell;
        ptr++;

        // 探索位置を進める
        current.x += vx;
        current.y += vy;
    }

    return ptr - buf;
}
