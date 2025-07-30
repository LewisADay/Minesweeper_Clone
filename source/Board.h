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
	int GetWidth() const;
	int GetHeight() const;
	Tile GetValue(const int x, const int y) const;
	void Render(Vector2 position, Vector2 size, const SpriteSheet& spriteSheet, bool useVisibility = true);
	void ToggleFlagAt(int x, int y);

private:
	void GenerateBoardRandom();
	bool BoundsCheckIsMine(int x, int y);
	void RenderTileAt(const SpriteSheet& spriteSheet, Tile tile, int x, int y) const;
	void SetValue(const int x, const int y, const Tile value);

private:
	std::vector<Tile> m_Data; // Init to size Width * Height of 0's
	std::vector<bool> m_VisibilityMask;
	std::vector<bool> m_FlagMask;
	int m_Width;
	int m_Height;
	int m_NumMines;
	float m_ScaleFactor = 1.0f;
};
