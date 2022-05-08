#include "IA.hpp"
#include "Board.hpp"
#include <array>
#include <cstddef>
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
    int score=0;
    for(int i=0;i<patterns.size();i++){
        score+=countPattern(board,patterns[i])*patternScores[i];
    }
    return score;
}

int IA::countPattern(Board &board, string pattern)
{
    int count = 0;
    string boardString = board.getBoard();

    int space = N;
    count += countPatternRow(boardString, pattern, space);
    space = N-1;
    count += countPatternColumn(boardString, pattern, space);
    space = N;
    count += countPatternFirstDiag(boardString, pattern, space);
    space = N-2;
    count += countPatternSecondDiag(boardString, pattern, space);
    return count;
}

int IA::countPatternRow(const string board, string pattern, int space)
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

int IA::countPatternColumn(const string board, string pattern, int space)
{   
    int count = 0;

    // Pattern creation
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

int IA::countPatternFirstDiag(const string board, string pattern, int space)
{
    int count = 0;
    int posMax = N - pattern.length();

    // Pattern creation
    string diagPattern = "(?=(";
    for (int i = 0 ; i < pattern.length() ; i++)
    {
        diagPattern += pattern[i];
        if (i+1 != pattern.length()){diagPattern += ".{" + to_string(space) +"}";}
    }
    diagPattern += ")+)";

    smatch match;
    regex const reg(diagPattern);
    regex_search(board,match,reg);

    for (int i = 1 ; i < match.size(); i++)
    {
        int pos = match.position(i);
        if (pos % N < posMax) {count++;}
    }

    return count;
}

int IA::countPatternSecondDiag(const string board, string pattern, int space)
{
    int count = 0;
    int posMin = pattern.length();

    // Pattern creation
    string diagPattern = "(?=(";
    for (int i = 0 ; i < pattern.length() ; i++)
    {
        diagPattern += pattern[i];
        if (i+1 != pattern.length()){diagPattern += ".{" + to_string(space) +"}";}
    }
    diagPattern += ")+)";

    smatch match;
    regex const reg(diagPattern);
    regex_search(board,match,reg);

    for (int i = 1 ; i < match.size(); i++)
    {
        int pos = match.position(i);
        if (pos % N > posMin) {count++;}
    }

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

    if(depth==0){
        int eval=evaluation(board, isMax);
        //std::size_t coup = std::hash<>{}(board)
        return eval;
    }

    if(isMax){
        int maxEval=numeric_limits<int>::max();
        int eval;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(board.checkEmpty(i, j)){
                    eval=minimaxAlphaBeta(board, depth-1, isMax, alpha, beta, i, j);
                    maxEval=max(maxEval,eval);
                    alpha= max(alpha,eval);
                    if(beta<=alpha){
                        break;
                    }

                }
            }
        }
        return maxEval;
    }
    else{
        int minEval= numeric_limits<int>::min();
        int eval;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(board.checkEmpty(i, j)){
                    eval=minimaxAlphaBeta(board, depth-1, isMax, alpha, beta, i, j);
                    minEval= min(beta,eval);
                    beta= max(beta,eval);
                    if(beta<=alpha){
                        break;
                    }

                }
            }
        }
        return minEval;
    }

    return 0;
}

void IA::addToHashTable(Board & board, int eval){
    string board_s=board.getBoard();
    hashTable.insert({board_s,eval});
}

bool IA::checkHashTable(Board &board){
    string board_s=board.getBoard();
    if(hashTable.find(board_s)==hashTable.end()){
        return false;
    }
    return true;
}

int IA::getHashEval(Board &board){
    string board_s=board.getBoard();
    return hashTable[board_s];
}