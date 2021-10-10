#include "ReversiGame.h"
#include <iostream>
using namespace std;

void ReversiGame::playGame()
{
	ReversiBoard board;
	GameStatus g = IN_PROGRESS;
	int r, c;
	int exiter = 0;
	while (board.getGameStatus() == IN_PROGRESS)
	{
		bool validInput = false;
		do
		{
			bool switchTurn = 0;
		/*	if (!board.isMovePossible())
			{
				switchTurn = 1;
				exiter++;
			}*/
			if (switchTurn == 0)
			{
				exiter = 0;
				board.displayBoard();
				cout << "\tBlack Score: " << board.getBlackScore();
				cout << "\n\tWhite Score: " << board.getWhiteScore();
				cout << "\n\tPlayer " << char(board.getCurrentPlayer()) << " enter position (row column): ";
				cin >> r;
				cin >> c;
				int moveStatus = board.placeDisc(r, c);
				if (moveStatus == 0)
				{
					cout << "\tCells out of range\n";
				}
				else if (board.placeDisc(r, c) == -1)
				{
					cout << "\tInvalid move\n";
				}
				else if (board.placeDisc(r, c) == 1)
				{
					cout << "\tSuccessfully done\n";
					/*cin.get();
					system("CLS");*/
				}
			}
			board.switchPlayerTurn();
			/*if (exiter == 2)
			{
				board.displayBoard();
				cout << "\n\tGame ended due to no player having turns left.";
				exit(0);
			}*/
		} while (validInput == 0 || validInput == -1);
		if (board.getGameStatus() == BLACK_WIN)
		{
			board.displayBoard();
			cout << "\nGame Won by Player :" << "BLACK PLAYER" << "\n";
			g = BLACK_WIN;
		}
		else if(board.getGameStatus() == WHITE_WIN)
		{
			board.displayBoard();
			cout << "\nGame Won by Player :" << "WHITE PLAYER" << "\n";
			g = WHITE_WIN;
		}
		else if (board.getGameStatus() == DRAW)
		{
			board.displayBoard();
			cout << "\nGame Draw.\n";
			g = DRAW;
		}
	}
}