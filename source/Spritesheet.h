#pragma once

#include <raylib.h>
#include <filesystem>
#include <map>

#include "Utils.h"

class SpriteSheet {
public:
	
	SpriteSheet(std::string_view displayName);
	~SpriteSheet();

	/// <summary>
	/// Load sprite sheet
	/// </summary>
	/// <param name="sheetPath">File path to sprite sheet</param>
	/// <param name="width">Number of sprites width wise on the sheet</param>
	/// <param name="height">Number of sprites height wise on the sheet</param>
	void LoadSheet(const char* sheetPath, int width, int height);

	void RenderSprite(iVector2 coord, Vector2 position, float scale = 1.0f) const;
	void RegisterSprite(int key, iVector2 coord);
	void RenderSprite(int key, Vector2 position, float scale = 1.0f) const;

	int GetWidthPerSprite() const { return m_WidthPerSprite; }
	int GetHeightPerSprite() const { return m_HeightPerSprite; }
	std::string GetDisplayName() const { return m_DisplayName; }

private: // Private members
	std::string m_DisplayName = "";
	Texture2D m_Sheet = {};
	int m_WidthPerSprite = 0;
	int m_HeightPerSprite = 0;
	std::map<int, iVector2> m_RegisteredSpriteCoords;

};
