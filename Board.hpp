#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>

using namespace std;

const int N = 15;
const char PLAYER_SYMBOL = 'X';
const char COMPUTER_SYMBOL = 'O';
const char EMPTY_SYMBOL = '-';

class Board
{
private:
    char board[N][N];
    int movesCount;

public:
    Board();
    void display();
    void setValue(int x, int y, char c);
    bool checkEmpty(int x, int y);
    bool rowWinMove(int x, int y);
    bool columnWinMove(int x, int y);
    bool firstDiagWinMove(int x, int y);
    bool secondDiagWinMove(int x, int y);
    bool winMove(int x, int y);
    bool draw();
    char getValue(int x, int y);
    int getMovesCount();
    string getBoard();
    char getComputerSymbol() { return COMPUTER_SYMBOL; };
    char getPlayerSymbol() { return PLAYER_SYMBOL; };
    char getEmptySymbol() { return EMPTY_SYMBOL; };
};

#endif