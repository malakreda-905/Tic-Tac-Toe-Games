
#ifndef NUMERICALTICTACTOE_H
#define NUMERICALTICTACTOE_H
#include <bits/stdc++.h>
#include "../sourceClass/BoardGame_Classes.h"
using namespace std;

map<int, int> used_numbers;

template <typename T>
class Numerical_Board : public Board<T>
{

public:
    Numerical_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class Numerical_Player : public Player<T>
{
public:
    Numerical_Player(string name, T symbol);
    void getmove(int &x, int &y);
    list<int> numSet;
};

template <typename T>
class Numerical_Random_Player : public RandomPlayer<T>
{
public:
    Numerical_Random_Player(T symbol);
    void getmove(int &x, int &y);
    list<int> numSet;
};

template <typename T>
Numerical_Board<T>::Numerical_Board()
{
    this->rows = this->columns = 3;
    this->board = new int *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++)
        {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Numerical_Board<T>::update_board(int x, int y, T symbol)
{
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) and (this->board[x][y] == 0))
    {
        this->n_moves++;
        this->board[x][y] = symbol;
        used_numbers[symbol] = 1;
        return true;
    }
    return false;
}

template <typename T>
void Numerical_Board<T>::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++)
        {
            int curr = this->board[i][j];
            if (curr == 0)
                cout << " (" << i << "," << j << ") |";
            else
                cout << "   " << this->board[i][j] << "  " << " |";
        }
        cout << "\n--------------------------";
    }
    cout << endl;
}

template <typename T>
bool Numerical_Board<T>::is_win()
{
    // Check rows and columns
    for (int i = 0; i < this->rows; i++)
    {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 && this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15 && this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0))
            return true;
    }
    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 && this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15 && this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0))
        return true;

    return false;
}

template <typename T>
bool Numerical_Board<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Numerical_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
Numerical_Player<T>::Numerical_Player(string name, T symbol) : Player<T>(name, symbol)
{//constructor
    if (symbol == 1)
        this->numSet = {1, 3, 5, 7, 9};
    else
        this->numSet = {2, 4, 6, 8};
}

template <typename T>
void Numerical_Player<T>::getmove(int &x, int &y)
{
    cout << "\nplayer " << this->name << " Please enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    cout << "(player 1 must enter odd number and player 2 even number)\nplease enter a number [1,9] : ";
    while (true)
    {
        cin >> this->symbol;
        bool found = used_numbers[this->symbol];
        bool valid = find(this->numSet.begin(), this->numSet.end(), this->symbol) != this->numSet.end(); // exist

        if (valid and !found)
            break;
        cout << "please enter a valid number :";
    }
}

template <typename T>
Numerical_Random_Player<T>::Numerical_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    string Symbol = (symbol == 1 ? "2" : "1");
    if (symbol == 1)
        this->numSet = {1, 3, 5, 7, 9};
    else
        this->numSet = {2, 4, 6, 8};
    this->dimension = 3;
    this->name = "Random Computer Player " + Symbol;
    srand(static_cast<unsigned int>(time(0))); 
}
template <typename T>
void Numerical_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    vector<int> validNum;
    for (int i : numSet)
    {
        if (used_numbers[i] == 0)
            validNum.push_back(i);
    }
    if (!validNum.empty())
    {
        this->symbol = validNum[rand() % validNum.size()];
    }
}

#endif
