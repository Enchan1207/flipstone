//
// 石の数を数える
//

#include "Field.h"

unsigned int getStoneCount(Field* f, unsigned char value) {
    unsigned int summary = 0;

    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            Point p;
            p.x = x;
            p.y = y;

            if (*getDataAt(f, p) == value) {
                summary++;
            }
        }
    }

    return summary;
}
