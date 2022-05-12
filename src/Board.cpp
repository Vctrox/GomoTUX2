#include "Board.hpp"

using namespace std;

Board::Board()
{

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i*N+j] = EMPTY_SYMBOL;
    movesCount = 0;
}
 
void Board::display()
{
    cout << "   ";
    for (int i = 0; i < N; i++)
    {
        string s = i < 10 ? "  " : " ";
        cout << i << s;
    }
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        string s = i < 10 ? "  " : " ";
        cout << i << s;
        for (int j = 0; j < N; j++)
        {
            cout << board[i*N+j] << "  ";
        }
        // cout <<i;
        cout << endl;
    }
    /*
    cout <<"   ";
    for (int i = 0 ; i < N; i++){
        string s = i < 10?"  ":" ";
        cout << i <<s;
    } */
    cout << endl;
}

void Board::display2()
{
    cout << "   ";
    for (int i = 1; i <= N; i++)
{
        string s = i < 10 ? "  " : " ";
        cout << i << s;
    }
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        cout << ALPHABET[i] << "  ";
        for (int j = 0; j < N; j++)
        {
            cout << board[i*N+j] << "  ";
        }
        // cout <<i;
        cout << endl;
    }
    cout << endl;
}

bool Board::checkEmpty(int x, int y)
{
    if (x >= 0 && x < N && y >= 0 && y < N && board[x*N+y] == EMPTY_SYMBOL)
        return true;
    return false;
}

void Board::setValue(int x, int y, char c)
{
    board[x*N+y] = c;
    if (c == EMPTY_SYMBOL)
        movesCount--;
    else
        movesCount++;
}

bool Board::rowWinMove(int x, int y)
{
    int count = 1;
    for (int i = 1; count < 5 && i < 5 && y + i < N && board[x*N+y + i] == board[x*N+y]; i++)
        count++;
    for (int i = 1; count < 5 && i < 5 && y - i >= 0 && board[x*N+y - i] == board[x*N+y]; i++)
        count++;
    return count == 5;
}

bool Board::columnWinMove(int x, int y)
{
    int count = 1;
    for (int i = 1; count < 5 && i < 5 && x + i < N && board[(x + i)*N+y] == board[x*N+y]; i++)
        count++;
    for (int i = 1; count < 5 && i < 5 && x - i >= 0 && board[(x - i)*N+y] == board[x*N+y]; i++)
        count++;
    return count == 5;
}

bool Board::firstDiagWinMove(int x, int y)
{
    int count = 1;
    for (int i = 1; count < 5 && i < 5 && x + i < N && y + i < N && board[(x + i)*N+(y + i)] == board[x*N+y]; i++)
        count++;
    for (int i = 1; count < 5 && i < 5 && x - i >= 0 && y - i >= 0 && board[(x - i)*N+(y - i)] == board[x*N+y]; i++)
        count++;
    return count == 5;
}

bool Board::secondDiagWinMove(int x, int y)
{
    int count = 1;
    for (int i = 1; count < 5 && i < 5 && x + i < N && y - i >= 0 && board[(x + i) * N + (y - i)] == board[x*N+y]; i++)
        count++;
    for (int i = 1; count < 5 && i < 5 && x - i >= 0 && y + i < N && board[(x - i)*N+(y + i)] == board[x*N+y]; i++)
        count++;
    return count == 5;
}

bool Board::winMove(int x, int y)
{
    return rowWinMove(x, y) || columnWinMove(x, y) || firstDiagWinMove(x, y) || secondDiagWinMove(x, y);
}

bool Board::draw()
{
    return movesCount == N * N;
}

bool Board::adjacent(int x, int y) 
{
    int isAdj = false;

    if (board[x*N+y] != EMPTY_SYMBOL)
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
        if (x+a[0] >= 0 && x+a[0] < N && y+a[1] >= 0 && y+a[1] < N) {
            if (isAdj) break;
            isAdj = board[(x+a[0])*N+(y+a[1])] != EMPTY_SYMBOL;
        }
    }

    return isAdj;

}

char Board::getValue(int x, int y)
{
    return board[x*N+y];
}

int Board::getMovesCount()
{
    return movesCount;
}

string Board::getBoard()
{
    string out = "";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            out += (
                board[i*N+j] == COMPUTER_SYMBOL ? 
                    '1' :
                    (board[i*N+j] == PLAYER_SYMBOL ? 
                        '2' :
                        '0'
                    )
            );
    return out;
}