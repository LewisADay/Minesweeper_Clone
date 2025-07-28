
#include "Board.h"

Board::Board(int width, int height, int numMines)
	: m_Data(width * height), m_Width(width), m_Height(height), m_NumMines(numMines)
{
	GenerateBoardRandom();
}

int Board::GetWidth() const {
	return m_Width;
}

int Board::GetHeight() const {
	return m_Height;
}

int Board::GetValue(const int x, const int y) const {
	if (x < 0 || x > m_Width || y < 0 || y > m_Height) {
		throw("Invalid lookup!");
	}
	return m_Data[y * m_Width + x];
}

void Board::GenerateBoardRandom() {
	static std::random_device m_RandDevice;
	static std::mt19937 rng{ m_RandDevice() };
	static std::uniform_int_distribution<int> dist{0, (m_Width * m_Height) - 1};

	int minesLayed = 0;
	while (minesLayed < m_NumMines) {
		int index = dist(rng);
		if (m_Data[index] == -1) { continue; } // Duplicate placement
		m_Data[index] = -1;
		++minesLayed;
	}

	// Adjacencies
	for (int y = 0; y < m_Height; ++y) {
		for (int x = 0; x < m_Width; ++x) {
			int& tile = m_Data[y * m_Width + x];
			if (tile == -1) { continue; } // Skip mines

			tile += BoundsCheckIsMine(x - 1, y - 1);
			tile += BoundsCheckIsMine(x - 1, y);
			tile += BoundsCheckIsMine(x - 1, y + 1);

			tile += BoundsCheckIsMine(x, y - 1);
			tile += BoundsCheckIsMine(x, y);
			tile += BoundsCheckIsMine(x, y + 1);

			tile += BoundsCheckIsMine(x + 1, y - 1);
			tile += BoundsCheckIsMine(x + 1, y);
			tile += BoundsCheckIsMine(x + 1, y + 1);
		}
	}
}

bool Board::BoundsCheckIsMine(int x, int y) {
	if (x < 0 || x >= m_Width || y < 0 || y >= m_Height) {
		return false;
	}

	if (m_Data[y * m_Width + x] == -1) {
		return true;
	}

	return false;
}
