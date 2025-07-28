
#include "Spritesheet.h"

void Spritesheet::LoadSheet(const char* sheetPath, int width, int height) {
	m_Sheet = LoadTexture(sheetPath);
	m_WidthPerSprite = m_Sheet.width / width;
	m_HeightPerSprite = m_Sheet.height / height;
	SetTextureFilter(m_Sheet, TEXTURE_FILTER_POINT);
}

void Spritesheet::RenderSprite(Vector2 coord, Vector2 position, float scale /* 1.0f */) {
	Rectangle spriteBounds{ m_WidthPerSprite * coord.x, m_HeightPerSprite * coord.y, m_WidthPerSprite, m_HeightPerSprite };
	Rectangle dest{ position.x, position.y, fabsf(m_WidthPerSprite * scale), fabsf(m_HeightPerSprite * scale) };
	DrawTexturePro(m_Sheet, spriteBounds, dest, { 0.0f, 0.0f }, 0.0f, WHITE);
	//DrawTextureRec(m_Sheet, spriteBounds, position, WHITE);
}

void Spritesheet::RegisterSprite(int key, Vector2 coord) {
	m_RegisteredSpriteCoords[key] = coord;
}

void Spritesheet::RenderSprite(int key, Vector2 position, float scale /* 1.0f */) {
	RenderSprite(m_RegisteredSpriteCoords[key], position, scale);
}


