#ifndef TIC_TAC_TOE_GAME_H
#define TIC_TAC_TOE_GAME_H
#include "../sourceClass/BoardGame_Classes.h"
#pragma once

// ------____DEFINITIONS____------

template <typename T>
class Tic_Tac_Toe_Board : public Board<T>
{
public:
    Tic_Tac_Toe_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();

private:
};

template <typename T>
class Tic_Tac_Toe_Player : public Player<T>
{
public:
    Tic_Tac_Toe_Player(string name, T symbol);
    void getmove(int &x, int &y);

private:
};

template <typename T>
class Tic_Tac_Toe_Random_Player : public RandomPlayer<T>
{
public:
    Tic_Tac_Toe_Random_Player(T symbol);
    void getmove(int &x, int &y);

private:
};

// ------____IMPLEMENTATION____------
#include <iostream>
#include <iomanip>
#include <cctype>

template <typename T>
inline Tic_Tac_Toe_Board<T>::Tic_Tac_Toe_Board()
{
    this->rows = 3;
    this->board = new char *[this->rows]; // 3 rows
    this->columns = 1;
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
            this->board[i][j] = 0;
        this->columns += 2;
    }
    this->n_moves = 0;
}

template <typename T>
inline bool Tic_Tac_Toe_Board<T>::update_board(int x, int y, T symbol)
{
    // check validation
    if ((x < 0 || y < 0 || x >= this->rows) || (x == 0 && y != 0) || (x == 1 && (y > 2)) || (x == 2 && (y > 4)))
        return false;
    if (this->board[x][y] != 0 && symbol != 0)
        return false;
    if (symbol == 0)
    {
        this->n_moves--;
        this->board[x][y] = 0;
    }
    else
    {
        this->n_moves++;
        this->board[x][y] = symbol;
    }
    return true;
}

template <typename T>
inline void Tic_Tac_Toe_Board<T>::display_board()
{
    string current[3][5];
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < 2 * (i + 1) - 1; j++)
        {
            current[i][j] = '(' + to_string(i) + "," + to_string(j) + ')';
            if (this->board[i][j] != 0)
            {
                current[i][j] = "  ";
                current[i][j].push_back((this->board[i][j]));
                current[i][j] += "  ";
            }
        }
    }
    cout << "     |     |" + current[0][0] + "|     |     " << endl;
    cout << "-----|-----|-----|-----|-----|" << endl;
    cout << "     |" + current[1][0] + "|" + current[1][1] + "|" + current[1][2] + "|     " << endl;
    cout << "-----|-----|-----|-----|-----|" << endl;
    cout << current[2][0] + "|" + current[2][1] + "|" + current[2][2] + "|" + current[2][3] + "|" + current[2][4] << endl;
    cout << "_------------------------------_" << endl;
}

template <typename T>
inline bool Tic_Tac_Toe_Board<T>::is_win()
{
    // check diag
    if ((this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][0] && this->board[2][0] != 0) ||
        (this->board[0][0] == this->board[1][2] && this->board[1][2] == this->board[2][4] && this->board[2][4] != 0))
        return true;
    // check rows
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[2][2] != 0)
        return true;
    this->columns = 3;
    int i = 1;
    while (i < 3)
    {
        for (int j = 0; j < this->columns - 2; j++)
        {
            if (this->board[i][j] == this->board[i][j + 1] && this->board[i][j + 1] == this->board[i][j + 2] &&
                this->board[i][j + 1] != 0)
                return true;
        }
        i++;
        this->columns += 2;
    }
    return false;
}

template <typename T>
inline bool Tic_Tac_Toe_Board<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
inline bool Tic_Tac_Toe_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
inline Tic_Tac_Toe_Player<T>::Tic_Tac_Toe_Player(string name, T symbol) : Player<T>(name, symbol)
{
}

template <typename T>
inline void Tic_Tac_Toe_Player<T>::getmove(int &x, int &y)
{
    cout << this->name << " enter your move seprated by space ex.{1 2}, x => [0,2], y => [0,4]: ";
    cin >> x >> y;
}

template <typename T>
inline Tic_Tac_Toe_Random_Player<T>::Tic_Tac_Toe_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
inline void Tic_Tac_Toe_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % 3;
    // make y fit with x
    if (x == 0)
    {
        y = 0;
    }
    else if (x == 1)
    {
        y = rand() % 3;
    }
    else
    {
        y = rand() % 5;
    }
}

#endif