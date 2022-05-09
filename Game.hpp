#ifndef Game_H
#define Game_H

#include <iostream>
#include "IA.hpp"
#include <vector>
#include <unordered_map>
#include <tuple>
#include <array>

class Game
{
    private:
        Board board;
        IA brain;
    public:
        Game();
        bool play(int x, int y);
        array<int,2> input(unordered_map<char, int> translate);
        unordered_map<char,int> getBinds();
        int whoFirst();
        void run();
};

#endif
