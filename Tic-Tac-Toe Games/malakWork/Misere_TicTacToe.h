#ifndef MISERE_TICTACTOE_H
#define MISERE_TICTACTOE_H

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include "../sourceClass/BoardGame_Classes.h"
template <typename T>
class X_O_Board : public Board<T> {
public:
    X_O_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    bool has_three_in_row(T symbol);
    T get_loser();
private:
    T loser;
};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T> {
public:
    X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

// Implementation

template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

template <typename T>
void X_O_Board<T>::display_board() {
    cout << "\nMisere Tic Tac Toe (Get 3 in a row to LOSE!)\n";
    cout << "--------------------------------------------\n";
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

template <typename T>
bool X_O_Board<T>::has_three_in_row(T symbol) {
    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] == symbol && this->board[i][1] == symbol && this->board[i][2] == symbol) {
            return true;
        }
    }

    for (int i = 0; i < this->columns; i++) {
        if (this->board[0][i] == symbol && this->board[1][i] == symbol && this->board[2][i] == symbol) {
            return true;
        }
    }

    if ((this->board[0][0] == symbol && this->board[1][1] == symbol && this->board[2][2] == symbol) ||
        (this->board[0][2] == symbol && this->board[1][1] == symbol && this->board[2][0] == symbol)) {
        return true;
    }

    return false;
}

template <typename T>
bool X_O_Board<T>::is_win() {
    if (has_three_in_row('X')) {
        loser = 'X';
        return true;
    }
    if (has_three_in_row('O')) {
        loser = 'O';
        return true;
    }
    return false;
}

template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return (is_win() || is_draw());
}

template <typename T>
T X_O_Board<T>::get_loser() {
    return loser;
}

template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move (x y): ";
    cin >> x >> y;
}

template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 3;
    y = rand() % 3;
}

#endif //MISERE_TICTACTOE_H