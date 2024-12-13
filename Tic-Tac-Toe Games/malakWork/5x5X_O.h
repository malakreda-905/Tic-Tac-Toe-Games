#ifndef TICTACTOE_5X5_H
#define TICTACTOE_5X5_H

#include "../sourceClass/BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>

using namespace std;

template <typename T>
class TicTacToe5x5_Board : public Board<T> {
public:
    TicTacToe5x5_Board();
    bool update_board(int x, int y, T symbol);
    T get_cell(int x, int y);
    void display_board();
    void reset_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    int count_x_sequences();
    int count_o_sequences();
    TicTacToe5x5_Board<T>* clone() const;
};

template <typename T>
class TicTacToe5x5_Player : public Player<T> {
public:
    TicTacToe5x5_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class TicTacToe5x5_Random_Player : public RandomPlayer<T> {
public:
    TicTacToe5x5_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

// Implementation

template <typename T>
TicTacToe5x5_Board<T>::TicTacToe5x5_Board() {
    this->rows = this->columns = 5;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '.';
        }
    }
    this->n_moves = 0;
}

template <typename T>
T TicTacToe5x5_Board<T>::get_cell(int x, int y) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
        return this->board[x][y];
    }
    return '.';  // Return empty cell for invalid coordinates
}

template <typename T>
TicTacToe5x5_Board<T>* TicTacToe5x5_Board<T>::clone() const {
    TicTacToe5x5_Board<T>* copy = new TicTacToe5x5_Board<T>();
    copy->n_moves = this->n_moves;

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            copy->board[i][j] = this->board[i][j];
        }
    }
    return copy;
}

template <typename T>
bool TicTacToe5x5_Board<T>::update_board(int x, int y, T symbol) {
    // Only allow valid moves within bounds and to empty cells
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == '.') {
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void TicTacToe5x5_Board<T>::display_board() {
    cout << "\n  ";
    for (int i = 0; i < this->columns; i++) {
        cout << i << " ";
    }
    cout << "\n";

    for (int i = 0; i < this->rows; i++) {
        cout << i << " ";
        for (int j = 0; j < this->columns; j++) {
            cout << this->board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

template <typename T>
int TicTacToe5x5_Board<T>::count_x_sequences() {
    int x_sequences = 0;

    // Horizontal
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= 2; j++) {
            if (this->board[i][j] == 'X' &&
                this->board[i][j + 1] == 'X' &&
                this->board[i][j + 2] == 'X') {
                x_sequences++;
            }
        }
    }

    // Vertical
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i <= 2; i++) {
            if (this->board[i][j] == 'X' &&
                this->board[i + 1][j] == 'X' &&
                this->board[i + 2][j] == 'X') {
                x_sequences++;
            }
        }
    }

    // Diagonal (top-left to bottom-right)
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            if (this->board[i][j] == 'X' &&
                this->board[i + 1][j + 1] == 'X' &&
                this->board[i + 2][j + 2] == 'X') {
                x_sequences++;
            }
        }
    }

    // Diagonal  (top-right to bottom-left)
    for (int i = 0; i <= 2; i++) {
        for (int j = 4; j >= 2; j--) {
            if (this->board[i][j] == 'X' &&
                this->board[i + 1][j - 1] == 'X' &&
                this->board[i + 2][j - 2] == 'X') {
                x_sequences++;
            }
        }
    }

    return x_sequences;
}

template <typename T>
int TicTacToe5x5_Board<T>::count_o_sequences() {
    int o_sequences = 0;

    // Horizontal
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= 2; j++) {
            if (this->board[i][j] == 'O' &&
                this->board[i][j + 1] == 'O' &&
                this->board[i][j + 2] == 'O') {
                o_sequences++;
            }
        }
    }

    // Vertical
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i <= 2; i++) {
            if (this->board[i][j] == 'O' &&
                this->board[i + 1][j] == 'O' &&
                this->board[i + 2][j] == 'O') {
                o_sequences++;
            }
        }
    }

    // Diagonal  (top-left to bottom-right)
    for (int i = 0; i <= 2; i++) {
        for (int j = 0; j <= 2; j++) {
            if (this->board[i][j] == 'O' &&
                this->board[i + 1][j + 1] == 'O' &&
                this->board[i + 2][j + 2] == 'O') {
                o_sequences++;
            }
        }
    }

    // Diagonal  (top-right to bottom-left)
    for (int i = 0; i <= 2; i++) {
        for (int j = 4; j >= 2; j--) {
            if (this->board[i][j] == 'O' &&
                this->board[i + 1][j - 1] == 'O' &&
                this->board[i + 2][j - 2] == 'O') {
                o_sequences++;
            }
        }
    }

    return o_sequences;
}

template <typename T>
bool TicTacToe5x5_Board<T>::is_win() {
    // Game continues until board is full
    return false;
}

template <typename T>
bool TicTacToe5x5_Board<T>::is_draw() {
    // Game is a draw when board is full (24 moves)
    return this->n_moves == 24;
}

template <typename T>
bool TicTacToe5x5_Board<T>::game_is_over() {
    // Game is over when board is full (24 moves)
    return this->n_moves == 24;
}

template <typename T>
void TicTacToe5x5_Board<T>::reset_board() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = '.';
        }
    }
    this->n_moves = 0;
}

template <typename T>
TicTacToe5x5_Player<T>::TicTacToe5x5_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void TicTacToe5x5_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlayer " << this->name << " enter your move (row column): ";
    cin >> x >> y;
}

template <typename T>
TicTacToe5x5_Random_Player<T>::TicTacToe5x5_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

template <typename T>
void TicTacToe5x5_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % 5;
    y = rand() % 5;
}

#endif // TICTACTOE_5X5_H