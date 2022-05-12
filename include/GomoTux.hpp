#ifndef GOMOTUX_H
#define GOMOTUX_H

#include <cstring>
#include "patterns.hpp"

class GomoTux {
    private:
        struct pattern {
            char min_occur;
            char length;
            char blocks;
            char spaces;
        };

        pattern *patterns;
        int *scores;

    public:
        GomoTux();
        int evaluation(const char *board);
};

#endif