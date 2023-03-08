//
// simple_reversi
//
#include <stdio.h>
#include <stdlib.h>

#include "field.h"
#include "point.h"

void dumpField(Field *f, unsigned char targetStone);
void inputPointToPlace(Field *f, Point *p, unsigned char targetStone);

int main(int argc, char const *argv[]) {
    // フィールド初期化
    Field field, *F;
    F = &field;
    initField(F);

    // それぞれのプレイヤーが置く石を決める
    const unsigned char playerStone = REVERSI_BLACK;
    const unsigned char cpuStone = REVERSI_WHITE;

    // 今どっちが置いているか
    unsigned char isPlayerTurn = 1;

    // ゲームループ
    int isSkippedAtPreviousTurn = 0;  // ひとつ前のループでターンスキップしたか
    while (1) {
        unsigned char currentStone = isPlayerTurn ? playerStone : cpuStone;
        char *currentPlayerStrRepr = isPlayerTurn ? "Player" : "CPU";

        // フィールドをダンプ
        printf("%s turn!\n", currentPlayerStrRepr);
        dumpField(F, currentStone);

        // 置けるところがひとつもなければターンスキップ
        if (hasPlacablePoint(F, currentStone) == REVERSI_UNPLACABLE) {
            // 以前スキップしていた(互いに置けるところがない)ならゲーム終了
            if (isSkippedAtPreviousTurn) {
                break;
            }

            printf("No place to put stone! turn switching...\n");
            isSkippedAtPreviousTurn = 1;

            // ここにもターンスイッチ書くの腹立つな
            isPlayerTurn = isPlayerTurn ? 0 : 1;

            continue;
        } else {
            isSkippedAtPreviousTurn = 0;
        }

        // どこに置くか?
        Point p;
        if (isPlayerTurn) {
            inputPointToPlace(F, &p, currentStone);
        } else {
            decideStonePosition(F, &p, currentStone);
        }

        // 石を置く
        printf("%s Placed Stone at (%d, %d).\n", currentPlayerStrRepr, p.x, p.y);
        putStoneAt(F, p, currentStone);

        // ターンをスイッチ
        isPlayerTurn = isPlayerTurn ? 0 : 1;
    }

    // 試合終了!
    printf("FINISHED!\n");

    unsigned int playerCount = getStoneCount(F, playerStone);
    unsigned int cpuCount = getStoneCount(F, cpuStone);
    printf("Player: %d CPU: %d\n", playerCount, cpuCount);

    char *winner = playerCount > cpuCount ? "Player" : "CPU";
    printf("%s win!\n", winner);

    deinitField(F);
    return 0;
}

/**
 * @brief フィールドの状態をコンソールにダンプする
 *
 * @param f ダンプ対象のフィールド
 * @param targetStone この引数に指定した石を置ける場所をハイライトする REVERSI_NONE を渡すとハイライトしない
 */
void dumpField(Field *f, unsigned char targetStone) {
    // 表示
    printf("-------- Field --------\n");
    for (int y = -1; y < f->height + 1; y++) {
        for (int x = -1; x < f->width + 1; x++) {
            Point point;
            point.x = x;
            point.y = y;
            unsigned char *cell = getDataAt(f, point);
            if (cell == NULL) {
                printf(".");
                continue;
            }

            if (*cell != REVERSI_NONE) {
                char *cellStrRepr = *cell == REVERSI_BLACK ? "○" : "●";
                printf("%s", cellStrRepr);
            } else {
                // 指示があれば置ける石の数を表示
                if (targetStone != REVERSI_NONE) {
                    int togglableCount = getTogglableCount(f, point, targetStone);
                    if (togglableCount > 0) {
                        printf("\033[41m%d\033[0m", togglableCount);
                    } else {
                        printf(" ");
                    }
                } else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("-----------------------\n");
}

/**
 * @brief フィールドに石を置く場所をコンソールから入力する
 *
 * @param f 配置対象のフィールド
 * @param p 置く場所
 * @param targetStone 置きたい石
 */
void inputPointToPlace(Field *f, Point *p, unsigned char targetStone) {
    int isPlacable = REVERSI_UNPLACABLE;
    while (isPlacable == REVERSI_UNPLACABLE) {
        // コンソールから入力
        printf("Type place to put stone (format: \\d,\\d) >");
        fflush(stdout);
        char placebuffer[5] = {0};  // x,y\n\0 で入力される想定
        fgets(placebuffer, 5, stdin);

        // ガバガバリデーション
        if (placebuffer[1] != ',') {
            continue;
        }

        // 各桁を取り出して数値に変換 クソ実装すぎる
        char *invalidStrBuffer = NULL;
        unsigned char x = (unsigned char)strtol(placebuffer, &invalidStrBuffer, 10);
        if (invalidStrBuffer[0] != ',') {
            continue;
        }
        unsigned char y = (unsigned char)strtol(placebuffer + 2, &invalidStrBuffer, 10);
        if (invalidStrBuffer[0] != '\n') {
            continue;
        }

        p->x = x;
        p->y = y;

        fflush(stdin);  // クソ実装(fflush(stdin)は未定義)

        isPlacable = getTogglableCount(f, *p, targetStone);
        if (isPlacable == REVERSI_UNPLACABLE) {
            printf("Invalid place!\n");
        }
    }
}
