#pragma once

#include "Spritesheet.h"
#include "Board.h"

class Application {
public:
	Application();
	void Run();
private:
	enum Scene {
		TITLE,
		GAME
	};

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

private:
	void RenderTileAt(Tile tile, int x, int y);

private:
	Scene m_CurrentScene;
	Spritesheet m_SpriteSheet;
	Board m_Board;
	std::vector<bool> m_VisibilityMask;
	std::vector<bool> m_FlagMask;
	float m_ScaleFactor = 1.0f;

};
