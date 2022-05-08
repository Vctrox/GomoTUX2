#ifndef IA_H
#define IA_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <limits>

#include "Board.hpp"

using namespace std;

const int MAX_INT = numeric_limits<int>::max();
const int MIN_INT = numeric_limits<int>::min();

class IA
{
private:
    unordered_map<string, int> hashTable;
    vector<string> patterns;
    vector<int> patternScores;

public:
    IA(const string patternFile);
    int evaluation(Board & board, bool isMax);
    int countPattern(Board & board, string pattern);
    int countPatternRow(const string board, string pattern);
    int countPatternColumn(const string board, string pattern, int spaces = 14);
    int countPatternFirstDiag(const string board, string pattern, int spaces = 15);
    int countPatternSecondDiag(const string board, string pattern, int space = 13);
    int minimaxAlphaBeta(Board & board, int depth, bool isMax, int alpha, int beta, int x, int y);
    void addToHashTable(Board & board, int eval);
    bool checkHashTable(Board & board);
    int getHashEval(Board & board);
};

#endif