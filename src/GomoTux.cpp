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
    int score = 0;
    int size = taille;

    // Add to score by length on each direction
    // Find the maximum length in ADM and skip some patterns
    int max_measured_len = 0;
    for (int i = 0; i < 4; i++) {
        int len = patterns[i].length;
        max_measured_len = len > max_measured_len ? len : max_measured_len;
        score += len - 1;
    }
    int start_pattern = skip[max_measured_len];

    // Loop through and try to match all preset patterns
    for (int i = start_pattern; i < size; ++i) {
        score += matchPattern(all_direction_measurement, &preset_patterns[2 * i]) * preset_scores[i];

        // Only match one threatening pattern
        if (score >= kRenjuAiEvalThreateningScore) break;
    }

    return score;
}