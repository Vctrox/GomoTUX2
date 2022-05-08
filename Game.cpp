#include "Game.hpp"

Game::Game()
{
    
}

void Game::run()
{
    //welcome
    cout << "Welcome" << endl;
    cout << "would you like to play? Y/n :";
    char awnser;
    
    while(awnser!='Y' && awnser!='n'){
        cin >> awnser;
        cout << endl;
        if(awnser=='n'){
            cout << "Good by beautie" <<endl;
            return;
        }
        else if(awnser == 'Y'){
            cout << "Welcome to the best game ever made" << endl;
        }
        else{
            cout << "another one: ";
        }
    }

    //jouer en ou en 2
    int role;
    cout << "Would you like to play first or second? 1/2: ";
    
    while(role!=1 && role!= 2)
    {
        cin >> role;
        
        if(role==1 || role==2){
            cout << "okay you are going to play " << (role==1? "first" : "second") << endl;
        }
        else{
            cout << "another one: ";
        }
    }
    cout<< "yes";

    bool player;
    player=(role==1 ? true:false); 
    
    //start

    //corespondance alphabet - number
    unordered_map<char, int> correspondance;
    for(int i=0;i<N;i++){
        correspondance.insert({ALPHABET[i],i});
    }

    bool finish=true;
    while (finish) {
        //board.display();
        if(player){
            char l;
            int x=-1;
            int y=-1;
            while(x>15 && x<0 && y>15 && y<0 && board.checkEmpty(x, y)){
                cout << "Coordonate of the desire move\n x: ";
                cin >> l;
                if(correspondance.find(l)!=correspondance.end()){
                    x=correspondance[l];
                }
                cout << "y: ";
                cin >> y;
                player=(player ? false :true);
            }
            if(board.winMove(x, y)){
                cout << "Great Great you win against the amazing me\nCome try again";
                finish=false;
            }
        }
        else{
            vector<int> nextMove = brain.nextMove(board);
            int lig=nextMove[0];
            int col=nextMove[1];
            if(board.checkEmpty(lig, col)){
                if(board.winMove(lig, col)){
                    cout << "sorry computer better than you AHAHAHA\nCome try again noob"<< endl;
                    finish=false;
                }
                board.setValue(lig, col, COMPUTER_SYMBOL);
            }
            player=(player ? false :true);
            cout<< "else";
        }
    }
}

bool Game::play(int x, int y){
    return true;
}