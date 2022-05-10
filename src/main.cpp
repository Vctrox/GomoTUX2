#include <iostream>
#include <vector>

#include "Board.hpp"
#include "IA.hpp"
#include "Game.hpp"

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
    /*
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
    cout<<(cerveau.checkHashTable(board)?"trouve":"pas trouve") << endl;*/

    //Game game = Game();
    //game.run();

    
    Board board = Board();

    board.setValue(7, 7, PLAYER_SYMBOL);
    //board.setValue(8, 8, COMPUTER_SYMBOL);
    //board.setValue(7, 6, PLAYER_SYMBOL);
    //board.setValue(7, 8, COMPUTER_SYMBOL);
    //board.setValue(6, 8, PLAYER_SYMBOL);
    //board.setValue(8, 7, COMPUTER_SYMBOL);
    //board.setValue(8, 6, PLAYER_SYMBOL);
    //board.setValue(9, 5, COMPUTER_SYMBOL);
    //board.setValue(5, 9, PLAYER_SYMBOL);

    IA ia = IA("patterns.csv");

    //cout << ia.evaluation(board, true) << endl;

    board.display();

}