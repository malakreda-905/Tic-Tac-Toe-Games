#ifndef MINMAXWORDPLAYER_H
#define MINMAXWORDPLAYER_H

#include "../sourceClass/BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;
#pragma once

// _____DEFINITION_____

template <typename T>
class minMaxWordPlayer : public Player<T>
{
public:
    minMaxWordPlayer(T symbol);
    void getmove(int &x, int &y) override;

private:
    int calculateMinMax(bool isMaximizing);
    pair<int, int> getBestMove();
    vector<pair<int, int>> availableMoves;
};

// _____IMPELEMENTAION_____

template <typename T>
inline minMaxWordPlayer<T>::minMaxWordPlayer(T symbol) : Player<T>(symbol)
{
    this->name = "AI Player";
}
template <typename T>
inline void minMaxWordPlayer<T>::getmove(int &x, int &y)
{
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first, y = bestMove.second;
}
template <typename T>
inline int minMaxWordPlayer<T>::calculateMinMax(bool isMaximizing)
{
    if (this->boardPtr->is_win())
        return (isMaximizing ? -1 : 1);
    if (this->boardPtr->is_draw())
        return 0;
    int bestScore = (isMaximizing ? INT_MIN : INT_MAX);
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            for (char symb = 'A'; symb <= 'Z'; symb++)
            {
                if (this->boardPtr->update_board(row, col, symb))
                {
                    int score = calculateMinMax(!isMaximizing);
                    this->boardPtr->update_board(row, col, 0);
                    bestScore = (isMaximizing ? max(bestScore, score) : min(bestScore, score));
                }
            }
        }
    }
    return bestScore;
}
template <typename T>
inline std::pair<int, int> minMaxWordPlayer<T>::getBestMove()
{
    // check if this move is the winning move or not
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            for (char symb = 'A'; symb <= 'Z'; symb++)
            {
                if (this->boardPtr->update_board(row, col, symb))
                {
                    if (this->boardPtr->is_win())
                    {
                        this->boardPtr->update_board(row, col, 0);
                        this->symbol = symb;
                        return {row, col};
                    }
                    this->boardPtr->update_board(row, col, 0);
                }
            }
        }
    }
    pair<int, int> bestMove = {-1, -1};
    int bestScore = INT_MIN;
    // get the available moves
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            for (char a = 'A'; a <= 'Z'; a++)
            {
                if (this->boardPtr->update_board(row, col, a))
                {
                    int move = calculateMinMax(false);
                    this->boardPtr->update_board(row, col, 0);
                    if (move > bestScore)
                    {
                        bestScore = move;
                        bestMove = {row, col};
                    }
                }
            }
        }
    }
    return bestMove;
}
#endif