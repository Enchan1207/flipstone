//
// リバーシのメインロジック
//

#include "Field.h"

int getTogglableCount(Field* f, Point p, unsigned char value) {
    unsigned char* cell = getDataAt(f, p);

    // 範囲外,値が不正ならスキップ
    if (cell == NULL) {
        return REVERSI_UNPLACABLE;
    }
    if (value != REVERSI_BLACK && value != REVERSI_WHITE) {
        return REVERSI_UNPLACABLE;
    }

    // 既に置かれている場合はスキップ
    if (*cell != REVERSI_NONE) {
        return REVERSI_UNPLACABLE;
    }

    // 全方向について
    unsigned int allTogglableCount = 0;
    for (int vy = -1; vy <= 1; vy++) {
        for (int vx = -1; vx <= 1; vx++) {
            if (vx == 0 && vy == 0) {
                continue;
            }

            // 探索し、
            unsigned char cellbuf[8] = {0};
            unsigned char searchLength = search(f, p, vx, vy, cellbuf);

            // 端っこにぶち当たったら次へ
            if (searchLength < 2) {
                continue;
            }

            // 探索結果について、
            unsigned char inversedValue = value == REVERSI_BLACK ? REVERSI_WHITE : REVERSI_BLACK;  // 置かない方の石
            unsigned char hasSameStone = 0;                                                        // 置こうとしている石と同じものが見つかったか?
            unsigned char togglableCount = 0;                                                      // ひっくり返せる石の数
            for (int i = 1; i < searchLength; i++) {
                // 空白が見つかったら中止
                if (cellbuf[i] == REVERSI_NONE) {
                    break;
                }

                // 置こうとしている石と同じものが見つかったらフラグを立ててループを抜ける
                if (cellbuf[i] == value) {
                    hasSameStone = 1;
                    break;
                }

                // 置こうとしている石と違うものが見つかったら **仮に** togglableCountを足す
                if (cellbuf[i] == inversedValue) {
                    togglableCount++;
                }
            }

            // 石を置ける場合はtogglableCount総計に加算
            if (hasSameStone && togglableCount > 0) {
                allTogglableCount += togglableCount;
            }
        }
    }

    return allTogglableCount > 0 ? allTogglableCount : REVERSI_UNPLACABLE;
}

int putStoneAt(Field* f, Point p, unsigned char value) {
    int togglableCount = getTogglableCount(f, p, value);

    // 置けなければ失敗する
    if (togglableCount == REVERSI_UNPLACABLE) {
        return REVERSI_UNPLACABLE;
    }

    // 石を置いて
    setDataAt(f, p, value);

    // ひっくり返してゆく
    for (int vy = -1; vy <= 1; vy++) {
        for (int vx = -1; vx <= 1; vx++) {
            if (vx == 0 && vy == 0) {
                continue;
            }

            // 探索し、
            unsigned char cellbuf[8] = {0};
            unsigned char searchLength = search(f, p, vx, vy, cellbuf);

            // 端っこにぶち当たったら次へ
            if (searchLength < 2) {
                continue;
            }

            // 探索結果について、
            unsigned char inversedValue = value == REVERSI_BLACK ? REVERSI_WHITE : REVERSI_BLACK;  // 置かない方の石
            for (int i = 1; i < searchLength; i++) {
                // 空白か自分と同じ色の石が来たらループを抜ける
                if (cellbuf[i] != inversedValue) {
                    break;
                }

                // 対象の位置を特定して、石を置き換える
                Point target;
                target.x = p.x + vx * i;
                target.y = p.y + vy * i;
                setDataAt(f, target, value);
            }
        }
    }

    return togglableCount;
}
