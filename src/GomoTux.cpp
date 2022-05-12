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