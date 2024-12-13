#include <bits/stdc++.h>
// ___Ibrahim Work___
#include "ibrahimWork/Tic_Tac_Toe_Game.h"
#include "ibrahimWork/Tic_Tac_Toe_Word.h"
#include "ibrahimWork/minMaxWordPlayer.h"
#include "ibrahimWork/minMaxXOPlayer.h"
// ___Malak Work___
#include "malakWork/3x3X_O.h"
#include "malakWork/5x5X_O.h"
#include "malakWork/MinMaxPlayer3x3X.h"
#include "malakWork/MinMaxPlayer5x5X.h"
#include "malakWork/SUS.h"
// ___Ziad Work___
#include "ziadWork/FourInARow.h"
#include "ziadWork/FourInARow_MinMaxPlayer.h"
#include "ziadWork/NumericalTicTacToe.h"
#include "ziadWork/ultimateTicTacToe.h"
using namespace std;
int main()
{
  Player<char> *players[2];
  Player<int> *playersNumericalGame[2];
  Board<char> *board;
  Board<int> *boardNumericalGame;
  string player1XName, player2XName;
  char choiceGame;
  map<char, string> welcome;
  vector<string> gameNames = {"0- Pyramic Tic-Tac-Toe", "1- Four-in-a-row", "2- 5 x 5 Tic Tac Toe", "3- Word Tic-tac-toe",
                              "4- Numerical Tic-Tac-Toe", "5- Misere Tic Tac Toe", "6- Ultimate Tic Tac Toe", "7- SUS"};
  for (int i = 0; i < 8; i++) // set welcome map
    welcome[i + '0'] = "Welcome to " + gameNames[i].substr(3) + " Game";
  while (true)
  {
    used_numbers.clear();
    cout << "Choose a game from the following list:\n";
    for (auto &gameName : gameNames) // display all game name
      cout << gameName << endl;
    cout << "8- Exit" << endl;
    cout << "Enter choice from 0 -> 9: ";
    cin >> choiceGame;
    while (choiceGame < '0' || choiceGame > '8') // get valid choice
    {
      cout << "Enter choice from 0 -> 9: ";
      cin >> choiceGame;
    }
    if (choiceGame == '8')
      break;
    // print welcome message
    cout << welcome[choiceGame] << endl;
    // get player name
    cout << "Enter Player1 X name: ";
    cin >> player1XName;
    cout << "Choose Player1 X type:\n";
    cout << "1- Human\n";
    cout << "2- Random Computer\n";
    if (choiceGame != '6' && choiceGame != '7')
    {
      cout << "3- Smart AI\n";
      cout << "Enter choice from {1,3}: ";
    }
    else
      cout << "Enter choice from {1,2}: ";
    string choicePlayer1;
    while (true)
    {
      cin >> choicePlayer1;
      if (choicePlayer1 == "1" || choicePlayer1 == "2")
        break;
      if ((choiceGame != '6' && choiceGame != '7') && choicePlayer1 == "3")
        break;
      cout << "Enter choice: ";
    }
    cout << "Enter Player2 X name: ";
    cin >> player2XName;
    cout << "Choose Player2 X type:\n";
    cout << "1- Human\n";
    cout << "2- Random Computer\n";
    if (choiceGame != '6' && choiceGame != '7')
    {
      cout << "3- Smart AI\n";
      cout << "Enter choice from {1,3}: ";
    }
    else
      cout << "Enter choice from {1,2}: ";
    string choicePlayer2;
    while (true)
    {
      cin >> choicePlayer2;
      if (choicePlayer2 == "1" || choicePlayer2 == "2")
        break;
      if ((choiceGame != '6' && choiceGame != '7') && choicePlayer2 == "3")
        break;
      cout << "Enter choice: ";
    }
    // use the power of polymorphism here => set the board and players as game choice 
    switch (choiceGame)
    {
    case '0':
      board = new Tic_Tac_Toe_Board<char>();
      if (choicePlayer1 == "1")
        players[0] = new Tic_Tac_Toe_Player<char>(player1XName, 'X');
      else if (choicePlayer1 == "2")
        players[0] = new Tic_Tac_Toe_Random_Player<char>('X');
      else if (choicePlayer1 == "3")
        players[0] = new minMaxXOPlayer<char>('X');
      if (choicePlayer2 == "1")
        players[1] = new Tic_Tac_Toe_Player<char>(player2XName, 'O');
      else if (choicePlayer2 == "2")
        players[1] = new Tic_Tac_Toe_Random_Player<char>('O');
      else if (choicePlayer2 == "3")
        players[1] = new minMaxXOPlayer<char>('O');
      players[0]->setBoard(board);
      players[1]->setBoard(board);
      break;
    case '1':
      board = new FourInARow_Board<char>();
      if (choicePlayer1 == "1")
        players[0] = new FourInARow_Player<char>(player1XName, 'X');
      else if (choicePlayer1 == "2")
        players[0] = new FourInARow_Random_Player<char>('X');
      else if (choicePlayer1 == "3")
        players[0] = new FourInARow_MinMax_Player<char>('X');
      if (choicePlayer2 == "1")
        players[1] = new FourInARow_Player<char>(player2XName, 'O');
      else if (choicePlayer2 == "2")
        players[1] = new FourInARow_Random_Player<char>('O');
      else if (choicePlayer2 == "3")
        players[1] = new FourInARow_MinMax_Player<char>('O');
      players[0]->setBoard(board);
      players[1]->setBoard(board);
      break;
    case '2':
      board = new TicTacToe5x5_Board<char>();
      if (choicePlayer1 == "1")
        players[0] = new TicTacToe5x5_Player<char>(player1XName, 'X');
      else if (choicePlayer1 == "2")
        players[0] = new TicTacToe5x5_Random_Player<char>('X');
      else if (choicePlayer1 == "3")
        players[0] = new X_O_5x5X_MinMax_Player<char>('X');
      if (choicePlayer2 == "1")
        players[1] = new TicTacToe5x5_Player<char>(player2XName, 'O');
      else if (choicePlayer2 == "2")
        players[1] = new TicTacToe5x5_Random_Player<char>('O');
      else if (choicePlayer2 == "3")
        players[1] = new X_O_5x5X_MinMax_Player<char>('O');
      players[0]->setBoard(board);
      players[1]->setBoard(board);
      break;
    case '3':
      board = new Tic_Tac_Toe_Word_Board<char>();
      if (choicePlayer1 == "1")
        players[0] = new Tic_Tac_Toe_Word_Player<char>(player1XName, 'X');
      else if (choicePlayer1 == "2")
        players[0] = new Tic_Tac_Toe_Word_Random_Player<char>('X');
      else if (choicePlayer1 == "3")
        players[0] = new minMaxWordPlayer<char>('X');
      if (choicePlayer2 == "1")
        players[1] = new Tic_Tac_Toe_Word_Player<char>(player2XName, 'O');
      else if (choicePlayer2 == "2")
        players[1] = new Tic_Tac_Toe_Word_Random_Player<char>('O');
      else if (choicePlayer2 == "3")
        players[1] = new minMaxWordPlayer<char>('O');
      players[0]->setBoard(board);
      players[1]->setBoard(board);
      break;
    case '4':
      boardNumericalGame = new Numerical_Board<int>();
      if (choicePlayer1 == "1")
        playersNumericalGame[0] = new Numerical_Player<int>(player1XName, 1);
      else if (choicePlayer1 == "2")
        playersNumericalGame[0] = new Numerical_Random_Player<int>(1);
      // else if (choicePlayer1 == "3")
      //   playersNumericalGame[0] = new <int>('X');
      if (choicePlayer2 == "1")
        playersNumericalGame[1] = new Numerical_Player<int>(player2XName, 2);
      else if (choicePlayer2 == "2")
        playersNumericalGame[1] = new Numerical_Random_Player<int>(2);
      // else if (choicePlayer2 == "3"){
      //   playersNumericalGame[1] = new <int>('O'); }
      playersNumericalGame[0]->setBoard(boardNumericalGame);
      playersNumericalGame[1]->setBoard(boardNumericalGame);
      break;
    case '5':
      board = new X_O_Board<char>();
      if (choicePlayer1 == "1")
        players[0] = new X_O_Player<char>(player1XName, 'X');
      else if (choicePlayer1 == "2")
        players[0] = new X_O_Random_Player<char>('X');
      else if (choicePlayer1 == "3")
        players[0] = new X_O_MinMax_3x3X_Player<char>('X');
      if (choicePlayer2 == "1")
        players[1] = new X_O_Player<char>(player2XName, 'O');
      else if (choicePlayer2 == "2")
        players[1] = new X_O_Random_Player<char>('O');
      else if (choicePlayer2 == "3")
        players[1] = new X_O_MinMax_3x3X_Player<char>('O');
      players[0]->setBoard(board);
      players[1]->setBoard(board);
      break;
    case '6':
      board = new Ultimate_X_O_Board<char>();
      if (choicePlayer1 == "1")
        players[0] = new Ultimate_X_O_Player<char>(player1XName, 'X');
      else if (choicePlayer1 == "2")
        players[0] = new Ultimate_X_O_Random_Player<char>('X');
      if (choicePlayer2 == "1")
        players[1] = new Ultimate_X_O_Player<char>(player2XName, 'O');
      else if (choicePlayer2 == "2")
        players[1] = new Ultimate_X_O_Random_Player<char>('O');
      break;
    case '7':
      board = new SUS_Board<char>();
      if (choicePlayer1 == "1")
        players[0] = new SUS_Player<char>(player1XName, 'S');
      else if (choicePlayer1 == "2")
        players[0] = new SUS_Random_Player<char>('S');
      if (choicePlayer2 == "1")
        players[1] = new SUS_Player<char>(player2XName, 'U');
      else if (choicePlayer2 == "2")
        players[1] = new SUS_Random_Player<char>('U');
      players[0]->setBoard(board);
      players[1]->setBoard(board);
      break;
    default:
      break;
    }
    if (choiceGame == '4') // the numeric game require in type
    {
      GameManager<int> GAME(boardNumericalGame, playersNumericalGame);
      GAME.run();
    }
    else
    {
      GameManager<char> GAME(board, players);
      GAME.run();
    }
    if (choiceGame == '4') // delete numeric attr
      delete boardNumericalGame;
    else
      delete board;
    for (int i = 0; i < 2; i++)
    {
      if (choiceGame == '4')
        delete playersNumericalGame[i];
      else
        delete players[i];
    }
  }
  return 0;
}