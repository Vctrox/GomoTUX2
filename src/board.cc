#include <board.h>
#include <iostream>

using namespace std;

bool Board::remoteCell(const char *gs, int r, int c) {
    if (gs == nullptr) return false;
    for (int i = r - 2; i <= r + 2; ++i) {
        if (i < 0 || i >= g_board_size) continue;
        for (int j = c - 2; j <= c + 2; ++j) {
            if (j < 0 || j >= g_board_size) continue;
            if (gs[g_board_size * i + j] > 0) return false;
        }
    }
    return true;
}

void Board::display(const char*gs) {
    cout << "     ";
    for (int i = 0; i < g_board_size; i++)
    {
        string s = i < 10 ? "  " : " ";
        cout << i << s;
    }
    cout << endl << endl;
    for (int i = 0; i < g_board_size; i++)
    {
        string s = i < 10 ? "    " : "   ";
        cout << i << s;
        for (int j = 0; j < g_board_size; j++)
        {
            cout << g_symbols[(int)gs[g_board_size * i + j] - 48] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void Board::display2(const char*gs) {
    cout << "     ";
    for (int i = 0; i < g_board_size; i++)
    {
        string s = i < 10 ? "  " : " ";
        cout << i + 1 << s;
    }
    cout << endl << endl;
    for (int i = 0; i < g_board_size; i++)
    { 
        cout << static_cast<char>(65 + i) << "    ";
        for (int j = 0; j < g_board_size; j++)
        {
            cout << g_symbols[(int)gs[g_board_size * i + j] - 48] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}