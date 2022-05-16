#include <game.h>
#include "gomotux_ai.h"
#include <iostream>
#include <board.h>

using namespace std;

vector<int> Game::generateMove(const char *board_string, int player, int search_depth,
                                           int time_limit) {
    // Record start time
    std::clock_t clock_begin = std::clock();

    // Generate move
    int x, y, winning_player, actual_depth;
    unsigned int node_count, eval_count, pm_count;
    
    GomoTuxAI::generateMove(board_string, player, search_depth, time_limit, &actual_depth,
                                          &x, &y, &winning_player, &node_count, &eval_count);

    // Calculate elapsed CPU time
    std::clock_t clock_end = std::clock();
    std::clock_t cpu_time = (clock_end - clock_begin) * 1000 / CLOCKS_PER_SEC;

    vector<int> v;
    v.push_back(x);
    v.push_back(y);
    v.push_back(cpu_time);

    return v;

}

void Game::run() {
    string logo = "   _____                    _______         ___\n    / ____|                  |__   __|       |__ \\ \n  | |  __  ___  _ __ ___   ___ | |_   ___  __  ) |\n | | |_ |/ _ \\| '_ ` _ \\ / _ \\| | | | \\ \\/ / / /\n  | |__| | (_) | | | | | | (_) | | |_| |>  < / /_\n   \\_____|\\___/|_| |_| |_|\\___/|_|\\__,_/_/\\_\\____|";

    int moves = 0;
    cout << logo << endl << endl;

    cout << "Welcome to GomoTux 2" << endl;
    int ai_player = 0;

    while (ai_player == 0) {
        cout << "Do you want to play black (play first) or white (play second) ? [B/w]" << endl;

        string choice;
        getline(cin, choice);

        if (choice == "B" || choice == "b" || choice == "")
            ai_player = 2;

        if (choice == "W" || choice == "w")
            ai_player = 1;
    }

    g_board_size = 15;
    g_gs_size = (unsigned int)g_board_size * g_board_size;
    char gs_string[226] = {0};
    
    int search_depth = -1;
    int time_limit = 5500;

    memcpy(gs_string, "000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", 226);
    search_depth = 0;

    bool ai_fisrt = false;

    if (ai_player == 1) {
        ai_fisrt = true;
        gs_string[112] = '1';
        moves += 1;
        cout << "I've played H:8" << endl;
    }

    string move_string;
    int x, y;

    for (int i = 0; i < 60 - moves; i++) {
        int valid = false;

        //cout << "\x1B[2J\x1B[H";
        Board::display2(gs_string);

        while (true) {
            cout << "It's your turn. " << endl << "Move format: <row_letter><coluln_number>, ex: \"D5\"" << endl;
            getline(cin, move_string);

            if (move_string.size() < 2) {
                cout << "Bad input format" << endl;
                continue;
            }
            if ((int)move_string[0] < 65 || (int)move_string[0] > 79) {
                cout << "Bad input format" << endl;
                continue;
            }
            if ((int)move_string[1] < 49 || (int)move_string[1] > 57) {
                cout << "Bad input format" << endl;
                continue;
            }

            x = (int)move_string[0] - 65;
            if (move_string[1] == 49 && move_string[2] != 0)
                y = ((int)move_string[1] - 39) + ((int)move_string[2] - 49);
            else
                y = (int)move_string[1] - 49;
            break;
        }

        Board::setCell(gs_string, x, y, ai_player == 1 ? '2' : '1');
        moves += 1;
        vector<int> result = Game::generateMove(gs_string, ai_player, search_depth, time_limit);

        if (ai_fisrt && moves == 2) {
            Board::setCell(gs_string, 3, 3, '1');
        } else {

        Board::setCell(gs_string, result[0], result[1], ai_player == 1 ? '1' : '2');
        }
        moves += 1;
        cout << "I've played " << static_cast<char>(65 + result[0]) << ":" << result[1] + 1 << " in " << (float)result[2] / 1000 << "s" << endl;
    }
}