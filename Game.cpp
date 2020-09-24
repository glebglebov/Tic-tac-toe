#include "Game.h"
#include "GameField.h"

#include <iostream>

using namespace std;

Game::Game() {
	m_board = 0;
}

void Game::gameStart() {
	if (m_board) {
		m_board->fieldPrint();

		cout << "Кидаем монетку..." << endl;
		int rnd = rand() % 100 + 1;

		if (rnd > 50) {
			cout << "Первым ходит бот!\n" << endl;

			int n = m_board->getSize();
			int i = rand() % n + 0;

			cout << "Ходит бот...\n" << endl;

			m_board->set(i, 1);
			gameUpdate(1);
		}
		else {
			cout << "Вы ходите первым!\n" << endl;

			playerTurn();
		}
	}
	else {
		cerr << "Нет игровой доски";
	}
}

void Game::setBoard(GameField& board) {
	m_board = &board;
}

bool Game::checkWin(GameField& board, int player) {
	int n = board.getSize();

	vector<int> field = board.getField();

	bool res = false;

	int i = 0;
	while (!res && i < n * n) {
		res = true;

		for (int j = i, k = 0; k < n; j++, k++) {
			if (field[j] != player) {
				res = false;
				break;
			}
		}

		i += n;
	}

	if (!res) {
		for (int i = 0; i < n; i++) {
			res = true;

			int j = i;
			int k = 0;
			while (k < n) {
				if (field[j] != player) {
					res = false;
					break;
				}

				j += n;
				k++;
			}

			if (res == true)
				break;
		}
	}

	if (!res) {
		int k = 0;

		res = true;

		while (k < n * n) {
			if (field[k] != player) {
				res = false;
				break;
			}

			k = k + n + 1;
		}
	}

	if (!res) {
		int k = n - 1;

		res = true;

		while (k <= n * n - n) {
			if (field[k] != player) {
				res = false;
				break;
			}

			k = k + n - 1;
		}
	}

	return res;
}

Game::Move Game::chooseTurn(GameField& board, int player) {
	Move res;

	vector<int> available = board.getAvailableField();

	if (available.size() > 8) {
		int n = board.getSize();
		int rnd = rand() % available.size() + 1;

		res.index = available[rnd-1];

		return res;
	}

	if (checkWin(board, 1)) {
		res.score = 10;
		return res;
	}
	else if (checkWin(board, -1)) {
		res.score = -10;
		return res;
	}
	else if (available.size() == 0) {
		res.score = 0;
		return res;
	}

	Move move;
	vector<Move> moves;

	for (int i = 0; i < available.size(); i++) {
		board.set(available[i], player);

		move.index = available[i];
		
		if (player == 1) {
			res = chooseTurn(board, -1);
			move.score = res.score;
		}
		else if (player == -1) {
			res = chooseTurn(board, 1);
			move.score = res.score;
		}

		moves.push_back(move);
		board.clean(available[i]);
	}

	int bestMove = 0;
	int bestScore = 0;

	if (player == -1) {
		bestScore = 100;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score < bestScore) {
				bestScore = moves[i].score;
				bestMove = i;
			}
		}
	}
	else if (player == 1) {
		bestScore = -100;
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].score > bestScore) {
				bestScore = moves[i].score;
				bestMove = i;
			}
		}
	}

	return moves[bestMove];
}

void Game::gameUpdate(int player) {
	m_board->fieldPrint();

	if (checkWin(*m_board, player)) {
		if (player == 1)
			cout << "Вы проиграли!\n";
		else if (player == -1)
			cout << "Вы победили!\n";

		cout << "\n" << endl;

		return;
	}
	else if (!m_board->isHasAvailable()) {
		cout << "Ничья.\n" << endl;

		return;
	}

	if (player == 1)
		playerTurn();
	else if (player == -1)
		aiTurn();
}

void Game::playerTurn() {
	int x, y;

	cout << "Ваш ход!\n"
		<< "Строка и столбец: ";

	cin >> x >> y;
	cout << endl;

	x -= 1;
	y -= 1;

	int i = x * m_board->getSize() + y;

	if (m_board->isSpotAvailable(i)) {
		m_board->set(i, -1);
		gameUpdate(-1);

	}
	else {
		cout << "Эта клетка уже занята!\n" << endl;
		playerTurn();
	}
}

void Game::aiTurn() {
	cout << "Ходит бот...\n" << endl;

	GameField newBoard = *m_board;

	Move move = chooseTurn(newBoard, 1);

	m_board->set(move.index, 1);
	gameUpdate(1);
}