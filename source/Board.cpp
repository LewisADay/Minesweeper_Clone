
#include "Board.h"

Board::Board(int width, int height, int numMines)
	: m_Data(width * height), m_Width(width), m_Height(height), m_NumMines(numMines)
{
	GenerateBoardRandom();
	m_VisibilityMask.resize(width * height, false);
	m_FlagMask.resize(width * height, false);
}

int Board::GetWidth() const {
	return m_Width;
}

int Board::GetHeight() const {
	return m_Height;
}

Board::Tile Board::GetValue(const int x, const int y) const {
	if (x < 0 || x > m_Width || y < 0 || y > m_Height) {
		throw("Invalid lookup!");
	}
	return m_Data[y * m_Width + x];
}

void Board::Render(Vector2 position, Vector2 size, const Spritesheet& spriteSheet, bool useVisibility /* = true */) {
	
	// Determine scale factor for renderering so board fills the available space
	int yBasePixels = spriteSheet.GetHeightPerSprite() * m_Height;
	int xBasePixels = spriteSheet.GetWidthPerSprite() * m_Width;
	float yScaleFactor = size.y / yBasePixels;
	float xScaleFactor = size.x / xBasePixels;
	m_ScaleFactor = std::min(yScaleFactor, xScaleFactor);

	// Draw board
	for (int y = 0; y < m_Height; ++y) {
		for (int x = 0; x < m_Width; ++x) {
			if (m_FlagMask[y * m_Width + x]) {
				RenderTileAt(spriteSheet, Tile::Flag, x, y);
				continue;
			}
			if (useVisibility && !m_VisibilityMask[y * m_Width + x]) {
				RenderTileAt(spriteSheet, Tile::Hidden, x, y);
				continue;
			}
			RenderTileAt(spriteSheet, GetValue(x, y), x, y);
		}
	}
}

void Board::ToggleFlagAt(int x, int y) {
	m_FlagMask[y * m_Width + x] = !m_FlagMask[y * m_Width + x];
}

void Board::GenerateBoardRandom() {
	static std::random_device m_RandDevice;
	static std::mt19937 rng{ m_RandDevice() };
	static std::uniform_int_distribution<int> dist{0, (m_Width * m_Height) - 1};

	int minesLayed = 0;
	while (minesLayed < m_NumMines) {
		int index = dist(rng);
		if (m_Data[index] == Tile::Bomb) { continue; } // Duplicate placement
		m_Data[index] = Tile::Bomb;
		++minesLayed;
	}

	// Adjacencies
	for (int y = 0; y < m_Height; ++y) {
		for (int x = 0; x < m_Width; ++x) {
			if (m_Data[y * m_Width + x] == Tile::Bomb) { continue; } // Skip mines

			int count = 0;
			count += BoundsCheckIsMine(x - 1, y - 1);
			count += BoundsCheckIsMine(x - 1, y);
			count += BoundsCheckIsMine(x - 1, y + 1);

			count += BoundsCheckIsMine(x, y - 1);
			count += BoundsCheckIsMine(x, y + 1);

			count += BoundsCheckIsMine(x + 1, y - 1);
			count += BoundsCheckIsMine(x + 1, y);
			count += BoundsCheckIsMine(x + 1, y + 1);

			m_Data[y * m_Width + x] = static_cast<Tile>(count);
		}
	}
}

bool Board::BoundsCheckIsMine(int x, int y) {
	if (x < 0 || x >= m_Width || y < 0 || y >= m_Height) {
		return false;
	}

	if (m_Data[y * m_Width + x] == Tile::Bomb) {
		return true;
	}

	return false;
}

void Board::RenderTileAt(const Spritesheet& spriteSheet, Tile tile, int x, int y) const {
	spriteSheet.RenderSprite(
		tile,
		{
			static_cast<float>(spriteSheet.GetWidthPerSprite() * x * m_ScaleFactor),
			static_cast<float>(spriteSheet.GetHeightPerSprite() * y * m_ScaleFactor)
		},
		m_ScaleFactor
	);
}
