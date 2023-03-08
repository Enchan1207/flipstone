//
// リバーシAI
//

#include "field.hpp"

unsigned int searchPlacablePosition(Field* f, unsigned char value, Point* buf, unsigned int bufferLength);

void decideStonePosition(Field* f, Point* p, unsigned char value) {
    // 現在置けるすべての場所をサーチ
    unsigned int searchLength = f->width * f->height;  // 置ける場所の数が幅*高さ以上になることはありえない
    Point* placablePoints;
    placablePoints = (Point*)calloc(sizeof(Point), searchLength);
    if (placablePoints == NULL) {
        perror("FATAL: memory allocation failed!!\n");
        exit(1);
        return;
    }
    unsigned int positionCount = searchPlacablePosition(f, value, placablePoints, searchLength);

    // どこに設けなければ降参(お守りみたいなもの、実際はこの処理に入ることはない)
    if (positionCount == 0) {
        p->x = 0;
        p->y = 0;
        return;
    }

    // それぞれの場所について、そこに置くことでひっくり返せる石の数を調べる
    unsigned char* togglableCounts;
    togglableCounts = (unsigned char*)calloc(sizeof(unsigned char), positionCount);
    if (togglableCounts == NULL) {
        perror("FATAL: memory allocation failed!!\n");
        exit(1);
        return;
    }

    unsigned char* cursor = togglableCounts;
    for (int i = 0; i < positionCount; i++) {
        unsigned char togglableCount = (unsigned char)getTogglableCount(f, placablePoints[i], value);
        *cursor = togglableCount;
        cursor++;
    }

    // 最大値のインデックスを取得し
    unsigned char index = 0, current = togglableCounts[index];
    for (int i = 0; i < positionCount; i++) {
        if (togglableCounts[i] > current) {
            current = togglableCounts[i];
            index = i;
        }
    }

    // インデックスにあたる位置の値に書き換える
    p->x = placablePoints[index].x;
    p->y = placablePoints[index].y;

    free(togglableCounts);
    free(placablePoints);
}

/**
 * @brief 現時点で石を置けるすべての場所をサーチ
 *
 * @param f 対象のフィールド
 * @param value 置きたい石
 * @param buf 座標バッファ
 * @param bufferLength 座標バッファ長さ
 * @return 置ける場所の数
 */
unsigned int searchPlacablePosition(Field* f, unsigned char value, Point* buf, unsigned int bufferLength) {
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
