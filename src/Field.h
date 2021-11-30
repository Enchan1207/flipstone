//
// フィールド
//

#ifndef _FIELD_H_
#define _FIELD_H_

#include <stdio.h>
#include <stdlib.h>

#include "Point.h"

typedef struct {
    unsigned char width;
    unsigned char height;
    unsigned char size;

    unsigned char *field;
} Field;

// フィールド初期化
void initField(Field *f, unsigned char width, unsigned char height);
void deinitField(Field *);

// 探索
unsigned char *getDataAt(Field *, Point p);
int search(Field *f, Point p, char vx, char vy, unsigned char *buf);

#endif
