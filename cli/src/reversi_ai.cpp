/// @file
/// @brief リバーシAI
//

#include "reversi_ai.hpp"

void decideStonePosition(Field* f, Point* p, uint8_t value) {
    // 現在置けるすべての場所をサーチ
    const unsigned int searchLength = f->width * f->height;
    Point placablePoints[searchLength];
    unsigned int positionCount = searchPlacablePosition(f, value, placablePoints, searchLength);

    // どこに設けなければ降参(お守りみたいなもの、実際はこの処理に入ることはない)
    if (positionCount == 0) {
        p->x = 0;
        p->y = 0;
        return;
    }

    // それぞれの場所について、そこに置くことでひっくり返せる石の数を調べる
    uint8_t togglableCounts[positionCount];

    uint8_t* cursor = togglableCounts;
    for (int i = 0; i < positionCount; i++) {
        uint8_t togglableCount = (uint8_t)getTogglableCount(f, placablePoints[i], value);
        *cursor = togglableCount;
        cursor++;
    }

    // 最大値のインデックスを取得し
    uint8_t index = 0, current = togglableCounts[index];
    for (int i = 0; i < positionCount; i++) {
        if (togglableCounts[i] > current) {
            current = togglableCounts[i];
            index = i;
        }
    }

    // インデックスにあたる位置の値に書き換える
    p->x = placablePoints[index].x;
    p->y = placablePoints[index].y;
}

unsigned int searchPlacablePosition(Field* f, uint8_t value, Point* buf, unsigned int bufferLength) {
    Point* cursor = buf;
    for (int y = 0; y < f->height; y++) {
        for (int x = 0; x < f->width; x++) {
            Point p;
            p.x = x;
            p.y = y;

            int togglableCount = getTogglableCount(f, p, value);
            if (togglableCount != REVERSI_UNPLACABLE && (cursor - buf) < bufferLength) {
                cursor->x = p.x;
                cursor->y = p.y;
                cursor++;
            }
        }
    }

    return cursor - buf;
}
