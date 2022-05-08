#ifndef Game_H
#define Game_H

#include <iostream>
#include "Board.hpp"
#include "IA.hpp"

class Game
{
    private:
        Board * board;
        IA * brain;
    public:
        Game(const string patternFile);
        void play();
        void run();
};

#endif
