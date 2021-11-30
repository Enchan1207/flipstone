//
// フィールド
//

#include "Field.h"

void initField(Field* f, unsigned char width, unsigned char height) {
    f->width = width;
    f->height = height;
    f->size = width * height;

    unsigned char* field;
    field = (unsigned char*)calloc(sizeof(unsigned char), f->size);
    if (field == NULL) {
        perror("memory allocation failed\n");
        return;
    }
    f->field = field;
}

void deinitField(Field* f) {
    free(f->field);
}

unsigned char* getDataAt(Field* f, unsigned char x, unsigned char y) {
    // 範囲外ならNULLを返す
    if (x >= f->width || y >= f->height) {
        return NULL;
    }

    return &(f->field[y * f->width + x]);
}
