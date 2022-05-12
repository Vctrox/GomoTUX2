#ifndef GOMOTUX_H
#define GOMOTUX_H

#include <cstring>
#include "globals.hpp"

const int pattern_size = 11;

class GomoTux {
    private:
        struct pattern {
            char min_occur;
            char length;
            char blocks;
            char spaces;
        };
        struct Deplacement{
            char length;
            char blocks;
            char spaces;
        };
        pattern *patterns;
        int *scores;
        int pattern_skip[];

    public:
        GomoTux();
        int evaluation(const char *board, char player);
        int evaluationMove(const char* board, int r, int c, char player);
        ~GomoTux();
        int winner(const char *gs);
        void measureDeplacement(const char *gs,
                                   int r, int c,
                                   int dr, int dc,
                                   int player,
                                   bool consecutive,
                                   Deplacement *result);
};

#endif