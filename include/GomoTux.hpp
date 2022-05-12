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

        pattern *patterns;
        int *scores;

    public:
        GomoTux();
        ~GomoTux();
        int evaluation(const char *board);
};

#endif