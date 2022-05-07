#include <iostream>

using namespace std;

const int N = 15;
const char playerSymbol = 'X';
const char computerSymbol = 'O';
const char emptySymbol = '.';

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
};

