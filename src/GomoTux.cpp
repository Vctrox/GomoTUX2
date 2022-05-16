#include "GomoTux.hpp"
#include "Board.hpp"
#include "globals.hpp"


using namespace std;

GomoTux::GomoTux(){
    patterns = new Pattern[pattern_size * 2];
    scores = new int[pattern_size];
    
    int patterns_skip[6] = {11, 11, 10, 7, 1, 0};

    memcpy(patterns, g_patterns, sizeof(Pattern) * 11 * 2);
    memcpy(scores, g_scores, sizeof(int) * 11);
}


void GomoTux::measureInOneDirection(const char *board,
                                   int x, int y,
                                   int dx, int dy,
                                   int player,
                                   bool consecutive,
                                   GomoTux::MeasureMove *result) {
    // Check arguments
    if (board == nullptr) return;
    if (x < 0 || x >= g_size || y < 0 || y >= g_size) return;
    if (dx == 0 && dy == 0) return;

    // Initialization
    int cx = x, cy = y;
    result->length = 1, result->blocks = 2, result->spaces = 0;

    int space_allowance = 1;
    if (consecutive) space_allowance = 0;

    for (bool reversed = false;; reversed = true) {
        while (true) {
            // Move
            cx += dx; cy += dy;

            // Validate position
            if (cx < 0 || cx >= g_size || cy < 0 || cy >= g_size) break;

            // Get cell value
            int cell = board[g_size * cx + cy];

            // Empty cells
            if (cell == 0) {
                if (space_allowance > 0 && board[cx + dx, cy + dy] == player) {
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
        cx = x; cy = y;
        dx = -dx; dy = -dy;
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

void GomoTux::measureInAllDirections(const char *board,
                                       int x,
                                       int y,
                                       int player,
                                       bool consecutive,
                                       GomoTux::MeasureMove *adm) {
    // Check arguments
    if (board == nullptr) return;
    if (x < 0 || x >= g_size || y < 0 || y >= g_size) return;

    // Measure 4 directions
    measureInOneDirection(board, x, y, 0,  1, player, consecutive, &adm[0]);
    measureInOneDirection(board, x, y, 1,  1, player, consecutive, &adm[1]);
    measureInOneDirection(board, x, y, 1,  0, player, consecutive, &adm[2]);
    measureInOneDirection(board, x, y, 1, -1, player, consecutive, &adm[3]);
}
    
int GomoTux::matchPattern(MeasureMove *all_direction_measurement,
                              Pattern *patterns) {
    // Check arguments
    if (all_direction_measurement == nullptr) return -1;
    if (patterns == nullptr) return -1;

    // Increment PM count
    //g_pm_count++;

    // Initialize match_count to INT_MAX since minimum value will be output
    int match_count = numeric_limits<int>::max(), single_pattern_match = 0;

    // Currently allows maximum 2 patterns
    for (int i = 0; i < 2; ++i) {
        auto p = patterns[i];
        if (p.length == 0) break;

        // Initialize counter
        single_pattern_match = 0;

        // Loop through 4 directions
        for (int j = 0; j < 4; ++j) {
            auto dm = all_direction_measurement[j];

            // Requires exact match
            if (dm.length == p.length &&
                (p.blocks == -1 || dm.blocks == p.blocks) &&
                (p.spaces == -1 || dm.spaces == p.spaces)) {
                single_pattern_match++;
            }
        }

        // Consider minimum number of occurrences
        single_pattern_match /= p.min_occur;

        // Take smaller value
        match_count = match_count >= single_pattern_match ? single_pattern_match : match_count;
    }
    return match_count;
}

int GomoTux::evalMove(const char *board, int x, int y, int player) {
    // Check parameters
    if (board == nullptr ||
        player < 1 || player > 2) return 0;

    // Count evaluations
    //++g_eval_count;

    // Allocate 4 direction measurements
    MeasureMove allDirections[4];

    // Measure in consecutive and non-consecutive conditions
    int max_score = 0;
    for (bool consecutive = false;; consecutive = true) {
        // Execute measurement
        measureInAllDirections(board, x, y, player, consecutive, allDirections);

        int score = evalInAllDirections(allDirections);

        // Prefer consecutive
        // if (!consecutive) score *= 0.9;

        // Choose the better between consecutive and non-consecutive
        max_score = std::max(max_score, score);

        if (consecutive) break;

        
    }

    return max_score;
}

    
int GomoTux::evalInAllDirections(GomoTux::MeasureMove *all_direction_measurement) {
    int score = 0;
    int size = g_pattern_size;

    // Add to score by length on each direction
    // Find the maximum length in ADM and skip some patterns
    int max_measured_len = 0;
    for (int i = 0; i < 4; i++) {
        int len = all_direction_measurement[i].length;
        max_measured_len = len > max_measured_len ? len : max_measured_len;
        score += len - 1;
    }
    int start_pattern = pattern_skip[max_measured_len];

    // Loop through and try to match all preset patterns
    for (int i = start_pattern; i < size; ++i) {
        score += matchPattern(all_direction_measurement, &patterns[2 * i]) * g_scores[i];

        // Only match one threatening pattern
        if (score >= 300) break;
    }

    return score;
}


int GomoTux::evalBoard(const char *board, int player) {
    // Check parameters
    if (board == nullptr ||
        player < 1 || player > 2) return 0;

    // Evaluate all possible moves
    int score = 0;
    for (int i = 0; i < g_size; ++i) {
        for (int j = 0; j < g_size; ++j) {
            score += evalMove(board, i, j, player);
        }
    }
    return score;
}