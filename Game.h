#pragma once

class GameField;

class Game {

	GameField* m_board;

	struct Move
	{
		int score;
		int index;
	};

public:
	Game();

	void gameStart();

	void setBoard(GameField& board);

	bool checkWin(GameField& board, int player);

	void playerTurn();

	void aiTurn();

	void gameUpdate(int player);

	Move chooseTurn(GameField& board, int player);

};
