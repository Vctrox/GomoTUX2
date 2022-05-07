#include "IA.hpp"
IA::IA(const string patternFile){}

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
    int space = 14 - pattern.length();
    string verticalPattern = "";
    // for (int i = 0 ; i < pattern.length() ; i++)
    // {
    //     verticalPattern += (pattern[i] == '.' ? "\\." : pattern[i]);
    // }

    regex const reg("(" + pattern + ").{"+ to_string(space) +"}");

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
    int space = 15 - pattern.length();
    regex const reg(pattern);
    
    return count;
}
int IA::countPatternSecondDiag(const string board, string pattern)
{
    //TODO
    int count = 0;
    int space = 13 - pattern.length();
    regex const reg(pattern);

    return count;
}
int IA::minimaxAlphaBeta(Board &board, int depth, bool isMax, int alpha, int beta, int x, int y)
{
    return 0;
}
void IA::addToHashTable(Board &board, int eval)
{
}
bool IA::checkHashTable(Board &board)
{
    return false;
}