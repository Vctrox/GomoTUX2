#include "Board.hpp"

using namespace std;

Board::Board()
{
    board = new board[g_size];

    for (int i = 0; i < g_size; i++)
        for (int j = 0; j < g_size; j++)
            board[i * g_size + j] = EMPTY_SYMBOL;
    movesCount = 0;
}
 
void Board::display()
{
    cout << "   ";
    for (int i = 1; i <= g_size; i++)
    {
        string s = i < 10 ? "  " : " ";
        cout << i << s;
    }
    cout << endl;
    for (int i = 0; i < g_size; i++)
    {
        cout << ALPHABET[i] << "  ";
        for (int j = 0; j < g_size; j++)
        {
            cout << board[i*g_size+j] << "  ";
        }
        // cout <<i;
        cout << endl;
    }
    cout << endl;
}

bool Board::checkEmpty(int x, int y)
{
    if (x >= 0 && x < g_size && y >= 0 && y < g_size && board[x * g_size + y] == EMPTY_SYMBOL)
        return true;
    return false;
}

void Board::setValue(int x, int y, char c)
{
    board[x * g_size + y] = c;
    if (c == EMPTY_SYMBOL)
        movesCount--;
    else
        movesCount++;
}

bool Board::rowWinMove(int x, int y)
{
    int count = 1;
    for (int i = 1; count < 5 && i < 5 && y + i < g_size && board[x * g_size + y + i] == board[x * g_size + y]; i++)
        count++;
    for (int i = 1; count < 5 && i < 5 && y - i >= 0 && board[x * g_size + y - i] == board[x * g_size + y]; i++)
        count++;
    return count == 5;
}

bool Board::columnWinMove(int x, int y)
{
    int count = 1;
    for (int i = 1; count < 5 && i < 5 && x + i < g_size && board[(x + i) * g_size + y] == board[x * g_size + y]; i++)
        count++;
    for (int i = 1; count < 5 && i < 5 && x - i >= 0 && board[(x - i) * g_size + y] == board[x * g_size + y]; i++)
        count++;
    return count == 5;
}

bool Board::firstDiagWinMove(int x, int y)
{
    int count = 1;
    for (int i = 1; count < 5 && i < 5 && x + i < g_size && y + i < g_size && board[(x + i) * g_size + (y + i)] == board[x * g_size + y]; i++)
        count++;
    for (int i = 1; count < 5 && i < 5 && x - i >= 0 && y - i >= 0 && board[(x - i) * g_size + (y - i)] == board[x * g_size + y]; i++)
        count++;
    return count == 5;
}

bool Board::secondDiagWinMove(int x, int y)
{
    int count = 1;
    for (int i = 1; count < 5 && i < 5 && x + i < g_size && y - i >= 0 && board[(x + i) * g_size + (y - i)] == board[x*g_size+y]; i++)
        count++;
    for (int i = 1; count < 5 && i < 5 && x - i >= 0 && y + i < g_size && board[(x - i) * g_size + (y + i)] == board[x * g_size + y]; i++)
        count++;
    return count == 5;
}

bool Board::winMove(int x, int y)
{
    return rowWinMove(x, y) || columnWinMove(x, y) || firstDiagWinMove(x, y) || secondDiagWinMove(x, y);
}

bool Board::draw()
{
    return movesCount == g_size * g_size;
}

bool Board::adjacent(int x, int y) 
{
    int isAdj = false;

    if (board[x * g_size + y] != EMPTY_SYMBOL)
        return false;

    int adj[8][2] {
        {-1, -1}, 
        {-1, 0},
        {-1, 1},
        {0, -1},
        {0, 1},
        {1, -1},
        {1, 0},
        {1, 1} 
    };

    for (auto a:adj) {
        if (x + a[0] >= 0 && x + a[0] < g_size && y + a[1] >= 0 && y + a[1] < g_size) {
            if (isAdj) break;
            isAdj = board[(x + a[0]) * g_size + ( y + a[1])] != EMPTY_SYMBOL;
        }
    }

    return isAdj;

}

char Board::getValue(int x, int y)
{
    return board[x*g_size+y];
}

int Board::getMovesCount()
{
    return movesCount;
}

string Board::getBoard()
{
    string out = "";
    for (int i = 0; i < g_size; i++)
        for (int j = 0; j < g_size; j++)
            out += (
                board[i * g_size + j] == COMPUTER_SYMBOL ? 
                    '1' :
                    (board[i * g_size + j] == PLAYER_SYMBOL ? 
                        '2' :
                        '0'
                    )
            );
    return out;
}