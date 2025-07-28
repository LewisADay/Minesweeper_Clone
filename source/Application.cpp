
#include "Application.h"

#include <raylib.h>

#include "Board.h"

Application::Application()
    : m_CurrentScene(TITLE), m_Board(30, 16, 99)
{
    const int width = 30;
    const int height = 16;
    const int mines = 99;
    //m_Board = Board{ width, height, mines };
    m_VisibilityMask.resize(width * height, false);
    m_FlagMask.resize(width * height, false);

    const int screenWidth = 800;
    const int screenHeight = 450;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Minesweeper Clone");

    //m_SpriteSheet.LoadSheet("resources/spritesheets/sheet_orange.png", 4, 4);
    m_SpriteSheet.LoadSheet("sheet_orange.png", 4, 4);
    m_SpriteSheet.RegisterSprite(Tile::Blank,   { 0, 3 });
    m_SpriteSheet.RegisterSprite(Tile::One,     { 0, 1 });
    m_SpriteSheet.RegisterSprite(Tile::Two,     { 1, 1 });
    m_SpriteSheet.RegisterSprite(Tile::Three,   { 2, 1 });
    m_SpriteSheet.RegisterSprite(Tile::Four,    { 3, 1 });
    m_SpriteSheet.RegisterSprite(Tile::Five,    { 0, 2 });
    m_SpriteSheet.RegisterSprite(Tile::Six,     { 1, 2 });
    m_SpriteSheet.RegisterSprite(Tile::Seven,   { 2, 2 });
    m_SpriteSheet.RegisterSprite(Tile::Eight,   { 3, 2 });
    m_SpriteSheet.RegisterSprite(Tile::Bomb,    { 0, 0 });
    m_SpriteSheet.RegisterSprite(Tile::Bang,    { 0, 3 });
    m_SpriteSheet.RegisterSprite(Tile::Flag,    { 0, 2 });
    m_SpriteSheet.RegisterSprite(Tile::Hidden,  { 2, 3 });
    m_SpriteSheet.RegisterSprite(Tile::Clicked, { 3, 3 });

    SetTargetFPS(60);
}

void Application::Run() {
    bool useVisibility = true;
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) { // Regenerate the board
            m_Board = Board{ 30, 16, 99 };
        }
        if (IsKeyPressed(KEY_V)) { // Toggle visibility check on/off
            useVisibility = !useVisibility;
        }

        int yBasePixels = m_SpriteSheet.GetHeightPerSprite() * m_Board.GetHeight();
        int xBasePixels = m_SpriteSheet.GetWidthPerSprite() * m_Board.GetWidth();
        float yScaleFactor = static_cast<float>(GetScreenHeight()) / yBasePixels;
        float xScaleFactor = static_cast<float>(GetScreenWidth()) / xBasePixels;
        m_ScaleFactor = std::min(yScaleFactor, xScaleFactor);

        BeginDrawing();

        ClearBackground(DARKGRAY);

        // Draw board
        for (int y = 0; y < m_Board.GetHeight(); ++y) {
            for (int x = 0; x < m_Board.GetWidth(); ++x) {
                if (m_FlagMask[y * m_Board.GetWidth() + x]) {
                    RenderTileAt(Tile::Flag, x, y);
                    continue;
                }
                if (useVisibility && !m_VisibilityMask[y * m_Board.GetWidth() + x]) {
                    RenderTileAt(Tile::Hidden, x, y);
                    continue;
                }
                RenderTileAt((Tile)m_Board.GetValue(x, y), x, y);
            }
        }

        EndDrawing();
    }
    CloseWindow();
}

void Application::RenderTileAt(Tile tile, int x, int y) {
    m_SpriteSheet.RenderSprite(
        tile,
        {
            static_cast<float>(m_SpriteSheet.GetWidthPerSprite() * x * m_ScaleFactor),
            static_cast<float>(m_SpriteSheet.GetHeightPerSprite() * y * m_ScaleFactor)
        },
        m_ScaleFactor
    );
}
