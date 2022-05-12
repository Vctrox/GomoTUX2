#include "GomoTux.hpp"
#include "Board.hpp"
#include "globals.hpp"


using namespace std;

GomoTux::GomoTux(){
    patterns = new Pattern[pattern_size * 2];
    scores = new int[pattern_size];
    memcpy(patterns, g_patterns, sizeof(char) * 11 * 2);
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