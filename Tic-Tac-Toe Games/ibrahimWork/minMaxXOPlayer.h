#ifndef MINMAXXOPLAYER_H
#define MINMAXXOPLAYER_H
#include "../sourceClass/BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;
#pragma once

// _____DEFINITION_____

template <typename T>
class minMaxXOPlayer : public Player<T>
{
public:
    minMaxXOPlayer(T symbol);

    void getmove(int &x, int &y) override;

private:
    int calculateMinMax(T s, bool isMaximizing);
    std::pair<int, int> getBestMove();
};
// _____IMPELEMENTAION_____

template <typename T>
inline minMaxXOPlayer<T>::minMaxXOPlayer(T symbol): Player<T>(symbol)
{
    this->name = "AI Player";
}

template <typename T>
inline void minMaxXOPlayer<T>::getmove(int &x, int &y)
{
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first, y = bestMove.second;
}

template <typename T>
inline int minMaxXOPlayer<T>::calculateMinMax(T s, bool isMaximizing)
{
    if (this->boardPtr->is_win())
        return (isMaximizing ? -1 : 1);
    if (this->boardPtr->is_draw())
        return 0;
    T oppo = (s == 'X' ? 'O' : 'X');
    int bestScore = (isMaximizing ? INT_MIN : INT_MAX);
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < (2 * row + 1); col++)
        {
            if (this->boardPtr->update_board(row, col, oppo))
            {
                int score = calculateMinMax(oppo, !isMaximizing);
                this->boardPtr->update_board(row, col, 0);
                bestScore = (isMaximizing ? max(bestScore, score) : min(bestScore, score));
            }
        }
    }
    return bestScore;
}

template <typename T>
inline pair<int, int> minMaxXOPlayer<T>::getBestMove()
{
    pair<int, int> bestMove = {-1, -1};
    int bestScore = INT_MIN;
    T oppo = (this->symbol == 'X' ? 'O' : 'X');
    // check if this move is the winning move for me or not
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < (2 * row + 1); col++)
        {
            if (this->boardPtr->update_board(row, col, this->symbol))
            {
                if (this->boardPtr->is_win())
                {
                    this->boardPtr->update_board(row, col, 0);
                    return {row, col};
                }
                this->boardPtr->update_board(row, col, 0);
            }
        }
    }
    // check if the next move is the winning move for the oppo
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < (2 * row + 1); col++)
        {
            if (this->boardPtr->update_board(row, col, oppo))
            {
                if (this->boardPtr->is_win())
                {
                    this->boardPtr->update_board(row, col, 0);
                    return {row, col};
                }
                this->boardPtr->update_board(row, col, 0);
            }
        }
    }
    // get the best move
    for (int row = 0; row <3; row++)
    {
        for (int col = 0; col < (2 * row + 1); col++)
        {
            if (this->boardPtr->update_board(row, col, this->symbol))
            {
                int move = calculateMinMax(this->symbol, false);
                this->boardPtr->update_board(row, col, 0);
                if (move > bestScore)
                {
                    bestScore = move;
                    bestMove = {row, col};
                }
            }
        }
    }
    return bestMove;
}

#endif