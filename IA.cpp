#include "IA.hpp"
#include "Board.hpp"
#include <array>
#include <cstddef>
#include <limits>
#include <string>
#include <sstream>
#include <regex>
#include <vector>

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

    count += countPatternRow(boardString, pattern);
    count += countPatternColumn(boardString, pattern);
    count += countPatternFirstDiag(boardString, pattern);
    count += countPatternSecondDiag(boardString, pattern);
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

int IA::countPatternColumn(const string board, string pattern, int spaces)
{   
    int count = 0;

    // Pattern creation
    string verticalPattern = "(?=(";
    for (int i = 0 ; i < pattern.length() ; i++)
    {
        verticalPattern += pattern[i];
        if (i+1 != pattern.length()){verticalPattern += ".{" + to_string(spaces) +"}";}
    }
    verticalPattern += ")+)";

    regex const reg(verticalPattern);

    count += ptrdiff_t(distance(
        sregex_iterator(board.begin(), board.end(), reg),
        sregex_iterator())
    );
    return count;
}

int IA::countPatternFirstDiag(const string board, string pattern, int spaces)
{
    int count = 0;
    int length = pattern.length();
    int posMax = N - length;

    // Pattern creation
    string diagPattern = "(?=(";
    for (int i = 0 ; i < length ; i++)
    {
        diagPattern += pattern[i];
        if (i+1 != length){diagPattern += ".{" + to_string(spaces) +"}";}
    }
    diagPattern += ")+)";

    regex const reg(diagPattern);
    for(sregex_iterator i = sregex_iterator(board.begin(), board.end(), reg);
                            i != sregex_iterator();
                            ++i )
    {
        smatch m = *i;
        int pos = m.position();
        if ((pos % N < posMax) && (pos/N < N - length/2) ){count++;}
    }

    return count;
}

int IA::countPatternSecondDiag(const string board, string pattern, int spaces)
{
    int count = 0;
    int length = pattern.length();
    int posMin = length;

    // Pattern creation
    string diagPattern = "(?=(";
    for (int i = 0 ; i < length ; i++)
    {
        diagPattern += pattern[i];
        if (i+1 != length){diagPattern += ".{" + to_string(spaces) +"}";}
    }
    diagPattern += ")+)";

    regex const reg(diagPattern);
    for(sregex_iterator i = sregex_iterator(board.begin(), board.end(), reg);
                            i != sregex_iterator();
                            ++i )
    {
        smatch m = *i;
        int pos = m.position();
        if ((pos % N > posMin) && (pos/N < N - length/2) ){count++;}
    }

    return count;
}

int IA::minimaxAlphaBeta(Board &board, int depth, bool isMax, int alpha, int beta, int x, int y) {
    char c = isMax ? COMPUTER_SYMBOL : PLAYER_SYMBOL;
    
    board.setValue(x, y, c);

    // Fin du jeu
    if (board.winMove(x, y)) {
        board.setValue(x, y, EMPTY_SYMBOL);
        if (isMax)
            return MAX_INT;
        else
            return MIN_INT;
    } else if (board.draw()) {
        board.setValue(x, y, EMPTY_SYMBOL);
        return 0;
    }

    // Fin de la recursion
    if (depth == 0) {
        int eval = 0;
        if (checkHashTable(board))
            eval = getHashEval(board);
        else {
            eval = evaluation(board, isMax);
            addToHashTable(board, eval);
        }
        board.setValue(x, y, EMPTY_SYMBOL);

        return eval;
    }

    // les prochains coup possible (x et y)
    vector<int> xs;
    vector<int> ys;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board.adjacent(x, y)) {
                xs.push_back(x);
                ys.push_back(y);
            }
        }
    }

    int len = (int) xs.size();
    if (isMax) { // Il faut minimiser parceque c'est le tour du joueur
        int m = MAX_INT;
        for (int i = 0; i < len; i++) {
            int tmp = minimaxAlphaBeta(board, depth - 1, false, alpha, beta, xs[i], ys[i]);
            if (m > tmp)
                m = tmp;
            if (beta > m)
                beta = m;
            if (alpha >= beta)
                break;
        }
        board.setValue(x, y, EMPTY_SYMBOL);

        return m;
    } else { // Il faut maximiser
        int M = MIN_INT;
        for (int i = 0; i < len; i++) {
            int tmp = minimaxAlphaBeta(board, depth, isMax, alpha, beta, x, y);
            if (M < tmp)
                M = tmp;
            if (alpha < M)
                alpha = M;
            if (alpha >= beta)
                break;
        }
        board.setValue(x, y, EMPTY_SYMBOL);

        return M;
    }


    return 0;
}

vector<int> IA::nextMove(Board &board) 
{
    vector<int> v = {0, 0};
    int M = MIN_INT;
    int x = N/2, y = N/2;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board.adjacent(i, j)) {
                int tmp = minimaxAlphaBeta(board, 5, true, MIN_INT, MAX_INT, i, j);
                if (M < tmp) {
                    M = tmp;
                    x = i;
                    y = j;
                }
            }
        }
    }
    v[0] = x;
    v[1] = y;

    return v;
}

void IA::addToHashTable(Board & board, int eval){
    string board_s = board.getBoard();
    hashTable.insert({board_s,eval});
}

bool IA::checkHashTable(Board &board){
    string board_s = board.getBoard();
    if(hashTable.find(board_s) == hashTable.end())
        return false;
    return true;
}

int IA::getHashEval(Board &board){
    string board_s=board.getBoard();
    return hashTable[board_s];
}