#ifndef TIC_TAC_TOE_WORD_H
#define TIC_TAC_TOE_WORD_H

#include "../sourceClass/BoardGame_Classes.h"
#include <bits/stdc++.h>
using namespace std;
#pragma once
// ------____DEFINITIONS____------

template <typename T>
class Tic_Tac_Toe_Word_Board : public Board<T>
{
public:
    Tic_Tac_Toe_Word_Board();
    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
    vector<char> get_valid_symbols(int row, int col);
    string get_row_string(int row);
    string get_col_string(int col);                         //
    bool can_form_word(string line, int indx, string word); //

private:
    map<string, bool> dictionary;
};

template <typename T>
class Tic_Tac_Toe_Word_Player : public Player<T>
{
public:
    Tic_Tac_Toe_Word_Player(string name, T symbol);
    void getmove(int &x, int &y);

private:
};

template <typename T>
class Tic_Tac_Toe_Word_Random_Player : public RandomPlayer<T>
{
public:
    Tic_Tac_Toe_Word_Random_Player(T symbol);
    void getmove(int &x, int &y);

private:
};

// ------____IMPLEMENTATION____------

template <typename T>
inline Tic_Tac_Toe_Word_Board<T>::Tic_Tac_Toe_Word_Board()
{
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++)
            this->board[i][j] = 0;
    }
    this->n_moves = 0;
    string word;
    ifstream dic("dic.txt");
    while (getline(dic, word))
        dictionary[word] = true;
    if (dic.is_open())
        dic.close();
}

template <typename T>
inline bool Tic_Tac_Toe_Word_Board<T>::update_board(int x, int y, T symbol)
{
    symbol = toupper(symbol);
    if (x < 0 || y < 0 || x >= this->rows || y >= this->columns)
        return false;
    if (symbol < 'A' || symbol > 'Z')
        if (symbol != 0)
            return false;
    if (this->board[x][y] != 0)
        if (symbol != 0)
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
inline void Tic_Tac_Toe_Word_Board<T>::display_board()
{
    string current[3][3];
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
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
    cout << "+-----------------------------+" << endl;
    cout << "" + current[0][0] + " | " + current[0][1] + " | " + current[0][2] + " |" << endl;
    cout << "-----------------------" << endl;
    cout << "" + current[1][0] + " | " + current[1][1] + " | " + current[1][2] + " |" << endl;
    cout << "-----------------------" << endl;
    cout << "" + current[2][0] + " | " + current[2][1] + " | " + current[2][2] + " |" << endl;
    cout << "_---------------------_" << endl;
    cout << "+-----------------------------+" << endl;
}

template <typename T>
inline bool Tic_Tac_Toe_Word_Board<T>::is_win()
{
    // check diag
    string s1 = string() + this->board[0][0] + this->board[1][1] + this->board[2][2], s2 = string() + this->board[0][2] + this->board[1][1] + this->board[2][0];
    if (dictionary[s1] || dictionary[s2])
        return true;
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    if (dictionary[s1] || dictionary[s2])
        return true;
    // check col & rows
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns - 2; j++)
        {
            // check col
            s1 = string() + this->board[i][j] + this->board[i][j + 1] + this->board[i][j + 2];
            // check rows
            s2 = string() + this->board[j][i] + this->board[j + 1][i] + this->board[j + 2][i];
            if (dictionary[s1])
                return true;
            if (dictionary[s2])
                return true;
            reverse(s1.begin(), s1.end());
            reverse(s2.begin(), s2.end());
            if (dictionary[s1])
                return true;
            if (dictionary[s2])
                return true;
        }
    }
    return false;
}

template <typename T>
inline bool Tic_Tac_Toe_Word_Board<T>::is_draw()
{
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
inline bool Tic_Tac_Toe_Word_Board<T>::game_is_over()
{
    return is_win() || is_draw();
}

template <typename T>
inline vector<char> Tic_Tac_Toe_Word_Board<T>::get_valid_symbols(int row, int col)
{
    {
        std::vector<char> validSymbols;

        if (this->board[row][col] != 0) // If the cell is already occupied
            return validSymbols;

        std::unordered_set<char> possibleLetters;

        // Horizontal word check
        std::string horizontal = get_row_string(row);
        for (const std::string &word : this->dictionary)
        {
            if (word.size() == 3 && can_form_word(horizontal, col, word))
            {
                possibleLetters.insert(word[col]);
            }
        }

        // Vertical word check
        std::string vertical = get_col_string(col);
        for (const std::string &word : this->dictionary)
        {
            if (word.size() == 3 && can_form_word(vertical, row, word))
            {
                possibleLetters.insert(word[row]);
            }
        }

        // Diagonal word checks
        std::string mainDiagonal = string() + this->board[0][0] + this->board[1][1] + this->board[2][2];
        std::string antiDiagonal = string() + this->board[0][2] + this->board[1][1] + this->board[2][0];
        for (const std::string &word : this->dictionary)
        {
            if (word.size() == 3)
            {
                if (can_form_word(mainDiagonal, row, word))
                    possibleLetters.insert(word[row]);

                if (can_form_word(antiDiagonal, row, word))
                    possibleLetters.insert(word[row]);
            }
        }

        validSymbols.assign(possibleLetters.begin(), possibleLetters.end());
        return validSymbols;
    }
}

template <typename T>
inline string Tic_Tac_Toe_Word_Board<T>::get_row_string(int row)
{
    std::string rowString;
    for (int col = 0; col < 3; col++)
    {
        rowString += (this->board[row][col] == 0 ? ' ' : this->board[row][col]);
    }
    return rowString;
}

template <typename T>
inline string Tic_Tac_Toe_Word_Board<T>::get_col_string(int col)
{
    std::string colString;
    for (int row = 0; row < 3; row++)
    {
        colString += (this->board[row][col] == 0 ? ' ' : this->board[row][col]);
    }
    return colString;
}

template <typename T>
inline bool Tic_Tac_Toe_Word_Board<T>::can_form_word(string line, int indx, string word)
{
    for (int i = 0; i < 3; i++)
    {
        if (i == indx)
            continue;

        if (line[i] != ' ' && line[i] != word[i])
            return false;
    }
    return true;
}

template <typename T>
inline Tic_Tac_Toe_Word_Player<T>::Tic_Tac_Toe_Word_Player(string name, T symbol) : Player<T>(name, symbol)
{
}

template <typename T>
inline void Tic_Tac_Toe_Word_Player<T>::getmove(int &x, int &y)
{
    cout << "Player " << this->name << " turn" << endl;
    cout << "Enter x & y & charcter ex.{0 1 C}, x & y => [0, 3]: ";
    cin >> x >> y >> this->symbol;
}

template <typename T>
inline Tic_Tac_Toe_Word_Random_Player<T>::Tic_Tac_Toe_Word_Random_Player(T symbol) : RandomPlayer<T>(symbol)
{
    this->name = "Random Computer Player";
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
inline void Tic_Tac_Toe_Word_Random_Player<T>::getmove(int &x, int &y)
{
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    this->symbol = 'A' + rand() % 26;
}

#endif