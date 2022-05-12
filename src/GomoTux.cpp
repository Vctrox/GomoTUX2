#include "GomoTux.hpp"
#include "Board.hpp"
#include "globals.hpp"
#include "patterns.hpp"

using namespace std;

GomoTux::GomoTux(){

    patterns = new pattern[size * 2];
    scores = new int[size];

    memcpy(*patterns, g_patterns, sizeof(char) * 11 * 2);
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

        measureAllDirections(board, r, c, player, consecutive, tdp);
        int score = evalADM(adm);
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

void GomoTux::measureDeplacement(const char *gs,
                                   int r, int c,
                                   int dr, int dc,
                                   int player,
                                   bool consecutive,
                                   Deplacement*result) {
    // Check arguments
    if (gs == nullptr) return;
    if (r < 0 || r >= g_size || c < 0 || c >= g_size) return;
    if (dr == 0 && dc == 0) return;

    // Initialization
    int cr = r, cc = c;
    result->length = 1, result->blocks = 2, result->spaces = 0;

    int space_allowance = 1;
    if (consecutive) space_allowance = 0;

    for (bool reversed = false;; reversed = true) {
        while (true) {
            // Move
            cr += dr; cc += dc;

            // Validate position
            if (cr < 0 || cr >= g_size || cc < 0 || cc >= g_size) break;

            // Get cell value
            int cell = gs[g_size * cr + cc];

            // Empty cells
            if (cell == 0) {
                if (space_allowance > 0 && Board[(cr+dr)*g_size+cc+dc] == player) {
                    space_allowance--; result->spaces++;
                    continue;
                } else {
                    result->blocks--;
                    break;
                }
            }

            // Another player
            if (cell != player) break;

            // Current player
            result->length++;
        }

        // Reverse direction and continue (just once)
        if (reversed) break;
        cr = r; cc = c;
        dr = -dr; dc = -dc;
    }

    // More than 5 pieces in a row is equivalent to 5 pieces
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