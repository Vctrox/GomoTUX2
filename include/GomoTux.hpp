#ifndef GOMOTUX_H
#define GOMOTUX_H

#include <cstring>
#include "globals.hpp"

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

    public:
        GomoTux();
        int evaluation(const char *board, char player);
        int evaluationMove(const char* board, int r, int c, char player);
};

#endif