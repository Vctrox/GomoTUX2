#include "GomoTux.hpp"

using namespace std;

GomoTux::GomoTux(){
    patterns = new pattern[11 * 2];
    scores = new int[11];

    memcpy(patterns, g_patterns, sizeof(char) * 11 * 2);
    memcpy(scores, g_scores, sizeof(int) * 11);
}

int GomoTux::evaluate(const char* board){
    int count = 0;
    return count;
}