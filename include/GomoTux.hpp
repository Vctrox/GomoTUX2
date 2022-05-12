#ifndef GOMOTUX_H
#define GOMOTUX_H

#include <cstring>
#include "patterns.hpp"

class GomoTux {
    private:
        char **patterns;
        int *scores;

    public:
        GomoTux();
        int evaluation(const char *board, char player);
        int evaluationMove(const char* board, int r, int c, char player);
};

#endif