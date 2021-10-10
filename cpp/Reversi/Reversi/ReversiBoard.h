#ifndef REVERSIBOARD_H
#define REVERSIBOARD_H

enum GameStatus {WHITE_WIN ='W', BLACK_WIN = 'B', IN_PROGRESS = 'P', DRAW = 'D'};
enum PlayerTurn {BLACK_PLAYER = 'B', WHITE_PLAYER = 'W'};
enum PlayerSymbol {BLACK_PLAYER_SYMBOL = 'B', WHITE_PLAYER_SYMBOL = 'W'};

#define ROWS 8
#define COLS 8

class ReversiBoard
{
	char data[ROWS][COLS];
	int data2[ROWS][COLS];
	PlayerTurn currentPlayer = BLACK_PLAYER;
	GameStatus gStatus = IN_PROGRESS;
	int whiteScore = 2;
	int blackScore = 2;
public:
	ReversiBoard();
	PlayerTurn getCurrentPlayer();
	void switchPlayerTurn();
	int placeDisc(int r, int c);
	bool isMovePossible();
	void displayBoard();
	int getWhiteScore();
	int getBlackScore();
	GameStatus getGameStatus();
private:
	void markPossibleColMoves();
	void markPossibleRowMoves();
	void markPossible1DiagonalMoves();
	void markPossible2DiagonalMoves();
	void flanker(int i, int j);
};

#endif