//
// simple_reversi
//
#include <stdio.h>

#include "interface.hpp"
#include "reversi.hpp"
#include "reversi_ai.hpp"

int main(int argc, char const *argv[]) {
    // フィールド初期化
    Field field, *F;
    F = &field;
    initField(F);

    // 各プレイヤーを定義
    const char *playerName = "Player";
    const unsigned char playerStone = REVERSI_BLACK;

    const char *cpuName = "Computer";
    const unsigned char cpuStone = REVERSI_WHITE;

    // 今どっちが置いているか
    unsigned char isPlayerTurn = 1;

    // ゲームループ
    int isSkippedAtPreviousTurn = 0;  // ひとつ前のループでターンスキップしたか
    while (1) {
        unsigned char currentStone = isPlayerTurn ? playerStone : cpuStone;
        const char *currentPlayerStrRepr = isPlayerTurn ? playerName : cpuName;

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

    const char *winner = playerCount > cpuCount ? playerName : cpuName;
    printf("%s win!\n", winner);

    deinitField(F);
    return 0;
}
