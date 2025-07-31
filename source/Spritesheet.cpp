
#include "Spritesheet.h"

SpriteSheet::SpriteSheet(std::string_view displayName)
	: m_DisplayName(displayName)
{}

SpriteSheet::~SpriteSheet() {
	UnloadTexture(m_Sheet);
}

void SpriteSheet::LoadSheet(const char* sheetPath, int width, int height) {
	if (m_Sheet.id) {
		UnloadTexture(m_Sheet);
	}
	m_Sheet = LoadTexture(sheetPath);
	m_WidthPerSprite = m_Sheet.width / width;
	m_HeightPerSprite = m_Sheet.height / height;
	SetTextureFilter(m_Sheet, TEXTURE_FILTER_POINT);
}

void SpriteSheet::RenderSprite(iVector2 coord, Vector2 position, float scale /* 1.0f */) const {
	Rectangle spriteBounds{ m_WidthPerSprite * coord.x, m_HeightPerSprite * coord.y, m_WidthPerSprite, m_HeightPerSprite };
	Rectangle dest{ position.x, position.y, fabsf(m_WidthPerSprite * scale), fabsf(m_HeightPerSprite * scale) };
	DrawTexturePro(m_Sheet, spriteBounds, dest, { 0.0f, 0.0f }, 0.0f, WHITE);
}

void SpriteSheet::RegisterSprite(int key, iVector2 coord) {
	m_RegisteredSpriteCoords[key] = coord;
}

void SpriteSheet::RenderSprite(int key, Vector2 position, float scale /* 1.0f */) const {
	RenderSprite(m_RegisteredSpriteCoords.at(key), position, scale);
}


