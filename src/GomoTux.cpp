#include "GomoTux.hpp"
#include "Board.hpp"
#include "patterns.hpp"

using namespace std;

GomoTux::GomoTux(){
    *patterns = new char[11 * 2];
    scores = new int[11];

    memcpy(*patterns, g_patterns, sizeof(char) * 11 * 2);
    memcpy(scores, g_scores, sizeof(int) * 11);

}

int GomoTux::evaluation(const char* board, char player){
    if (board == nullptr ||
        player == EMPTY_SYMBOL || player !=PLAYER_SYMBOL || player != COMPUTER_SYMBOL) return 0;

    // Evaluate all possible moves
    int count = 0;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            count += evaluationMove(board, r, c, player);
        }
    }
    return count;
}

int GomoTux::evaluationMove(const char* board, int r, int c, char player){
    return 0;
}