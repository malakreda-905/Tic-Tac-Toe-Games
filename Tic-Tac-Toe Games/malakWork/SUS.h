#ifndef _SUS_H
#define _SUS_H

#include "../sourceClass/BoardGame_Classes.h"
#include <iomanip>
#include <vector>
using namespace std;
template <typename T>
class SUS_Board : public Board<T> {
public:
    SUS_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    int get_player_sequences(T player_symbol) const;
    T get_cell(int x, int y) const { return this->board[x][y]; }
    int get_moves() const { return this->n_moves; }
    bool is_valid_move(int x, int y) const;
    void undo_move(int x, int y);

private:
    struct Sequence {
        int startX, startY;
        int deltaX, deltaY;
        T owner;
    };
    vector<Sequence> completed_sequences;
    bool check_sequence(int startX, int startY, int deltaX, int deltaY, T last_symbol);
};

template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = ' ';
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool SUS_Board<T>::is_valid_move(int x, int y) const {
    return (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == ' ');
}

template <typename T>
void SUS_Board<T>::undo_move(int x, int y) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns) {
        this->board[x][y] = ' ';
        this->n_moves--;

        auto it = completed_sequences.begin();
        while (it != completed_sequences.end()) {
            if (it->startX <= x && x <= it->startX + 2 * it->deltaX &&
                it->startY <= y && y <= it->startY + 2 * it->deltaY) {
                it = completed_sequences.erase(it);
            } else {
                ++it;
            }
        }
    }
}

template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T symbol) {
    if (!is_valid_move(x, y)) {
        return false;
    }

    this->board[x][y] = symbol;
    this->n_moves++;

    for (int startX = 0; startX < this->rows; startX++) {
        for (int startY = 0; startY < this->columns; startY++) {
            check_sequence(startX, startY, 0, 1, symbol);
            check_sequence(startX, startY, 1, 0, symbol);
            check_sequence(startX, startY, 1, 1, symbol);
            check_sequence(startX, startY, 1, -1, symbol);
        }
    }

    return true;
}

template <typename T>
bool SUS_Board<T>::check_sequence(int startX, int startY, int deltaX, int deltaY, T last_symbol) {
    if (startX < 0 || startX + 2*deltaX >= this->rows ||
        startY < 0 || startY + 2*deltaY >= this->columns) {
        return false;
    }

    if (this->board[startX][startY] == 'S' &&
        this->board[startX + deltaX][startY + deltaY] == 'U' &&
        this->board[startX + 2*deltaX][startY + 2*deltaY] == 'S') {

        for (const auto& seq : completed_sequences) {
            if (seq.startX == startX && seq.startY == startY &&
                seq.deltaX == deltaX && seq.deltaY == deltaY) {
                return false;
            }
        }

        completed_sequences.push_back({startX, startY, deltaX, deltaY, last_symbol});
        return true;
    }
    return false;
}

template <typename T>
int SUS_Board<T>::get_player_sequences(T player_symbol) const {
    int count = 0;
    for (const auto& seq : completed_sequences) {
        if (seq.owner == player_symbol) {
            count++;
        }
    }
    return count;
}

template <typename T>
void SUS_Board<T>::display_board() {
    cout << "\nCurrent board state:\n\n";
    for (int i = 0; i < this->rows; i++) {
        cout << "  ";
        for (int j = 0; j < this->columns; j++) {
            cout << "+---------------";
        }
        cout << "+\n  ";
        for (int j = 0; j < this->columns; j++) {
            cout << "|  (" << i << "," << j << ")";
            if (this->board[i][j] != ' ') {
                cout << " " << this->board[i][j] << "   ";
            } else {
                cout << "     ";
            }
        }
        cout << "|\n";
    }
    cout << "  ";
    for (int j = 0; j < this->columns; j++) {
        cout << "+---------------";
    }
    cout << "+\n";

    cout << "\nCurrent SUS sequences - S Player: " << get_player_sequences('S')
         << ", U Player: " << get_player_sequences('U') << "\n";
}

template <typename T>
bool SUS_Board<T>::is_win() {
    return is_draw();
}

template <typename T>
bool SUS_Board<T>::is_draw() {
    return this->n_moves == this->rows * this->columns;
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_draw();
}

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int& x, int& y) override {
        cout << "\nPlayer " << this->name << " [" << this->symbol << "]: Enter coordinates (row, column): ";
        cin >> x >> y;
    }
};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T> {
public:
    SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int& x, int& y) override {
        SUS_Board<T>* board = dynamic_cast<SUS_Board<T>*>(this->boardPtr);
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (!board->is_valid_move(x, y));
    }
};

#endif