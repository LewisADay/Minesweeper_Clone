#pragma once

#include <raylib.h>
#include <filesystem>
#include <map>

class Spritesheet {
public:
	
	Spritesheet() = default;

	/// <summary>
	/// Load sprite sheet
	/// </summary>
	/// <param name="sheetPath">File path to sprite sheet</param>
	/// <param name="width">Number of sprites width wise on the sheet</param>
	/// <param name="height">Number of sprites height wise on the sheet</param>
	void LoadSheet(const char* sheetPath, int width, int height);

	void RenderSprite(Vector2 coord, Vector2 position, float scale = 1.0f);
	void RegisterSprite(int key, Vector2 coord);
	void RenderSprite(int key, Vector2 position, float scale = 1.0f);

	int GetWidthPerSprite() const { return m_WidthPerSprite; }
	int GetHeightPerSprite() const { return m_HeightPerSprite; }

private: // Private members
	Texture2D m_Sheet = {};
	int m_WidthPerSprite = 0;
	int m_HeightPerSprite = 0;
	std::map<int, Vector2> m_RegisteredSpriteCoords;

};
