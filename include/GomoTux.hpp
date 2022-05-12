#ifndef GOMOTUX_H
#define GOMOTUX_H

#include "patterns.hpp"

class GomoTux {
    private:
        char **patterns;
        int *scores;

    public:
        GomoTux();
        int evaluate(const char *board);
};

#endif