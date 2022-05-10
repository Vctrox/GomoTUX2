#include "Game.hpp"
#include "Board.hpp"

Game::Game(){}

unordered_map<char,int> Game::getBinds(){
    unordered_map<char,int> binds;
    for(int i = 0 ; i < N ; i++){
        binds.insert({ALPHABET[i],i});
    }
    return binds;
}

int Game::whoFirst(){
    // 1 : player is first
    // 0 : computer is first
    // -1 : error/wrong input
    string choice;
    cout << "Would you like to play first ? [Y]/n ";
    getline(cin, choice);

    if (choice.empty() || choice == "Y"){
        return 1;
    } else if (choice == "n"){
        return 0;
    } else {
        return -1;
    }
}

array<int,2> Game::input(unordered_map<char,int> bind)
{
    array<int,2> positions = {-1,-1}; // x and y
    string str;
    while (positions[0] == -1 || positions[1] == -1){
        cout << "Your move (format : XY) : ";
        getline(cin, str);

        if (str.empty() || (str.size() != 2 && str.size() != 3)) {
            cout << "Try again : "; 
            continue;
        }
        cout << endl;

        if(bind.find(str[0]) != bind.end()){
            if(str.size() == 2){
                int y = str[1] - '0';
                if (y < 1 || y > N) { 
                    continue;
                }
                positions[0] = bind[str[0]];
                positions[1] = y - 1;
            }
            else{
                int y = (str[1] - '0') * 10 + (str[2] - '0');
                if (y < 1 || y > N) { 
                    continue;
                }
                positions[0] = bind[str[0]];
                positions[1] = y - 1;
            }
            
        
        }
    }
    return positions;
}

void Game::run()
{
    //welcome
    cout << "Welcome to GomoTUX" << endl;

    // Who is playing
    int role = -1;
    while (role == -1){
        role = whoFirst();
    }

    bool player = (role == 1 ? true : false); 
    
    //bind alphabet - number
    unordered_map<char, int> bind = getBinds();

    
    int x;
    int y;

    bool finish = true;
    while (finish) {
        board.display2();
        if(player){
            cout << "#PLAYER'S TURN" << endl;
            
            while (!board.checkEmpty(x,y)) {
                array<int,2> positions = input(bind);
                x = positions[0];
                y = positions[1];
            }
            board.setValue(x, y, PLAYER_SYMBOL);
            cout << "Move : " << x << "," << y << endl;
            if(board.winMove(x, y)){
                // cout << "Great Great you won against the amazing me\nCome try again";
                cout << "WINNER : You, gratz !" << endl;
                finish = false;
            }
        }
        else{
            cout << "COMPUTER'S TURN" << endl;
            time_t start = time(nullptr);
            vector<int> nextMove = brain.nextMove(board);
            time_t end = time(nullptr);
            cout<< "computer calculation time: " << end - start << " second" <<endl;
            int lig = nextMove[0];
            int col = nextMove[1];
            if (board.checkEmpty(lig,col))
            {
                board.setValue(lig, col, COMPUTER_SYMBOL);
                cout << "Move : " << ALPHABET[lig] << "," << col + 1 << endl;
                if(board.winMove(lig, col)){
                    // cout << "sorry computer better than you AHAHAHA\nCome try again noob" << endl;
                    cout << "WINNER : Computer" << endl;
                    finish = false;
                }
            } else {
                cout << "ERROR : decided to place in an not empty place" << endl;
                break;
            }
        }
        player = !player;
    }
    cout << "Game finished with success." << endl;
}

bool Game::play(int x, int y){
    return true;
}