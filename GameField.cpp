#include <windows.h>

#include "GameField.h"

#include <iostream>
#include <iomanip>

using namespace std;

GameField::GameField(int size) {
	m_size = size;

	for (int i = 0; i < size * size; i++) {
		field.push_back(0);
	}
}

int GameField::getSize() const {
	return m_size;
}

void GameField::set(int i, int player) {
	field[i] = player;
}

void GameField::clean(int i) {
	field[i] = 0;
}

vector<int> GameField::getAvailableField() {
	vector<int> freeSpots;

	for (int i = 0; i < field.size(); i++) {
		if (field[i] == 0)
			freeSpots.push_back(i);
	}

	return freeSpots;
}

bool GameField::isHasAvailable() {
	int n = getAvailableField().size();

	if (n > 0)
		return true;
	else
		return false;
}

bool GameField::isSpotAvailable(int i) {
	return field[i] == 0;
}

GameField& GameField::operator= (const GameField& gf) {
	if (this == &gf)
		return *this;

	m_size = gf.m_size;
	field = gf.field;

	return *this;
}

void GameField::fieldPrint() const {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < field.size(); i++) {
		if (field[i] == -1) {
			SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_GREEN);
			cout << setw(3) << "O" << " ";
		}
		else if (field[i] == 1) {
			SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_RED);
			cout << setw(3) << "X" << " ";
		}
		else if (field[i] == 0) {
			SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_INTENSITY);
			cout << setw(3) << "-" << " ";
		}

		if ((i + 1) % m_size == 0 && i != 0)
			cout << endl;
	}

	cout << "\n" << endl;

	SetConsoleTextAttribute(hConsoleHandle, 2);
}