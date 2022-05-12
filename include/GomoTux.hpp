#ifndef GOMOTUX_H
#define GOMOTUX_H

#include <cstring>
#include <limits>
#include "globals.hpp"

const int pattern_size = 11;

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
        int *pattern_skip;

    public:
        GomoTux();
            // Measure a single direction
            void measureInOneDirection(const char *board,
                                 int x, int y,
                                 int dx, int dy,
                                 int player,
                                 bool consecutive,
                                 GomoTux::MeasureMove *result);

            void measureInAllDirections(const char *gs,
                                       int r,
                                       int c,
                                       int player,
                                       bool consecutive,
                                       GomoTux::MeasureMove *adm);            

            int matchPattern(MeasureMove *all_direction_measurement,
                            Pattern *patterns);

            // Evaluate one possible move as a player
            int evalMove(const char *board, int x, int y, int player);

            int evalInAllDirections(MeasureMove *all_direction_measurement);
            
            int evalBoard(const char *board, int player);
};

            

#endif