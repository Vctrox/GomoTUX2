#include "Game.hpp"

Game::Game()
{
    
}

void Game::run()
{
    //welcome
    cout << "Welcome" << endl;
    cout << "would you like to play? Y/n :";
    char answer;
    
    while ( answer != 'Y' && answer != 'n'){
        cin >> answer;
        cout << endl;
        if(answer =='n'){
            cout << "Good bye beauty" <<endl;
            return;
        }
        else if(answer == 'Y'){
            cout << "Welcome to the best game ever made" << endl;
        }
        else{
            cout << "another one: ";
        }
    }

    //jouer en ou en 2
    int role;
    cout << "Would you like to play first or second? 1/2: ";
    
    while(role != 1 && role != 2)
    {
        cin >> role;
        
        if(role == 1 || role == 2){
            cout << "okay you are going to play " << (role == 1 ? "first" : "second") << endl;
        }
        else{
            cout << "another one: ";
        }
    }
    cout << "#PLAYER CHOSEN" << endl;

    bool player = (role == 1 ? true : false); 
    
    //start

    //corespondance alphabet - number
    unordered_map<char, int> correspondance;
    for(int i = 0 ; i < N ; i++){
        correspondance.insert({ALPHABET[i],i});
    }

    cout << "#CORRESPONDANCE" << endl;

    bool finish = true;
    
    bool firstRound = true;
    while (finish) {
        board.display();
        if(player){
            cout << "#PLAYER'S TURN" << endl;
            char l;
            int x = -1;
            int y = -1;
            while (!board.checkEmpty(x,y)) {
                cout << "Coordinate of the desire move\nLine (A to O) : ";
                cin >> l;
                if(correspondance.find(l) != correspondance.end()){
                    x = correspondance[l];
                }
                cout << "Column (1 to 15): ";
                cin >> y;
            }
            board.setValue(x, y-1, PLAYER_SYMBOL);
            if(board.winMove(x, y-1)){
                cout << "Great Great you won against the amazing me\nCome try again";
                finish = false;
            }
        }
        else{
            cout << "COMPUTER'S TURN" << endl;
            vector<int> nextMove = brain.nextMove(board);
            int lig = nextMove[0];
            int col = nextMove[1];
            if (board.checkEmpty(lig,col))
            {
                board.setValue(lig, col, COMPUTER_SYMBOL);
                if(board.winMove(lig, col)){
                    cout << "sorry computer better than you AHAHAHA\nCome try again noob" << endl;
                    finish = false;
                }
            } else {
                cout << "ERROR : decided to place in an not empty place" << endl;
            }
           
        }
        player = !player;
    }
}

bool Game::play(int x, int y){
    return true;
}