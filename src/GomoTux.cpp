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
