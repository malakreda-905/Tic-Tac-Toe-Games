#ifndef AIPlayer5x5_H
#define AIPlayer5x5_H

#include "../sourceClass/BoardGame_Classes.h"
#include "5x5_TicTacToe.h"
#include <limits>
#include <algorithm>
#include <utility>

using namespace std;

template <typename T>
class X_O_5x5X_MinMax_Player : public Player<T> {
public:
    X_O_5x5X_MinMax_Player(T symbol);
    void getmove(int& x, int& y) override;

private:
    const int MAX_DEPTH = 3;
    TicTacToe5x5_Board<T>* getTicTacToeBoard() {
        return dynamic_cast<TicTacToe5x5_Board<T>*>(this->boardPtr);
    }
    int minimax(TicTacToe5x5_Board<T>* board, int depth, bool isMaximizing, int alpha, int beta);
    pair<int, int> findBestMove();
    bool isValidMove(int x, int y);
};

template <typename T>
X_O_5x5X_MinMax_Player<T>::X_O_5x5X_MinMax_Player(T symbol) : Player<T>(symbol) {
    this->name = "AI Player";
}

template <typename T>
void X_O_5x5X_MinMax_Player<T>::getmove(int& x, int& y) {
    pair<int, int> bestMove = findBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

template <typename T>
bool X_O_5x5X_MinMax_Player<T>::isValidMove(int x, int y) {
    T current_cell = getTicTacToeBoard()->get_cell(x, y);
    return current_cell == '.';
}

template <typename T>
int X_O_5x5X_MinMax_Player<T>::minimax(TicTacToe5x5_Board<T>* board, int depth, bool isMaximizing, int alpha, int beta) {
    if (depth == 0 || board->game_is_over()) {
        int x_sequences = board->count_x_sequences();
        int o_sequences = board->count_o_sequences();
        return (this->symbol == 'X') ? (x_sequences - o_sequences) : (o_sequences - x_sequences);
    }

    if (isMaximizing) {
        int maxEval = numeric_limits<int>::min();
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board->get_cell(i, j) == '.') {
                    TicTacToe5x5_Board<T>* newBoard = board->clone();
                    newBoard->update_board(i, j, this->symbol);
                    int eval = minimax(newBoard, depth - 1, false, alpha, beta);
                    delete newBoard;
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha)
                        return maxEval;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = numeric_limits<int>::max();
        T opponent_symbol = (this->symbol == 'X') ? 'O' : 'X';
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (board->get_cell(i, j) == '.') {
                    TicTacToe5x5_Board<T>* newBoard = board->clone();
                    newBoard->update_board(i, j, opponent_symbol);
                    int eval = minimax(newBoard, depth - 1, true, alpha, beta);
                    delete newBoard;
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha)
                        return minEval;
                }
            }
        }
        return minEval;
    }
}

template <typename T>
pair<int, int> X_O_5x5X_MinMax_Player<T>::findBestMove() {
    int bestVal = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};
    TicTacToe5x5_Board<T>* board = getTicTacToeBoard();

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (isValidMove(i, j)) {
                bestMove = {i, j};
                i = j = 5;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (isValidMove(i, j)) {
                TicTacToe5x5_Board<T>* newBoard = board->clone();
                newBoard->update_board(i, j, this->symbol);
                int moveVal = minimax(newBoard, MAX_DEPTH - 1, false,
                                      numeric_limits<int>::min(),
                                      numeric_limits<int>::max());
                delete newBoard;

                if (moveVal > bestVal) {
                    bestMove = {i, j};
                    bestVal = moveVal;
                }
            }
        }
    }

    return bestMove;
}

#endif //AIPlayer5x5_H