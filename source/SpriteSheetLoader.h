#pragma once

#include <vector>
#include <filesystem>
#include "Spritesheet.h"
#include "Board.h"

class SpriteSheetLoader {
public:
	static SpriteSheetLoader& GetInstance();
	void LoadSheetsFromIni(std::filesystem::path path);
	std::shared_ptr<SpriteSheet> GetSheet(std::string_view name);
private:
	struct SheetInfo {
		std::filesystem::path Path;
		std::string DisplayName;
		int Width;
		int Height;
		std::map<Board::Tile, std::pair<int, int>> TileCoords;
	};

	struct LineData {
		std::string key;
		std::string value;
	};
private:
	SpriteSheetLoader() = default;
	void ProcessSheet(std::ifstream& iniFile);
	LineData GetLineData(const std::string& line);
	std::pair<int, int> GetCoordPair(const std::string& coords);
	std::shared_ptr<SpriteSheet> CreateSpriteSheet(SheetInfo info);
private:
	std::vector<std::shared_ptr<SpriteSheet>> m_Sheets;
};
