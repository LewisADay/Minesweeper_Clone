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
	Scene m_CurrentScene;
	std::shared_ptr<SpriteSheet> m_SpriteSheet;
	Board m_Board;
	float m_ScaleFactor = 1.0f;

};
