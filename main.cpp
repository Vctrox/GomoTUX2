#include <iostream>

#include "Board.hpp"
#include "IA.hpp"

int main()
{

    Board board = Board();

    board.setValue(3, 14, PLAYER_SYMBOL);
    board.setValue(4, 8, PLAYER_SYMBOL);
    board.setValue(6, 8, PLAYER_SYMBOL);
    board.setValue(8, 8, PLAYER_SYMBOL);
    board.setValue(14, 13, PLAYER_SYMBOL);

    board.display();

    cout << endl
         << board.getBoard() << endl;

    string expression = ".X.";
    IA ia = IA("patterns.csv");
    int count = ia.countPattern(board,expression);
    cout << count << endl;

    return 0;
}