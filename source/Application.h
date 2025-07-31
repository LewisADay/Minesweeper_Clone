#pragma once

#include <raylib.h>

#include "Spritesheet.h"
#include "Board.h"
#include "Utils.h"

class Application {
public:
	Application();
	void Run();
private:
	enum Scene {
		Title,
		Game
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
	void ProcessInputs();

private:
	Scene m_CurrentScene;
	Board m_Board;
	bool m_UseVisibility = true;
	int m_Sheet = 0;
};
