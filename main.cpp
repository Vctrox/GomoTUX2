#include <iostream>

#include "Board.hpp"
#include "IA.hpp"

int main()
{

    /*Board board = Board();

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

    return 0;*/

    Board board = Board();
    IA cerveau = IA("patterns.csv");
    
    board.setValue(3, 14, PLAYER_SYMBOL);
    board.setValue(4, 8, PLAYER_SYMBOL);
    board.setValue(6, 8, PLAYER_SYMBOL);
    board.setValue(8, 8, PLAYER_SYMBOL);
    board.setValue(14, 13, PLAYER_SYMBOL);

    if(!cerveau.checkHashTable(board)){
        cerveau.addToHashTable(board, 3);
    }
    cout<<cerveau.getHashEval(board)<<endl;

    //board.setValue(1, 1, PLAYER_SYMBOL);
    cout<<(cerveau.checkHashTable(board)?"trouve":"pas trouve") << endl;

}