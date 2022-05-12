#include "GomoTux.hpp"

using namespace std;

GomoTux::GomoTux(){

    patterns = new pattern[size * 2];
    scores = new int[size];

    memcpy(patterns, g_patterns, sizeof(char) * 11 * 2);
    memcpy(scores, g_scores, sizeof(int) * 11);
}

int GomoTux::evaluation(const char* board){
    int count = 0;
    return count;
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

GomoTux::~GomoTux(){}