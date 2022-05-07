#include <iostream>

#include "Board.hpp"
#include "IA.hpp"

int main()
{

    Board board = Board();

    board.setValue(3, 9, PLAYER_SYMBOL);
    board.setValue(4, 8, PLAYER_SYMBOL);
    board.setValue(5, 7, PLAYER_SYMBOL);
    board.setValue(6, 6, PLAYER_SYMBOL);
    board.setValue(7, 5, PLAYER_SYMBOL);
    cout << board.secondDiagWinMove(3, 4) << endl;

    board.display();

    cout << endl
         << board.getBoard() << endl;

    IA ia = IA("patterns.csv");

    return 0;
}