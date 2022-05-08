#include "Game.hpp"
#include "Board.hpp"
#include <iostream>
#include <unordered_map>

Game::Game(const string patternFile)
{
    board = new Board();
    brain = new IA(patternFile);
}

void Game::run()
{
    //welcome
    cout << "Welcome" << endl;
    cout << "would you like to play? Y/n :";
    char awnser;
    do{
    cin >> awnser;
    cout << endl;
    if(awnser=='n'){
        cout << "Good by beautie" <<endl;
        return;
    }
    else if(awnser == 'Y'){
        cout << "Welcome to the best game ever made" << endl;
        break;
    }
    else{
        cout << "another one: ";
    }
    }while(awnser!='Y' or awnser!='n');

    //jouer en ou en 2
    int role;
    cout << "Would you like to play first or second? 1/2: ";
    do
    {
    cin >> role;
    if(role==1 or role==2){
        cout << "okay you are going to play: " << role << endl;
        break;
    }
    else{
        cout << "another one: ";
    }
    }while(role!=1 or role!= 2);

    bool player;
    role==1 ? player=true:player=false; 
    
    //commencer

    //corespondance alphabet - number
    char alphabet[26]={'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    unordered_map<char, int> correspondance;
    for(int i=0;i<N;i++){
        correspondance.insert({alphabet[i],i});
    }

    bool finish=true;
    while (finish) {
        board->display();
        if(player){
            char l;
            int x;
            int y;
            while(x>15 && x<0 && y>15 && y<0 && board->checkEmpty(x, y)){
                cout << "Coordonate of the desire move\n x: ";
                cin >> l;
                cout << "y: ";
                cin >> y;
                player=(player ? false :true);
            }
        }
        else{
            vector<int> nextMove = nextMove(board);
            int lig=nextMove[0];
            int col=nextMove[1];
            if(board->checkEmpty(lig, col)){
                board->setValue(lig, col, COMPUTER_SYMBOL);
            }
            player=(player ? false :true);
        }
    }
}

bool Game::play(int x, int y){
    return true;
}