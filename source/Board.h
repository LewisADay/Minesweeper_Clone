#pragma once

#include <vector>
#include <random>

class Board {
public:
	Board(int width, int height, int numMines);
	int GetWidth() const;
	int GetHeight() const;
	int GetValue(const int x, const int y) const;
private:
	void GenerateBoardRandom();
	bool BoundsCheckIsMine(int x, int y);
private:
	std::vector<int> m_Data; // Init to size Width * Height of 0's
	int m_Width;
	int m_Height;
	int m_NumMines;
};
