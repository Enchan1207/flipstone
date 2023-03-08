//
// フィールド
//

#include "field.h"

void initField(Field* f) {
    f->width = 8;
    f->height = 8;
    f->size = 64;

    unsigned char* field;
    field = (unsigned char*)calloc(sizeof(unsigned char), f->size);
    if (field == NULL) {
        perror("memory allocation failed\n");
        return;
    }
    f->field = field;

    // フィールドを「何も置かれていない」状態にする
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            Point p;
            p.x = x;
            p.y = y;
            setDataAt(f, p, REVERSI_NONE);
        }
    }

    // リバーシの初期(真ん中に交互に石が置かれている)状態を設定 ここクソ実装
    unsigned char initial_points[12] = {
        3,
        3,
        REVERSI_BLACK,
        3,
        4,
        REVERSI_WHITE,
        4,
        3,
        REVERSI_WHITE,
        4,
        4,
        REVERSI_BLACK,
    };
    for (int i = 0; i < 4; i++) {
        Point p;
        p.x = initial_points[i * 3 + 0];
        p.y = initial_points[i * 3 + 1];
        setDataAt(f, p, initial_points[i * 3 + 2]);
    }
}

void deinitField(Field* f) {
    free(f->field);
}
