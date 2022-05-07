#include <iostream>
#include <unordered_map>
#include <vector>

#include "Board.hpp"

using namespace std;

class IA {
    private:
        unordered_map<string, int> hashTable;

    public:
        int evaluation(Board & board, bool isMax);
        int minimaxAlphaBeta(Board & board, int depth, bool isMax, int alpha, int beta, int x, int y);
        void addToHashTable(Board & board, int eval);
        bool checkHashTable(Board & board);
};