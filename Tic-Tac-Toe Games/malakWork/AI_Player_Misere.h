#ifndef AIPLAYER_MISERE_H
#define AIPLAYER_MISERE_H

#include "../sourceClass/BoardGame_Classes.h"
#include "Misere_TicTacToe.h"
using namespace std;

template <typename T>
class X_O_MinMax_3x3X_Player : public Player<T> {
public:
    X_O_MinMax_3x3X_Player(T symbol);
    void getmove(int& x, int& y) override;

private:
    int calculateMinMax(T s, bool isMaximizing, int depth);
    pair<int, int> getBestMove();
};

// IMPLEMENTATION

#include <limits>
#include <algorithm>
using namespace std;

template <typename T>
X_O_MinMax_3x3X_Player<T>::X_O_MinMax_3x3X_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

template <typename T>
void X_O_MinMax_3x3X_Player<T>::getmove(int& x, int& y) {
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

template <typename T>
int X_O_MinMax_3x3X_Player<T>::calculateMinMax(T s, bool isMaximizing, int depth) {
    if (this->boardPtr->is_win()) {
        return isMaximizing ? 1 : -1;
    }
    else if (this->boardPtr->is_draw() || depth == 0) {
        return 0;
    }

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    T opponentSymbol = (s == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, s)) {
                int value = calculateMinMax(opponentSymbol, !isMaximizing, depth - 1);
                this->boardPtr->update_board(i, j, 0);

                if (isMaximizing) {
                    bestValue = max(bestValue, value);
                } else {
                    bestValue = min(bestValue, value);
                }
            }
        }
    }

    return bestValue;
}

template <typename T>
pair<int, int> X_O_MinMax_3x3X_Player<T>::getBestMove() {
    int bestValue = numeric_limits<int>::max();
    pair<int, int> bestMove = {-1, -1};
    T opponentSymbol = (this->symbol == 'X') ? 'O' : 'X';

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (this->boardPtr->update_board(i, j, this->symbol)) {
                int moveValue = calculateMinMax(opponentSymbol, true, 5);
                this->boardPtr->update_board(i, j, 0);

                if (moveValue < bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

#endif //AIPLAYER_MISERE_H