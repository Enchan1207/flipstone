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
