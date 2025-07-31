#pragma once

#include <vector>
#include <random>

#include "Spritesheet.h"

class Board {
public:
	enum Tile {
		Blank = 0,
		One,
		Two,
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Bomb,
		Bang,
		Flag,
		Hidden,
		Clicked
	};

public:
	Board(int width, int height, int numMines);
	Board(iVector2 size, int numMines);
	int GetWidth() const;
	int GetHeight() const;
	Tile GetValue(const int x, const int y) const;
	Tile GetValue(const iVector2 coord) const;
	void Render(bool useVisibility = true);
	void ProcessInputs();
	bool IsGameOver() const;

public:
	Vector2 DisplayPosition = { 0, 0 };
	Vector2 DisplaySize = { (float)GetScreenWidth(), (float)GetScreenHeight() };
	std::shared_ptr<SpriteSheet> Sprites;

private:
	void GenerateBoardRandom();
	bool BoundsCheckIsMine(const iVector2& coord);
	void RenderTileAt(Tile tile, const iVector2& coord) const;
	void SetValue(const iVector2& coord, const Tile value);
	void ToggleFlagAt(const iVector2& coord);
	void DepressTile(const iVector2& coord);
	iVector2 GetMouseBoardCoords(Vector2 position);
	bool IsMouseOnBoard(const Vector2& position);
	void ClickTile(const iVector2& coord);
	void FlagTile(const iVector2& coord);
	size_t CoordToIndex(const iVector2& coord) const;
	void RevealTile(iVector2 coord);

private:
	std::vector<Tile> m_Data; // Init to size Width * Height of 0's
	std::vector<bool> m_VisibilityMask;
	std::vector<bool> m_FlagMask;
	int m_Width;
	int m_Height;
	int m_NumMines;
	float m_ScaleFactor = 1.0f;
	iVector2 m_DepressedTileCoords = { -1, -1 };
	bool m_IsGameOver = false;
};
