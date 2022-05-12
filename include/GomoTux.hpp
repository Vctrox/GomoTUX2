#ifndef GOMOTUX_H
#define GOMOTUX_H

#include <cstring>
#include "globals.hpp"
<<<<<<< HEAD

const int size = 11;
=======
>>>>>>> 9809c5c74fb7a51444c87746e89e7c6278858e06

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
        int pattern_skip[];

    public:
        GomoTux();
        ~GomoTux();
        int evaluation(const char *board);
        int winner(const char *gs);
};

#endif