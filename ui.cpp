#include <iostream>
#include <Windows.h>

#include "ui.h"
#include "Game.h"
#include "GameField.h"

using namespace std;

UI::UI() {
	game_size = 3;

	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, 2);

	mainMenu();
}

void UI::mainMenu() {
	int x = 0;

	while (x != -1) {
		cout << "---����� ���������� � ��������-������!---\n\n"
			<< "\t1. [������ ����� ����]\n"
			<< "\t2. [��������� ����]\n"
			<< "\t3. [����� �� ����]\n\n"
			<< "������� ��������: ";

		cin >> x;
		cout << endl;

		if (x == 1) {
			newGame();

		}
		else if (x == 2) {
			options();
		}
		else if (x == 3) {
			x = -1;
			break;
		}
	}

}

void UI::newGame() {
	cout << "\n\n________________________\n\n" << endl;

	Game game;

	GameField board(game_size);

	game.setBoard(board);

	cout << "���� ����������!\n" << endl;

	game.gameStart();

}

void UI::options() {
	int x = 0;

	cout << "---��������� ����---\n\n"
		<< "\t1. [�������� ������ ����]\n\n"
		<< "������� ��������: ";

	cin >> x;
	cout << endl;

	if (x == 1) {
		int y = 0; 

		cout << "������� ����� ������ �������� ����.\n"
			<< "(�� 3 �� 9)\n"
			<< "������� ������: " << game_size << "\n"
			<< "����: ";

		cin >> y;
		cout << endl;

		if (y >= 3 && y <= 9) {
			if (y != game_size)
				game_size = y;
		}
	}
}