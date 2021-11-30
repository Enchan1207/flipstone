//
// フィールド
//

#ifndef _FIELD_H_
#define _FIELD_H_

#include <stdio.h>
#include <stdlib.h>

#include "Point.h"

#define REVERSI_NONE 0x00
#define REVERSI_BLACK 0x01
#define REVERSI_WHITE 0x02

/**
 * @brief フィールド
 */
typedef struct {
    unsigned char width;
    unsigned char height;
    unsigned char size;

    unsigned char *field;
} Field;

/**
 * @brief フィールド初期化
 * 
 * @param f 初期化対象のフィールド
 * @param width フィールドの幅
 * @param height フィールドの高さ
 */
void initField(Field *f, unsigned char width, unsigned char height);

/**
 * @brief フィールドメモリの開放
 * 
 * @param f 開放対象のフィールド
 */
void deinitField(Field *);

/**
 * @brief 指定位置の値を取得
 * 
 * @param f 探索対象のフィールド
 * @param p 探索対象の点
 * @return unsigned char* フィールド上の探索位置にあたるポインタ 範囲外ならNULL
 */
unsigned char *getDataAt(Field *, Point p);

/**
 * @brief 指定位置の値を設定
 * 
 * @param f 探索対象のフィールド
 * @param p 探索対象の点
 * @param value 設定したい値
 */
void setDataAt(Field *f, Point p, unsigned char value);

/**
 * @brief 位置と方向を指定してフィールド内を探索
 * 
 * @param f 探索対象のフィールド
 * @param p 探索開始点
 * @param vx 探索方向x
 * @param vy 探索方向y
 * @param buf 結果格納バッファ
 * @return int 探索できた長さ
 */
int search(Field *f, Point p, char vx, char vy, unsigned char *buf);

#endif
