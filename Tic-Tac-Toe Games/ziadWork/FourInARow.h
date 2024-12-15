#ifndef FOURINAROW_H
#define FOURINAROW_H
#include <bits/stdc++.h>
#include "../sourceClass/BoardGame_Classes.h"
using namespace std;

template <typename T>
class FourInARow_Board : public Board<T>{
public:
    FourInARow_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    auto get_board(int x, int y); 
};

template <typename T>
class FourInARow_Player : public Player<T>
{
public:
    FourInARow_Player(string name, T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
class FourInARow_Random_Player : public RandomPlayer<T>
{
public:
    FourInARow_Random_Player(T symbol);
    void getmove(int &x, int &y);
};

template <typename T>
FourInARow_Board<T>::FourInARow_Board()
{
    this->rows = 6, this->columns = 7;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
auto FourInARow_Board<T>::get_board(int x, int y)
{
    return this->board[x][y];
}

template <typename T>
bool FourInARow_Board<T>::update_board(int x, int y, T mark)
{
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0))
    {//
        if (mark == 0)
        {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else
        {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

template <typename T>
void FourInARow_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            char curr = this->board[i][j];
            if (curr == 0)
            {
                cout << " (" << j << ")";
                cout << this->board[i][j] << " |";
            }
            else
            {
                cout << "  " << this->board[i][j] << "  " << "|";
            }
        }
        cout << "\n--------------------------------------------";
    }
    cout << endl;
}

template <typename T>
bool FourInARow_Board<T>::is_win()
{
    // rows
    for (int i = 0; i < this->rows; ++i)
    {
        for (int j = 0; j <= this->columns - 4; ++j)
        {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i][j + 1] && this->board[i][j] == this->board[i][j + 2] && this->board[i][j] == this->board[i][j + 3])
            {
                return true;
            }
        }
    }
    // columns
    for (int j = 0; j < this->columns; ++j)
    {
        for (int i = 0; i <= this->rows - 4; ++i)
        {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j] && this->board[i][j] == this->board[i + 2][j] && this->board[i][j] == this->board[i + 3][j])
            {
                return true;
            }
        }
    }
    // (+) slope
    for (int i = 0; i <= this->rows - 4; ++i)
    {
        for (int j = 0; j <= this->columns - 4; ++j)
        {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i + 1][j + 1] && this->board[i][j] == this->board[i + 2][j + 2] && this->board[i][j] == this->board[i + 3][j + 3])
            {
                return true;
            }
        }
    }
    // (-) slope
    for (int i = 3; i < this->rows; ++i)
    {
        for (int j = 0; j <= this->columns - 4; ++j)
        {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i - 1][j + 1] && this->board[i][j] == this->board[i - 2][j + 2] && this->board[i][j] == this->board[i - 3][j + 3])
            {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool FourInARow_Board<T>::is_draw()
{
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool FourInARow_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
FourInARow_Player<T>::FourInARow_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void FourInARow_Player<T>::getmove(int &x, int &y)
{
    cout << "\nPlease enter your move y in range {0,6}: ";
    cin >> y;
    x = 5; 
    auto *boardCopy = dynamic_cast<FourInARow_Board<T> *>(this->boardPtr);
    while (x >= 0 && boardCopy->get_board(x, y) != 0)
        x--;
    if (x < 0)
        cout << "this column is full, Please Choose another column.\n";
}

template <typename T>
FourInARow_Random_Player<T>::FourInARow_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->dimension = 7;
    string Symbol = "";
    Symbol += (char)symbol;
    this->name = "Random Computer Player ( " +Symbol + " )";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void FourInARow_Random_Player<T>::getmove(int &x, int &y)
{
    y = rand() % this->dimension;
    x = 5; 
    auto *boardCopy = dynamic_cast<FourInARow_Board<T> *>(this->boardPtr);
    while (x >= 0 && boardCopy->get_board(x, y) != 0)
        x--;
}

#endif
