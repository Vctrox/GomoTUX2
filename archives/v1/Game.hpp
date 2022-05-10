#ifndef Game_H
#define Game_H

#include <iostream>
#include "Board.hpp"
#include "IA.hpp"
#include <vector>
#include <unordered_map>

class Game
{
    private:
        Board board;
        IA brain;
    public:
        Game();
        bool play(int x, int y);
        void run();
};

#endif
