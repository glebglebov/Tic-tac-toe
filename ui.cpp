#include <iostream>
#include <Windows.h>

#include "ui.h"
#include "Game.h"
#include "GameField.h"

UI::UI()
{
	game_size = 3;

	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, 2);

	mainMenu();
}

void UI::mainMenu()
{
	int x = 0;

	while (x != -1) {
		std::cout << "---����� ���������� � ��������-������!---\n\n"
			<< "\t1. [������ ����� ����]\n"
			<< "\t2. [��������� ����]\n"
			<< "\t3. [����� �� ����]\n\n"
			<< "������� ��������: ";

		std::cin >> x;
		std::cout << std::endl;

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

void UI::newGame()
{
	std::cout << "\n\n________________________\n\n" << std::endl;

	Game game;
	GameField board(game_size);
	game.setBoard(board);

	std::cout << "���� ����������!\n" << std::endl;

	game.gameStart();
}

void UI::options()
{
	int x = 0;

	std::cout << "---��������� ����---\n\n"
		<< "\t1. [�������� ������ ����]\n\n"
		<< "������� ��������: ";

	std::cin >> x;
	std::cout << std::endl;

	if (x == 1) {
		int y = 0;

		std::cout << "������� ����� ������ �������� ����.\n"
			<< "(�� 3 �� 9)\n"
			<< "������� ������: " << game_size << "\n"
			<< "����: ";

		std::cin >> y;
		std::cout << std::endl;

		if (y >= 3 && y <= 9) {
			if (y != game_size)
				game_size = y;
		}
	}
}
