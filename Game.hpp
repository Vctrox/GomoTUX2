#ifndef Game_H
#define Game_H

#include <iostream>
#include "Board.hpp"
#include "IA.hpp"
#include <vector>

class Game
{
    private:
        Board * board;
        IA * brain;
    public:
        Game(const string patternFile);
        bool play(int x, int y);
        void run();
};

#endif
