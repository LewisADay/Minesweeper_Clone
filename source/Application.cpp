
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
    bool orangeSheet = true;
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) { // Regenerate the board
            m_Board = Board{ 30, 16, 99 };
        }
        if (IsKeyPressed(KEY_V)) { // Toggle visibility check on/off
            useVisibility = !useVisibility;
        }
        if (IsKeyPressed(KEY_F)) { // Change sprite sheet
            orangeSheet = !orangeSheet;
            if (orangeSheet) {
                m_SpriteSheet.LoadSheet("sheet_dark.png", 4, 3);
                m_SpriteSheet.RegisterSprite(Tile::Blank, { 0, 2 });
                m_SpriteSheet.RegisterSprite(Tile::One, { 0, 0 });
                m_SpriteSheet.RegisterSprite(Tile::Two, { 1, 0 });
                m_SpriteSheet.RegisterSprite(Tile::Three, { 2, 0 });
                m_SpriteSheet.RegisterSprite(Tile::Four, { 3, 0 });
                m_SpriteSheet.RegisterSprite(Tile::Five, { 1, 0 });
                m_SpriteSheet.RegisterSprite(Tile::Six, { 1, 1 });
                m_SpriteSheet.RegisterSprite(Tile::Seven, { 1, 2 });
                m_SpriteSheet.RegisterSprite(Tile::Eight, { 1, 3 });
                m_SpriteSheet.RegisterSprite(Tile::Bomb, { 2, 2 });
                m_SpriteSheet.RegisterSprite(Tile::Bang, { 2, 2 });
                m_SpriteSheet.RegisterSprite(Tile::Flag, { 3, 2 });
                m_SpriteSheet.RegisterSprite(Tile::Hidden, { 1, 2 });
                m_SpriteSheet.RegisterSprite(Tile::Clicked, { 0, 2 });
            }
            else {
                m_SpriteSheet.LoadSheet("sheet_orange.png", 4, 4);
                m_SpriteSheet.RegisterSprite(Tile::Blank, { 0, 3 });
                m_SpriteSheet.RegisterSprite(Tile::One, { 0, 1 });
                m_SpriteSheet.RegisterSprite(Tile::Two, { 1, 1 });
                m_SpriteSheet.RegisterSprite(Tile::Three, { 2, 1 });
                m_SpriteSheet.RegisterSprite(Tile::Four, { 3, 1 });
                m_SpriteSheet.RegisterSprite(Tile::Five, { 0, 2 });
                m_SpriteSheet.RegisterSprite(Tile::Six, { 1, 2 });
                m_SpriteSheet.RegisterSprite(Tile::Seven, { 2, 2 });
                m_SpriteSheet.RegisterSprite(Tile::Eight, { 3, 2 });
                m_SpriteSheet.RegisterSprite(Tile::Bomb, { 0, 0 });
                m_SpriteSheet.RegisterSprite(Tile::Bang, { 0, 3 });
                m_SpriteSheet.RegisterSprite(Tile::Flag, { 0, 2 });
                m_SpriteSheet.RegisterSprite(Tile::Hidden, { 2, 3 });
                m_SpriteSheet.RegisterSprite(Tile::Clicked, { 3, 3 });
            }
        }

        BeginDrawing();

        ClearBackground(DARKGRAY);

        // Draw board
        m_Board.Render({ 0, 0 }, { (float)GetScreenWidth(), (float)GetScreenHeight() }, m_SpriteSheet, useVisibility);

        EndDrawing();
    }
    CloseWindow();
}
