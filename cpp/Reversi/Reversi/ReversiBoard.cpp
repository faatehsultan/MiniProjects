#include "ReversiBoard.h"
#include <iostream>
using namespace std;

ReversiBoard::ReversiBoard()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			data[i][j] = '.';
		}
	}
	data[6][1] = 'W';
	data[5][2] = 'W';
	data[4][3] = 'W';
	data[3][4] = 'W';
	data[2][5] = 'W';
	data[1][6] = 'W';
	data[7][0] = 'B';
	displayBoard();
}

void ReversiBoard::displayBoard()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			data2[i][j] = data[i][j];
		}
	}
	markPossibleColMoves();
	markPossibleRowMoves();
	markPossible1DiagonalMoves();
	markPossible2DiagonalMoves();
	cout << "\t\t1\t2\t3\t4\t5\t6\t7\t8\n"
		<< "\t\t---------------------------------------------------------\n";
	for (int i = 0; i < ROWS; i++)
	{
		cout << "\t" << i + 1 << "|" << '\t';
		for (int j = 0; j < COLS; j++)
		{
			if (data2[i][j] == '.')
			{
				cout << ".";
			}
			else if (data2[i][j] == 'B')
			{
				cout << "B";
			}
			else if (data2[i][j] == 'W')
			{
				cout << "W";
			}
			else
			{
				cout << data2[i][j];
			}
			if (j != COLS - 1)
			{
				cout << "\t";
			}
			else
			{
				cout << "\n";
			}
		}
	}
}

int ReversiBoard::getWhiteScore()
{
	int score = 0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (data[i][j] == 'W')
			{
				score++;
			}
		}
	}
	whiteScore = score;
	return whiteScore;
}

int ReversiBoard::getBlackScore()
{
	int score = 0;
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (data[i][j] == 'B')
			{
				score++;
			}
		}
	}
	blackScore = score;
	return blackScore;
}

PlayerTurn ReversiBoard::getCurrentPlayer()
{
	return currentPlayer;
}

void ReversiBoard::switchPlayerTurn()
{
	if (currentPlayer == BLACK_PLAYER)
	{
		currentPlayer = WHITE_PLAYER;
	}
	else
	{
		currentPlayer = BLACK_PLAYER;
	}
}

int ReversiBoard::placeDisc(int r, int c)
{
	if (!(((r >= 1 && r <= 8) || (c >= 1 && c <= 8))))
	{
		return 0;
	}
	else if (data2[r-1][c-1] == '.' || data2[r-1][c-1] == 'B' || data2[r-1][c-1] == 'W')
	{
		return -1;
	}
	else if (data2[r-1][c-1] > 0 && data2[r-1][c-1] < 46)
	{
		if (getCurrentPlayer() == BLACK_PLAYER)
		{
			blackScore = blackScore + data2[r - 1][c - 1];
			data[r-1][c-1] = BLACK_PLAYER_SYMBOL;
			flanker(r - 1, c - 1);
		}
		else
		{
			whiteScore = whiteScore + data2[r - 1][c - 1];
			data[r-1][c-1] = WHITE_PLAYER_SYMBOL;
			flanker(r - 1, c - 1);
		}
		return 1;
	}
}

GameStatus ReversiBoard::getGameStatus()
{
	if (!isMovePossible() && (getBlackScore() > getWhiteScore()))
	{
		gStatus = BLACK_WIN;
	}
	else if (!isMovePossible() && (getBlackScore() < getWhiteScore()))
	{
		gStatus = WHITE_WIN;
	}
	else if (!isMovePossible() && getBlackScore() == getWhiteScore())
	{
		gStatus = DRAW;
	}
	return gStatus;
}

bool ReversiBoard::isMovePossible()
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			data2[i][j] = data[i][j];
		}
	}
	markPossibleColMoves();
	markPossibleRowMoves();
	markPossible1DiagonalMoves();
	markPossible2DiagonalMoves();
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (data2[i][j] != 'W' && data2[i][j] != 'B' && data2[i][j] != '.')
			{
				return true;
			}
		}
	}
	return false;
}

void ReversiBoard::markPossibleColMoves()
{
	char scorer;
	bool validScore = 1;
	if (getCurrentPlayer() == WHITE_PLAYER)
	{
		scorer = BLACK_PLAYER_SYMBOL;
	}
	else
	{
		scorer = WHITE_PLAYER_SYMBOL;
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			int scoreCounts1 = 0;
			if (j != 7)
			{
				if (data2[i][j] == '.' && data2[i][j + 1] == scorer)
				{
					int c;
					for (c = j + 1; data2[i][c] == scorer && c < COLS; c++)
					{
						scoreCounts1++;
					}
					if (scoreCounts1 != 0 && data2[i][c] == getCurrentPlayer())
					{
						data2[i][j] = scoreCounts1;
						if (data2[i][j] > 46)
						{
							data2[i][j] = data2[i][j] - 46;
						}
						validScore = 0;
					}
				}
			}
			if (j != 0)
			{
				if (data2[i][j] != 'B' && data2[i][j] != 'W' && data2[i][j - 1] == scorer)
				{
					int scoreCounts2 = 0;
					int c;
					for (c = j - 1; data2[i][c] == scorer && c > 0; c--)
					{
						scoreCounts2++;
					}
					if (scoreCounts2 != 0 && data2[i][c] == getCurrentPlayer())
					{
						int totalCount = scoreCounts2;
						if (validScore == 0)
						{
							int totalCount = scoreCounts1 + scoreCounts2;
						}
						data2[i][j] = totalCount;
						if (data2[i][j] > 46)
						{
							data2[i][j] = data2[i][j] - 46;
						}
					}
				}
			}
		}
	}
}

void ReversiBoard::markPossibleRowMoves()
{
	char scorer;
	bool validScore = 1;
	if (getCurrentPlayer() == WHITE_PLAYER)
	{
		scorer = BLACK_PLAYER_SYMBOL;
	}
	else
	{
		scorer = WHITE_PLAYER_SYMBOL;
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			int scorecounts1 = 0;
			if (i != 7)
			{
				if (data2[i][j] != 'W' && data2[i][j] != 'B' && data2[i + 1][j] == scorer)
				{
					int c;
					for (c = i + 1; data2[c][j] == scorer && c < COLS; c++)
					{
						scorecounts1++;
					}
					if (c == COLS)
					{
						scorecounts1 = 0;
					}
					if (scorecounts1 != 0 && data2[c][j] == getCurrentPlayer())
					{
						data2[i][j] = data2[i][j] + scorecounts1;
						if (data2[i][j] > 46)
						{
							data2[i][j] = data2[i][j] - 46;
						}
						validScore = 0;
					}
				}
			}
			if (j != 0)
			{
				if (data2[i][j] != 'W' && data2[i][j] != 'B' && data2[i - 1][j] == scorer)
				{
					int scoreCounts2 = 0;
					int c;
					for (c = i - 1; data2[c][j] == scorer && c > 0; c--)
					{
						scoreCounts2++;
					}
					if (scoreCounts2 != 0 && data2[c][j] == getCurrentPlayer())
					{
						int totalCount = scoreCounts2;
						if (validScore == 0)
						{
							int totalCount = scorecounts1 + scoreCounts2;
						}
						data2[i][j] = data2[i][j] + totalCount;
						if (data2[i][j] > 46)
						{
							data2[i][j] = data2[i][j] - 46;
						}
					}
				}
			}
		}
	}
}

void ReversiBoard::markPossible1DiagonalMoves()
{
	char scorer;
	bool validScore = 1;
	if (getCurrentPlayer() == WHITE_PLAYER)
	{
		scorer = BLACK_PLAYER_SYMBOL;
	}
	else
	{
		scorer = WHITE_PLAYER_SYMBOL;
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (j != 7)
			{
				if (data2[i][j] != 'B' && data2[i][j] != 'W' && data2[i + 1][j + 1] == scorer)
				{
					int scoreCounts = 0;
					int c;
					int k;
					for (k = j + 1, c = i + 1; data2[c][k] == scorer && k < ROWS && c < COLS; k++, c++)
					{
						scoreCounts++;
					}
					if (scoreCounts != 0 && data2[c][k] == getCurrentPlayer())
					{
						data2[i][j] = data2[i][j] + scoreCounts;
						if (data2[i][j] > 46)
						{
							data2[i][j] = data2[i][j] - 46;
						}
					}
				}
			}
			if (j != 0)
			{
				cout << "\ti: " << i << "  j: " << j << endl << scorer << endl;
				if (data2[i][j] != 'B' && data2[i][j] != 'W' && data2[i - 1][j - 1] == scorer)
				{
					int scoreCounts = 0;
					int c;
					int k;
					for (k = j - 1, c = i - 1; data2[c][k] == scorer && k > 0 && c > 0; k--, c--)
					{
						cout << "\t c: " << c + 1 << "  k: " << k + 1;
						scoreCounts++;
						cout << "  score:  " << scoreCounts << endl;
					}
					if (scoreCounts != 0 && data2[c][k] == getCurrentPlayer())
					{
						data2[i][j] = data2[i][j] + scoreCounts;
						if (data2[i][j] > 46)
						{
							data2[i][j] = data2[i][j] - 46;
						}
					}
				}
			}
		}
	}
}

void ReversiBoard::markPossible2DiagonalMoves()
{
	char scorer;
	if (getCurrentPlayer() == WHITE_PLAYER)
	{
		scorer = BLACK_PLAYER_SYMBOL;
	}
	else
	{
		scorer = WHITE_PLAYER_SYMBOL;
	}
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (i != 0 && j != 0)
			{
				if (data2[i][j] != 'B' && data2[i][j] != 'W' && data2[i + 1][j - 1] == scorer)
				{

					int scoreCounts = 0;
					int c;
					int k;
					for (k = j - 1, c = i + 1; data2[c][k] == scorer && c < ROWS && k > 0;c++, k--)
					{
						scoreCounts++;
					}
					if (scoreCounts != 0 && data2[c][k] == 'B')
					{
						data2[i][j] = data2[i][j] + scoreCounts;
						if (data2[i][j] > 46)
						{
							data2[i][j] = data2[i][j] - 46;
						}
					}
				}
			}
			if (j != 7)
			{
				if (data2[i][j] != 'B' && data2[i][j] != 'W' && data2[i - 1][j + 1] == scorer)
				{

					int scoreCounts = 0;
					int c;
					int k;
					for (k = j + 1, c = i - 1; c > 0 && data2[c][k] == scorer && k < COLS; c--, k++)
					{
						scoreCounts++;
					}
					if (scoreCounts != 0 && data2[c][k] == getCurrentPlayer())
					{
						data2[i][j] = data2[i][j] + scoreCounts;
						if (data2[i][j] > 46)
						{
							data2[i][j] = data2[i][j] - 46;
						}
					}
				}
			}
		}
	}
}

void ReversiBoard::flanker(int i, int j)
{
	char scorer;
	if (getCurrentPlayer() == WHITE_PLAYER)
	{
		scorer = BLACK_PLAYER_SYMBOL;
	}
	else
	{
		scorer = WHITE_PLAYER_SYMBOL;
	}
	if (data[i + 1][j] == scorer)
	{
		bool isFlank = 0;
		for (int c = i + 2; c < ROWS; c++)
		{
			if (data[c][j] == getCurrentPlayer())
			{
				isFlank = 1;
			}
		}
		for (int c = i + 1; isFlank && data[c][j] != getCurrentPlayer(); c++)
		{
			data[c][j] = getCurrentPlayer();
		}
	}
	if (data[i - 1][j] == scorer)
	{
		bool isFlank = 0;
		for (int c = i - 2; c > 0; c--)
		{
			if (data[c][j] == getCurrentPlayer())
			{
				isFlank = 1;
			}
		}
		for (int c = i - 1; isFlank && data[c][j] != getCurrentPlayer(); c--)
		{
			data[c][j] = getCurrentPlayer();
		}
	}
	if (data[i][j + 1] == scorer)
	{
		bool isFlank = 0;
		for (int c = j + 2; c < COLS; c++)
		{
			if (data[i][c] == getCurrentPlayer())
			{
				isFlank = 1;
			}
		}
		for (int c = j + 1; isFlank && data[i][c] != getCurrentPlayer(); c++)
		{
			data[i][c] = getCurrentPlayer();
		}
	}
	if (data[i][j - 1] == scorer)
	{
		bool isFlank = 0;
		for (int c = j - 2; c > 0; c--)
		{
			if (data[i][c] == getCurrentPlayer())
			{
				isFlank = 1;
			}
		}
		for (int c = j - 1; isFlank && data[i][c] != getCurrentPlayer(); c--)
		{
			data[i][c] = getCurrentPlayer();
		}
	}
	if (data[i + 1][j + 1] == scorer)
	{
		bool isFlank = 0;
		for (int c = i + 2, k = j + 2 ;c < COLS && k < ROWS; c++, k++)
		{
			if (data[c][k] == getCurrentPlayer())
			{
				isFlank = 1;
			}
		}
		for (int c = i + 1, k = j + 1; isFlank && data[c][k] != getCurrentPlayer();k++,c++)
		{
			data[c][k] = getCurrentPlayer();
		}
	}
	if (data[i - 1][j - 1] == scorer)
	{
		bool isFlank = 0;
		for (int c = i - 2, k = j - 2; c >= 0 && k >= 0; c--, k--)
		{
			if (data[c][k] == getCurrentPlayer())
			{
				isFlank = 1;
			}
		}
		for (int c = i - 1, k = j - 1; isFlank && data[c][k] != getCurrentPlayer(); k--, c--)
		{
			data[c][k] = getCurrentPlayer();
		}
	}
	if (data[i + 1][j - 1] == scorer)
	{
		bool isFlank = 0;
		for (int c = i + 2, k = j - 2; c < COLS && k > 0; c++, k--)
		{
			if (data[c][k] == getCurrentPlayer())
			{
				isFlank = 1;
			}
		}
		for (int c = i + 1, k = j - 1; isFlank && data[c][k] != getCurrentPlayer(); k--, c++)
		{
			data[c][k] = getCurrentPlayer();
		}
	}
	if (data[i - 1][j + 1] == scorer)
	{
		bool isFlank = 0;
		for (int c = i - 2, k = j + 2; c >= 0 && k <= COLS; c--, k++)
		{
			if (data[c][k] == getCurrentPlayer())
			{
				isFlank = 1;
			}
		}
		for (int c = i - 1, k = j + 1; isFlank && data[c][k] != getCurrentPlayer(); k++, c--)
		{
			data[c][k] = getCurrentPlayer();
		}
	}
}