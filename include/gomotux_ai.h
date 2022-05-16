#ifndef GOMOTUX_AI_H
#define GOMOTUX_AI_H

#include <cstring>
#include "gomotux_eval.h"
#include "globals.h"
#include <vector>


class GomoTuxAI
{
    public:

        static void generateMove(const char *board_string, int player,
                            int search_depth, int time_limit,
                            int *current_depth, int *x, int *y, int *winner,
                            unsigned int *node_count, unsigned int *eval_count);
        struct Move {
            int x;
            int y;
            int heuristic_val;
            int actual_score;

            bool operator<(Move other) const {
                return heuristic_val > other.heuristic_val;
            }   
        };
    private:

        static int presetSearchBreadth[5];

        static void gsFromString(const char *board_string, char *board);

        static void getBestMove(const char *board, int player, int search_depth, int time_limit,
                           int *current_depth, int *x, int *y, int *winner,
                           unsigned int *node_count, unsigned int *eval_count);

        static void minimaxAlphaBetaIterative(const char *board, int player, int depth, int time_limit,
                                      int *current_depth, int *x, int *y);

        static int minimaxAlphaBeta(char *board, int player, bool isMax, int initial_depth, int depth, int alpha, int beta,
                                     int *x, int *y);

        static void searchMovesOrdered(const char *board, int player, std::vector<GomoTuxAI::Move> *result);
};

#endif