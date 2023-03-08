//
// フィールド上の値にアクセス
//

#include "field.hpp"

unsigned char* getDataAt(Field* f, Point p) {
    // 範囲外ならNULLを返す
    if (p.x >= f->width || p.y >= f->height) {
        return NULL;
    }

    return &(f->field[p.y * f->width + p.x]);
}

void setDataAt(Field* f, Point p, unsigned char value) {
    // 範囲外なら戻る
    if (p.x >= f->width || p.y >= f->height) {
        return;
    }

    // 位置を特定して値を更新
    f->field[p.y * f->width + p.x] = value;
}
