
#include "SpritesheetLoader.h"

#include <fstream>
#include <algorithm>
#include <ranges>
#include <LoggingAD/LoggingAD.h>

#include "Board.h"

SpriteSheetLoader& SpriteSheetLoader::GetInstance() {
	static SpriteSheetLoader instance{};
	return instance;
}

void SpriteSheetLoader::LoadSheetsFromIni(std::filesystem::path path) {
	LoggingAD::Trace("[SpriteSheetLoader] Loading sprite sheet details from {}", path.string());

	std::ifstream iniFile;
	iniFile.open(path);

	if (!iniFile.is_open()) {
		LoggingAD::Error("[SpriteSheetLoader] Failed to load sprite sheet ini file! Check working directory to ensure resources are present.");
		return;
	}

	LoggingAD::Trace("[SpriteSheetLoader] Sprite sheet ini file opened successfully.");

	std::string line;
	while (std::getline(iniFile, line)) {
		if (line == "Sheet") { // Process this sheet
			ProcessSheet(iniFile);
		}
	}

	// End of file
	LoggingAD::Trace("[SpriteSheetLoader] End of Ini File at path {}", path.string());
	if (m_Sheets.empty()) {
		LoggingAD::Error("[SpriteSheetLoader] Finished parsing ini file at path {}, no sprite sheet information found!", path.string());
	}
}

std::shared_ptr<SpriteSheet> SpriteSheetLoader::GetSheet(std::string_view name) {
	
	auto sheetIt = std::ranges::find_if(
		m_Sheets,
		[&name](auto sheet) {
			return sheet->GetDisplayName() == name;
		}
	);

	if (sheetIt == m_Sheets.end()) {
		LoggingAD::Error("Sought sheet with name {}, no such sheet has been loaded.", name);
	}

	return *sheetIt;
}

void SpriteSheetLoader::ProcessSheet(std::ifstream& iniFile) {
	std::string line;
	SheetInfo info{};

	while (std::getline(iniFile, line), line != "") {
		LineData data = GetLineData(line);

		if (data.key == "DisplayName")  { info.DisplayName = data.value; }
		else if (data.key == "Path")	{ info.Path = data.value; }
		else if (data.key == "Width")	{ info.Width = std::stoi(data.value); }
		else if (data.key == "Height")	{ info.Height = std::stoi(data.value); }
		else if (data.key == "Blank")	{ info.TileCoords[Board::Tile::Blank]	= GetCoordPair(data.value); }
		else if (data.key == "One")		{ info.TileCoords[Board::Tile::One]		= GetCoordPair(data.value);	}
		else if (data.key == "Two")		{ info.TileCoords[Board::Tile::Two]		= GetCoordPair(data.value); }
		else if (data.key == "Three")	{ info.TileCoords[Board::Tile::Three]	= GetCoordPair(data.value); }
		else if (data.key == "Four")	{ info.TileCoords[Board::Tile::Four]	= GetCoordPair(data.value); }
		else if (data.key == "Five")	{ info.TileCoords[Board::Tile::Five]	= GetCoordPair(data.value); }
		else if (data.key == "Six")		{ info.TileCoords[Board::Tile::Six]		= GetCoordPair(data.value); }
		else if (data.key == "Seven")	{ info.TileCoords[Board::Tile::Seven]	= GetCoordPair(data.value); }
		else if (data.key == "Eight")	{ info.TileCoords[Board::Tile::Eight]	= GetCoordPair(data.value); }
		else if (data.key == "Bomb")	{ info.TileCoords[Board::Tile::Bomb]	= GetCoordPair(data.value); }
		else if (data.key == "Bang")	{ info.TileCoords[Board::Tile::Bang]	= GetCoordPair(data.value); }
		else if (data.key == "Flag")	{ info.TileCoords[Board::Tile::Flag]	= GetCoordPair(data.value); }
		else if (data.key == "Hidden")	{ info.TileCoords[Board::Tile::Hidden]	= GetCoordPair(data.value); }
		else if (data.key == "Clicked")	{ info.TileCoords[Board::Tile::Clicked]	= GetCoordPair(data.value); }
	}

	m_Sheets.push_back(CreateSpriteSheet(info));
	LoggingAD::Trace("Loaded sprite sheet from path {}", info.Path.string().c_str());
}

SpriteSheetLoader::LineData SpriteSheetLoader::GetLineData(const std::string& line) {
	LineData data{};
	int index = line.find('=');
	data.key = line.substr(0, index);
	data.value = line.substr(index + 1, line.size() - index - 1);
	return data;
}

std::pair<int, int> SpriteSheetLoader::GetCoordPair(const std::string& coords) {
	int x;
	int y;

	int index = coords.find(',');
	x = std::stoi(coords.substr(index - 1, 1));
	y = std::stoi(coords.substr(index + 1, 1));

	return { x, y };
}

std::shared_ptr<SpriteSheet> SpriteSheetLoader::CreateSpriteSheet(SheetInfo info) {
	std::shared_ptr<SpriteSheet> sheet = std::make_shared<SpriteSheet>(info.DisplayName);
	sheet->LoadSheet(info.Path.string().c_str(), info.Width, info.Height);

	for (const auto& [tile, coords] : info.TileCoords) {
		sheet->RegisterSprite(tile, { coords.first, coords.second });
	}

	return sheet;
}
