#ifndef ULTIMATETICTACTOE_H
#define ULTIMATETICTACTOE_H
#pragma once
#include <bits/stdc++.h>
#include "../sourceClass/BoardGame_Classes.h"
using namespace std;
// ________DEFINITION________

template <typename T>
class Ultimate_X_O_Board : public Board<T>
{
public:
  Ultimate_X_O_Board();
  bool update_board(int x, int y, T symbol);
  void display_board();
  bool is_win();
  bool is_draw();
  bool game_is_over();
  bool check_grid_winner(pair<int, int> grid, T symbol);
  bool check_grid_draw(pair<int, int> grid, T symbol);

private:
  char gridsWinner[3][3];
};

template <typename T>
class Ultimate_X_O_Player : public Player<T>
{

public:
  Ultimate_X_O_Player(string name, T symbol);
  void getmove(int &x, int &y);
};

template <typename T>
class Ultimate_X_O_Random_Player : public RandomPlayer<T>
{
  int grid;

public:
  Ultimate_X_O_Random_Player(T symbol);
  void getmove(int &x, int &y);
};

// ______IMPLEMENTATION______

template <typename T>
inline Ultimate_X_O_Board<T>::Ultimate_X_O_Board()
{
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      gridsWinner[i][j] = 0;
  this->rows = this->columns = 9;
  this->board = new char *[this->rows];
  for (int row = 0; row < this->rows; row++)
  {
    this->board[row] = new char[this->columns];
    for (int col = 0; col < this->columns; col++)
      this->board[row][col] = 0;
  }
  this->n_moves = 0;
}

template <typename T>
inline bool Ultimate_X_O_Board<T>::update_board(int x, int y, T symbol)
{
  if (x >= 9 || y >= 9 || x < 0 || y < 0)
    return false;
  if (this->gridsWinner[x / 3][y / 3] != 0)
    return false;
  if (this->board[x][y] != 0 && symbol != 0)
    return false;
  if (symbol == 0)
  {
    this->board[x][y] = 0;
  }
  else
  {
    this->board[x][y] = toupper(symbol);
  }
  pair<int, int> grid = {x / 3, y / 3};
  // check if the current grid is winner or not
  if (this->check_grid_winner(grid, symbol))
  {
    this->gridsWinner[x / 3][y / 3] = toupper(symbol);
    this->n_moves++;
  }
  else if (this->check_grid_draw(grid, symbol))
  {
    this->gridsWinner[x / 3][y / 3] = 'd';
    this->n_moves++;
  }
  return true;
}

template <typename T>
inline void Ultimate_X_O_Board<T>::display_board()
{
  cout << " _______+_______+_______   _______+_______+_______   _______+_______+_______" << endl;
  map<char, string> m;
  m['X'] = "   X   ", m['O'] = "   O   ", m['d'] = " DRAW  ";
  for (int row = 0; row < 9; row++)
  {
    cout << " ";
    for (int col = 0; col < 9; col++)
    {
      string curr = " (" + to_string(row) + "," + to_string(col) + ") ";
      if (this->board[row][col] != 0)
      {
        curr = "   ";
        curr.push_back(this->board[row][col]);
        curr += "   ";
      }
      if (this->gridsWinner[row / 3][col / 3] != 0)
        cout << m[this->gridsWinner[row / 3][col / 3]];
      else
        cout << curr;
      if (col != 2 && col != 5 && col != 8)
        cout << "|";
      else
        cout << "   ";
      if (col == 8)
        cout << endl;
    }
    if (row != 2 && row != 5 && row != 8)
      cout << " -------|-------|-------    ------|-------|-------    ------|-------|-------   " << endl;
    else
      cout << " _______________________   _______________________   _______________________ " << endl;
  }
      cout << "+___________________________________________________________________________+" << endl;
}

template <typename T>
inline bool Ultimate_X_O_Board<T>::is_win()
{
  // Check rows and columns
  for (int i = 0; i < 3; i++)
  {
    if ((this->gridsWinner[i][0] == this->gridsWinner[i][1] && this->gridsWinner[i][1] == this->gridsWinner[i][2] && this->gridsWinner[i][0] != 0) ||
        (this->gridsWinner[0][i] == this->gridsWinner[1][i] && this->gridsWinner[1][i] == this->gridsWinner[2][i] && this->gridsWinner[0][i] != 0))
    {
      return true;
    }
  }

  // Check diagonals
  if ((this->gridsWinner[0][0] == this->gridsWinner[1][1] && this->gridsWinner[1][1] == this->gridsWinner[2][2] && this->gridsWinner[0][0] != 0) ||
      (this->gridsWinner[0][2] == this->gridsWinner[1][1] && this->gridsWinner[1][1] == this->gridsWinner[2][0] && this->gridsWinner[0][2] != 0))
  {
    return true;
  }

  return false;
}

template <typename T>
inline bool Ultimate_X_O_Board<T>::is_draw()
{
  return (this->n_moves == 9 && !is_win());
}

template <typename T>
inline bool Ultimate_X_O_Board<T>::game_is_over()
{
  return is_win() || is_draw();
}

template <typename T>
inline bool Ultimate_X_O_Board<T>::check_grid_winner(pair<int, int> grid, T symbol)
{
  int startX = grid.first * 3, startY = grid.second * 3;
  // check diag
  if (this->board[startX][startY] == this->board[startX + 1][startY + 1] && this->board[startX + 1][startY + 1] == this->board[startX + 2][startY + 2] && this->board[startX][startY] != 0)
    return true;
  if (this->board[startX][startY + 2] == this->board[startX + 1][startY + 1] && this->board[startX + 2][startY] == this->board[startX][startY + 2] && this->board[startX][startY + 2] != 0)
    return true;
  // check rows
  for (int i = startX; i < startX + 3; i++)
  {
    if (this->board[i][startY] == this->board[i][startY + 1] && this->board[i][startY] == this->board[i][startY + 2] && this->board[i][startY] != 0)
      return true;
  }
  // check cols
  for (int i = startY; i < startY + 3; i++)
  {
    if (this->board[startX][i] == this->board[startX + 1][i] && this->board[startX][i] == this->board[startX + 2][i] && this->board[startX][i] != 0)
      return true;
  }
  return false;
}

template <typename T>
inline bool Ultimate_X_O_Board<T>::check_grid_draw(pair<int, int> grid, T symbol)
{
  int nMoves = 0;
  int startX = grid.first * 3, startY = grid.second * 3;
  for (int i = startX; i < startX + 3; i++)
  {
    for (int j = startY; j < startY + 3; j++)
    {
      nMoves += (this->board[i][j] != 0);
    }
  }
  return nMoves == 9 && !check_grid_winner(grid, symbol);
}

template <typename T>
inline Ultimate_X_O_Player<T>::Ultimate_X_O_Player(string name, T symbol) : Player<T>(name, symbol)
{
}

template <typename T>
inline void Ultimate_X_O_Player<T>::getmove(int &x, int &y)
{
  cout << "Player " + this->name + " Enter x & y seprated ex.{1 2}: ";
  cin >> x >> y;
}

template <typename T>
inline Ultimate_X_O_Random_Player<T>::Ultimate_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
  this->name = "Random computer player";
  this->dimension = 9;
  srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
inline void Ultimate_X_O_Random_Player<T>::getmove(int &x, int &y)
{
  x = rand() % this->dimension;
  y = rand() % this->dimension;
}

#endif