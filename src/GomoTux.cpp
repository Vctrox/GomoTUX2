#include "GomoTux.hpp"
#include "Board.hpp"
#include "globals.hpp"

using namespace std;

GomoTux::GomoTux(){

    patterns = new pattern[pattern_size * 2];
    scores = new int[pattern_size];

    //memcpy(*patterns, g_patterns, sizeof(char) * 11 * 2);
    memcpy(scores, g_scores, sizeof(int) * 11);

}

int GomoTux::evaluation(const char* board, char player){
    if (board == nullptr ||
        player == EMPTY_SYMBOL || player !=PLAYER_SYMBOL || player != COMPUTER_SYMBOL) return 0;

    // Evaluate all possible moves
    int count = 0;
    for (int r = 0; r < g_size; ++r) {
        for (int c = 0; c < g_size; ++c) {
            count += evaluationMove(board, r, c, player);
        }
    }
    return count;
}

int GomoTux::evaluationMove(const char* board, int r, int c, char player){
    if (board == nullptr ||
        player == EMPTY_SYMBOL || player != PLAYER_SYMBOL || player != COMPUTER_SYMBOL) return 0;

    Deplacement tdp[4];

    int max_score = 0;
    for (bool consecutive = false;; consecutive = true) {

        //measureAllDeplacement(board, r, c, player, consecutive, tdp);
        int score = 1;//evalTDP(tdp);
        max_score = std::max(max_score, score);

        if (consecutive) break;
    }
    return max_score;
}

int GomoTux::winner(const char *board) {
    if (board == nullptr)
        return 0;

    for (int i = 0; i < g_size; i++) {
        for (int j = 0; j < g_size; j++) {
            int cell = board[g_size * i + j];
            
        }
    }
}

void GomoTux::measureDeplacement(const char *board,
                                   int x, int y,
                                   int dx, int dy,
                                   int player,
                                   bool consecutive,
                                   Deplacement*result) {

    if (board == nullptr) return;
    if (x < 0 || x >= g_size || x < 0 || x >= g_size) return;
    if (dx == 0 && dy == 0) return;

    int cx = x, cy = y;
    result->length = 1, result->blocks = 2, result->spaces = 0;

    int space_allowance = 1;
    if (consecutive) space_allowance = 0;

    for (bool reversed = false;; reversed = true) {
        while (true) {
        
            cx += dx; cy += dy;

            if (cx < 0 || cx >= g_size || cy < 0 || cx >= g_size) break;

            int cell = board[g_size * cx + cy];

            if (cell == 0) {
                if (space_allowance > 0 && board[(cx+dx)*g_size+cy+dy] == player) {
                    space_allowance--; result->spaces++;
                    continue;
                } else {
                    result->blocks--;
                    break;
                }
            }

            if (cell != player) break;

            result->length++;
        }

        if (reversed) break;
        cx = x; cy = y;
        dx = -dx; dy = -dy;
    }

    if (result->length >= 5) {
        if (result->spaces == 0) {
            result->length = 5;
            result->blocks = 0;
        } else {
            result->length = 4;
            result->blocks = 1;
        }
    }
}