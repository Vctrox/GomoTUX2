#include <iostream>
#include <vector>

#include "Board.hpp"

int main()
{
    //Game game = Game();
    //game.run();
    
    Board board = Board();
    board.display();
    cout << board.getBoard() << endl;

}