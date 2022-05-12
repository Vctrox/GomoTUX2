#ifndef GOMOTUX_H
#define GOMOTUX_H

#include <cstring>
#include "globals.hpp"

const int size = 11;

class GomoTux {
    private:
        struct Pattern {
            char min_occur;
            char length;
            char blocks;
            char spaces;
        };
        struct MeasureMove{
            char length;
            char blocks;
            char spaces;
        };
        Pattern *patterns;
        int *scores;
        int pattern_skip[];

    public:RenjuAIEval::DirectionMeasurement
        GomoTux();
        static void MeasureDirection(const char *board,
                                 int x, int y,
                                 int dx, int dy,
                                 int player,
                                 bool consecutive,
                                 GomoTux::MeasureMove *result);
};

#endif