#pragma once

#include <vector>


class GameField {
	int m_size;

	std::vector<int> field;

public:
	GameField(int size = 3);
	
	int getSize() const;

	std::vector<int> getField() const {
		return field;
	}

	std::vector<int> getAvailableField();

	bool isSpotAvailable(int i);

	bool isHasAvailable();

	void set(int i, int player);

	void clean(int i);

	void fieldPrint() const;

	GameField& operator= (const GameField& gf);
};