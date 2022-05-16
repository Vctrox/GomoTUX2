#ifndef GAME_H
#define GAME_H

#include <vector>
#include <ctime>

class Game
{
    public:
        Game();
        static std::vector<int> generateMove(const char *board, int player, int depth,
                                           int time_limit);
        static void run();
};

#endif