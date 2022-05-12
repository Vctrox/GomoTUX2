#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

using namespace std;

const int N = 15;
const char PLAYER_SYMBOL = 'X';
const char COMPUTER_SYMBOL = 'O';
const char EMPTY_SYMBOL = '-';
const char ALPHABET[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

class Board
{
private:
    char board[N*N];
    int movesCount;

public:
    Board();
    void display();
    void display2();
    void setValue(int x, int y, char c);
    bool checkEmpty(int x, int y);
    bool rowWinMove(int x, int y);
    bool columnWinMove(int x, int y);
    bool firstDiagWinMove(int x, int y);
    bool secondDiagWinMove(int x, int y);
    bool winMove(int x, int y);
    bool draw();
    bool adjacent(int x, int y);
    char getValue(int x, int y);
    int getMovesCount();
    string getBoard();
    char getComputerSymbol() { return COMPUTER_SYMBOL; };
    char getPlayerSymbol() { return PLAYER_SYMBOL; };
    char getEmptySymbol() { return EMPTY_SYMBOL; };
};

#endif