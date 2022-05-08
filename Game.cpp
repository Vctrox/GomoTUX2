#include "Game.hpp"

Game::Game(const string patternFile)
{
    board = new Board();
    brain = new IA(patternFile);
}

void Game::play()
{
    cout << "Welcome" << endl;
    cout << "would you to play Y/n? :";
    char awnser='Y';
    do{
    cin >> awnser;
    cout << endl;
    if(awnser=='n'){
        cout << "Good by beautie" <<endl;
        return;
    }
    else if(awnser == 'Y'){
        cout << "Welcom to the best game ever made" << endl;
    }
    else{
        cout << "another one";
    }
    }while(awnser!='Y' or awnser!='n');
}