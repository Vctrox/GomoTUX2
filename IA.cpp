#include "IA.hpp"
#include <array>
#include <limits>
#include <string>
#include <sstream>
#include <regex>

IA::IA(const string patternFileName) {
    ifstream file(patternFileName);

    if (!file.is_open()) {
        cout << "could not open pattern file";
    }

    string pattern;
    while (getline(file >> ws, pattern, ',')){
        int score;
        if (file >> score) {
            patterns.push_back(pattern);
            patternScores.push_back(score);
        }
    }    
}

int IA::evaluation(Board &board, bool isMax)
{
    return 0;
}

int IA::countPattern(Board &board, string pattern)
{
    int count = 0;
    string boardString = board.getBoard();
    // count += countPatternRow(boardString, pattern);
    count += countPatternColumn(boardString, pattern);
    // count += countPatternFirstDiag(boardString, pattern);
    // count += countPatternSecondDiag(boardString, pattern);
    return count;
}

int IA::countPatternRow(const string board, string pattern)
{
    int count = 0;
    regex const reg(pattern);

    for (int i = 0 ; i < N ; i++)
    {
        string row = board.substr(i * N, N);
        count += ptrdiff_t(distance(
            sregex_iterator(row.begin(), row.end(), reg),
            sregex_iterator())
        );
    }
    return count;
}

int IA::countPatternColumn(const string board, string pattern)
{   
    //TO FINISH
    
    int count = 0;
    int space = 14;
    string verticalPattern = "(?=(";
    for (int i = 0 ; i < pattern.length() ; i++)
    {
        verticalPattern += pattern[i];
        if (i+1 != pattern.length()){verticalPattern += ".{" + to_string(space) +"}";}
    }
    verticalPattern += ")+)";

    regex const reg(verticalPattern);

    count += ptrdiff_t(distance(
        sregex_iterator(board.begin(), board.end(), reg),
        sregex_iterator())
    );
    return count;
}

int IA::countPatternFirstDiag(const string board, string pattern)
{
    //TODO
    int count = 0;
    int space = 15;
    regex const reg(pattern);
    
    return count;
}

int IA::countPatternSecondDiag(const string board, string pattern)
{
    //TODO
    int count = 0;
    int space = 13;
    regex const reg(pattern);

    return count;
}

int IA::minimaxAlphaBeta(Board &board, int depth, bool isMax, int alpha, int beta, int x, int y) {
    char c = isMax ? board.getComputerSymbol() : board.getPlayerSymbol();
    
    board.setValue(x, y, c);

    if (board.winMove(x, y)) {
        board.setValue(x, y, '.');
        if (isMax)
            return numeric_limits<int>::max();
        else
            return numeric_limits<int>::min();
    }

    return 0;
}