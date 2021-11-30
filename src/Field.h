//
// フィールド
//

#ifndef _FIELD_H_
#define _FIELD_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char width;
    unsigned char height;
    unsigned char size;

    unsigned char *field;
} Field;

void initField(Field *, unsigned char, unsigned char);
void deinitField(Field *);

unsigned char *getDataAt(Field *, unsigned char, unsigned char);

#endif
