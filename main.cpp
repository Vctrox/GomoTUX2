#include <iostream>

#include "Board.hpp"

int main() {

    Board board = Board();

    board.setValue(3, 9, playerSymbol);
    board.setValue(4, 8, playerSymbol);
    board.setValue(5, 7, playerSymbol);
    board.setValue(6, 6, playerSymbol);
    board.setValue(7, 5, playerSymbol);
    cout << board.secondDiagWinMove(3, 4) << endl;

    board.display();

    cout << endl << board.getBoard() << endl;

    return 0;
}