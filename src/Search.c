//
// 探索
//

#include "Field.h"

// 指定位置の値を取得
unsigned char* getDataAt(Field* f, Point p) {
    // 範囲外ならNULLを返す
    if (p.x >= f->width || p.y >= f->height) {
        return NULL;
    }

    return &(f->field[p.y * f->width + p.x]);
}

// 位置と方向を指定して探索
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

        // バッファに積んでカーソルを進める
        *ptr = *cell;
        ptr++;

        current.x += vx;
        current.y += vy;
    }

    return ptr - buf;
}
