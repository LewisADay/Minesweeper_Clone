
#include "Board.h"
#include <LoggingAD/LoggingAD.h>

Board::Board(int width, int height, int numMines)
	: m_Data(width * height), m_Width(width), m_Height(height), m_NumMines(numMines)
{
	GenerateBoardRandom();
	m_VisibilityMask.resize(width * height, false);
	m_FlagMask.resize(width * height, false);
}

Board::Board(iVector2 size, int numMines)
	: Board(size.x, size.y, numMines)
{}

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
	return m_Data[CoordToIndex({ x, y })];
}

Board::Tile Board::GetValue(const iVector2 coord) const {
	return GetValue(coord.x, coord.y);
}

void Board::Render(bool useVisibility /* = true */) {
	
	// Determine scale factor for renderering so board fills the available space
	int yBasePixels = Sprites->GetHeightPerSprite() * m_Height;
	int xBasePixels = Sprites->GetWidthPerSprite() * m_Width;
	float yScaleFactor = DisplaySize.y / yBasePixels;
	float xScaleFactor = DisplaySize.x / xBasePixels;
	m_ScaleFactor = std::min(yScaleFactor, xScaleFactor);

	// Draw board
	for (int y = 0; y < m_Height; ++y) {
		for (int x = 0; x < m_Width; ++x) {
			if (m_FlagMask[CoordToIndex({ x, y })]) {
				RenderTileAt(Tile::Flag, { x, y });
				continue;
			}
			if (useVisibility && !m_VisibilityMask[CoordToIndex({ x, y })]) {
				if (m_DepressedTileCoords.x == x && m_DepressedTileCoords.y == y) { // This tile is depressed (clicked)
					RenderTileAt(Tile::Clicked, { x, y });
				}
				else {
					RenderTileAt(Tile::Hidden, { x, y });
				}
				if (m_IsGameOver) {
					if (GetValue({ x, y }) == Tile::Bomb) {
						RenderTileAt(Tile::Bang, { x, y });
					}
				}
				continue;
			}
			RenderTileAt(GetValue({ x, y }), { x, y });
		}
	}

	// Clear depressed tile each renderpass
	m_DepressedTileCoords = { -1, -1 };
}

void Board::ProcessInputs() {

	Vector2 position = GetMousePosition();
	if (!IsMouseOnBoard(position)) { return; } // Outside the board render area

	iVector2 mouseCoords = GetMouseBoardCoords(position);

	if (   mouseCoords.x < 0 || mouseCoords.x >= m_Width
		|| mouseCoords.y < 0 || mouseCoords.y >= m_Height)
	{ // Outside the true rendered board
		return;
	}

	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { // Render tile as clicked
		m_DepressedTileCoords = mouseCoords;
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { // Reveal tile
		ClickTile(mouseCoords);
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) { // Flag tile
		FlagTile(mouseCoords);
	}
}

bool Board::IsGameOver() const {
	return m_IsGameOver;
}

void Board::ToggleFlagAt(const iVector2& coord) {
	m_FlagMask[CoordToIndex(coord)] = !m_FlagMask[CoordToIndex(coord)];
}

void Board::DepressTile(const iVector2& coord) {
	m_DepressedTileCoords = coord;
}

bool Board::IsMouseOnBoard(const Vector2& position) {
	if (   position.x > DisplayPosition.x && position.x < DisplayPosition.x + DisplaySize.x
		&& position.y > DisplayPosition.y && position.y < DisplayPosition.y + DisplaySize.y) {
		return true;
	}
	return false;
}

void Board::ClickTile(const iVector2& coord) {
	
	if (m_FlagMask[CoordToIndex(coord)]) {
		return; // No action if we try and click a flag
	}

	if (m_VisibilityMask[CoordToIndex(coord)]) {
		return; // TODO: Add double click detection for area clear
	}

	// Tile is visible and not a flag
	RevealTile(coord);

	// Detect game over state
	if (GetValue(coord) == Tile::Bomb) { // Game Over
		// Reveal all bombs as bangs notify application it's over jim
		m_IsGameOver = true;
	}
}

void Board::FlagTile(const iVector2& coord) {
	if (!m_VisibilityMask[CoordToIndex(coord)]) { // Tile has to be non-visible to flag
		m_FlagMask[CoordToIndex(coord)] = !m_FlagMask[CoordToIndex(coord)];
	}
}

size_t Board::CoordToIndex(const iVector2& coord) const {
	return coord.y * m_Width + coord.x;
}

void Board::RevealTile(iVector2 coord) {

	// Bounds check
	if (coord.x < 0 || coord.x >= m_Width || coord.y < 0 || coord.y >= m_Height) {
		return;
	}

	// Already visible?
	if (m_VisibilityMask[CoordToIndex(coord)]) { return; }

	// Reveal this tile
	m_VisibilityMask[CoordToIndex(coord)] = true;

	// Recursively reveal blank tiles connected it
	if (GetValue(coord) == Tile::Blank) {
		// Left
		RevealTile(coord - iVector2{ -1,  1 });
		RevealTile(coord - iVector2{ -1,  0 });
		RevealTile(coord - iVector2{ -1, -1 });
		// Middle
		RevealTile(coord - iVector2{ 0, -1 });
		RevealTile(coord - iVector2{ 0,  1 });
		// Right
		RevealTile(coord - iVector2{ 1,  1 });
		RevealTile(coord - iVector2{ 1,  0 });
		RevealTile(coord - iVector2{ 1, -1 });
	}
}

iVector2 Board::GetMouseBoardCoords(Vector2 position) {
	
	// Get mouse position in BoardSpace
	position -= DisplayPosition;

	float xUnused = DisplaySize.x - (m_Width * Sprites->GetWidthPerSprite() * m_ScaleFactor);
	float yUnused = DisplaySize.y - (m_Height * Sprites->GetHeightPerSprite() * m_ScaleFactor);
	float xPxPerTile = (DisplaySize.x - xUnused) / m_Width;
	float yPxPerTile = (DisplaySize.y - yUnused) / m_Height;
	int x = position.x / xPxPerTile; // Truncate
	int y = position.y / yPxPerTile; // Truncate
	return iVector2{ x, y };
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
			if (GetValue(x, y) == Tile::Bomb) { continue; } // Skip mines

			int count = 0;
			count += BoundsCheckIsMine({ x - 1, y - 1 });
			count += BoundsCheckIsMine({ x - 1, y });
			count += BoundsCheckIsMine({ x - 1, y + 1 });

			count += BoundsCheckIsMine({ x, y - 1 });
			count += BoundsCheckIsMine({ x, y + 1 });

			count += BoundsCheckIsMine({ x + 1, y - 1 });
			count += BoundsCheckIsMine({ x + 1, y });
			count += BoundsCheckIsMine({ x + 1, y + 1 });

			SetValue({ x, y }, static_cast<Tile>(count));
		}
	}
}

bool Board::BoundsCheckIsMine(const iVector2& coord) {
	if (coord.x < 0 || coord.x >= m_Width || coord.y < 0 || coord.y >= m_Height) {
		return false;
	}

	if (GetValue(coord) == Tile::Bomb) {
		return true;
	}

	return false;
}

void Board::RenderTileAt(Tile tile, const iVector2& coord) const {
	Sprites->RenderSprite(
		tile,
		{
			static_cast<float>(Sprites->GetWidthPerSprite() * coord.x * m_ScaleFactor),
			static_cast<float>(Sprites->GetHeightPerSprite() * coord.y * m_ScaleFactor)
		},
		m_ScaleFactor
	);
}

void Board::SetValue(const iVector2& coord, const Tile value) {
	m_Data[CoordToIndex(coord)] = value;
}
