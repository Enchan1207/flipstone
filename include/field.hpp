//
// フィールド
//

#ifndef SIMPLE_REVERSI_FIELD_H
#define SIMPLE_REVERSI_FIELD_H

#include <stdio.h>
#include <stdlib.h>

#include "direction.hpp"
#include "point.hpp"

#define REVERSI_NONE 0x00
#define REVERSI_BLACK 0x01
#define REVERSI_WHITE 0x02

#define REVERSI_OK 0x00
#define REVERSI_UNPLACABLE -1

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
 */
void initField(Field *f);

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
 * @brief 位置と方向を指定して、REVERSI_NONEか端に当たるまでフィールド内を探索
 *
 * @param f 探索対象のフィールド
 * @param p 探索開始点
 * @param vx 探索方向x
 * @param vy 探索方向y
 * @param buf 結果格納バッファ
 * @return int 探索できた長さ
 */
int search(Field *f, Point p, char vx, char vy, unsigned char *buf);

/**
 * @brief 指定位置に指定種別の石を置いた時にひっくり返せる石の合計数を返す
 *
 * @param f 探索対象のフィールド
 * @param p 石を置く場所
 * @param value 置きたい石の種類(REVERSI_*)
 * @return int ひっくり返せる石の数 / REVERSI_UNPLACABLE
 */
int getTogglableCount(Field *f, Point p, unsigned char value);

/**
 * @brief 指定位置に石を置く
 *
 * @param f 対象のフィールド
 * @param p 石を置く場所
 * @param value 置きたい石の種類
 * @return int ひっくり返した石の数 / REVERSI_UNPLACABLE
 */
int putStoneAt(Field *f, Point p, unsigned char value);

/**
 * @brief 石を置ける場所があるか
 *
 * @param f 対象のフィールド
 * @param value 置きたい石
 * @return int 置ける石の数 / REVERSI_UNPLACABLE
 */
int hasPlacablePoint(Field *f, unsigned char value);

/**
 * @brief 石の数を数える
 *
 * @param f 対象のフィールド
 * @param value 数えたい石
 * @return unsigned int フィールド上にある石の数
 */
unsigned int getStoneCount(Field *f, unsigned char value);

#endif
