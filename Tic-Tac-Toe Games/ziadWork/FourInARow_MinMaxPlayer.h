#ifndef FOURINAROW_MINMAXPLAYER_H
#define FOURINAROW_MINMAXPLAYER_H
#include <bits/stdc++.h>
#include "../sourceClass/BoardGame_Classes.h"
using namespace std;

template <typename T>
class FourInARow_MinMax_Player : public Player<T>
{
private:
    int calculateMinMax(T currentSymbol, bool isMaximizing, int depth, int maxDepth, int alpha, int beta);
    pair<int, int> getBestMove();
    int positionScore(T symbol);
    int evaluateScore(int row, int col, int dr, int dc, T symbol);

public:
    FourInARow_MinMax_Player(T symbol);
    void getmove(int &x, int &y) override;
};

template <typename T>
FourInARow_MinMax_Player<T>::FourInARow_MinMax_Player(T symbol) : Player<T>(symbol)
{
    string Symbol = "";
    Symbol += (char)symbol;
    this->name = "AI Player ( " + Symbol + " )";
}
template <typename T>
void FourInARow_MinMax_Player<T>::getmove(int &x, int &y)
{
    pair<int, int> bestMove = getBestMove();
    x = bestMove.first;
    y = bestMove.second;
}

template <typename T>
int FourInARow_MinMax_Player<T>::evaluateScore(int row, int col, int dr, int dc, T symbol)
{
    int count = 0, rows = 6, cols = 7;
    for (int i = 0; i < 4; ++i)
    {
        int nr = row + i * dr, nc = col + i * dc;
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols)
        {
            if (this->boardPtr->update_board(nr, nc, symbol))
            {
                count++;
                this->boardPtr->update_board(nr, nc, 0); // Undo any accidental updates
            }
        }
    }
    if (count == 4)
        return 1000;
    else if (count == 3)
        return 10;
    else if (count == 2)
        return 1;
    else
        return 0;
}

template <typename T>
int FourInARow_MinMax_Player<T>::positionScore(T symbol)
{
    int score = 0, rows = 6, cols = 7;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            score += evaluateScore(i, j, 1, -1, symbol); // Diagonal
            score += evaluateScore(i, j, 0, 1, symbol);  // Horizontal
            score += evaluateScore(i, j, 1, 1, symbol);  // Diagonal
            score += evaluateScore(i, j, 1, 0, symbol);  // Vertical
        }
    }
    return score;
}

template <typename T>
int FourInARow_MinMax_Player<T>::calculateMinMax(T currentSymbol, bool isMaximizing, int depth, int maxDepth, int alpha, int beta)
{ // Minimax algorithm with Alpha-Beta Pruning
    if (this->boardPtr->is_win())
        return isMaximizing ? -1000 : 1000;
    if (this->boardPtr->is_draw())
        return 0;
    if (depth >= maxDepth)
        return positionScore(currentSymbol);

    int bestValue = isMaximizing ? numeric_limits<int>::min() : numeric_limits<int>::max();
    T opponentSymbol = (currentSymbol == 'X') ? 'O' : 'X';

    for (int col = 0; col < 7; ++col)
    {
        for (int row = 5; row >= 0; --row)
        {
            if (this->boardPtr->update_board(row, col, currentSymbol))
            {
                int score = calculateMinMax(opponentSymbol, !isMaximizing, depth + 1, maxDepth, alpha, beta);
                this->boardPtr->update_board(row, col, 0); // Undo move
                if (isMaximizing)
                    bestValue = max(bestValue, score), alpha = max(alpha, bestValue);
                else
                    bestValue = min(bestValue, score), beta = min(beta, bestValue);

                if (beta <= alpha)
                    break;
                break;
            }
        }
    }
    return bestValue;
}
template <typename T>
pair<int, int> FourInARow_MinMax_Player<T>::getBestMove()
{
    int bestValue = numeric_limits<int>::min(), maxDepth = 5;
    pair<int, int> bestMove = {-1, -1};
    for (int col = 0; col < 7; ++col)
    {
        for (int row = 5; row >= 0; --row)
        {
            if (this->boardPtr->update_board(row, col, this->symbol))
            {
                int moveValue = calculateMinMax(this->symbol, false, 0, maxDepth, numeric_limits<int>::min(), numeric_limits<int>::max());
                this->boardPtr->update_board(row, col, 0); // Undo the move
                if (moveValue > bestValue)
                    bestMove = {row, col}, bestValue = moveValue;
                break; // Once a optimal row is found, no need to check higher rows
            }
        }
    }
    return bestMove;
}

#endif
