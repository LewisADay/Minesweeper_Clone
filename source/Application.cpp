
#include "Application.h"

#include <raylib.h>
#include <LoggingAD/LoggingAD.h>

#include "Board.h"
#include "SpriteSheetLoader.h"
#include "Utils.h"

Application::Application()
    : m_CurrentScene(Game), m_Board(30, 16, 99)
{
    LoggingAD::SetConfig({ .OutputLevel = LoggingAD::LogLevel::Trace });
    
    m_Board.DisplayPosition = { 0, 0 };

    const int screenWidth = 800;
    const int screenHeight = 450;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Minesweeper Clone");

    SpriteSheetLoader::GetInstance().LoadSheetsFromIni("resources/spritesheets/sheets.ini");
    m_Board.Sprites = SpriteSheetLoader::GetInstance().GetSheet("Classic");

    SetTargetFPS(60);
}

void Application::Run() {
    while (!WindowShouldClose()) {

        ProcessInputs();

        if (!m_Board.IsGameOver()) {
            m_Board.ProcessInputs();
        }

        BeginDrawing();

        ClearBackground(DARKGRAY);

        // Update available space for board
        m_Board.DisplaySize = { (float)GetScreenWidth(), (float)GetScreenHeight() };

        // Draw board
        m_Board.Render(m_UseVisibility);

        EndDrawing();
    }
    CloseWindow();
}

void Application::ProcessInputs() {
    if (IsKeyPressed(KEY_R)) { // Regenerate the board
        std::shared_ptr<SpriteSheet> currSheet = m_Board.Sprites;
        m_Board = Board{ 30, 16, 99 };
        m_Board.DisplayPosition = { 0, 0 };
        m_Board.Sprites = currSheet;
    }
    if (IsKeyPressed(KEY_V)) { // Toggle visibility check on/off
        m_UseVisibility = !m_UseVisibility;
    }
    if (IsKeyPressed(KEY_F)) { // Change sprite sheet
        m_Sheet = (m_Sheet + 1) % 7;
        if (m_Sheet == 0) {
            m_Board.Sprites = SpriteSheetLoader::GetInstance().GetSheet("Classic");
        }
        else if (m_Sheet == 1) {
            m_Board.Sprites = SpriteSheetLoader::GetInstance().GetSheet("Classic - Alt 1");
        }
        else if (m_Sheet == 2) {
            m_Board.Sprites = SpriteSheetLoader::GetInstance().GetSheet("Classic - Alt 2");
        }
        else if (m_Sheet == 3) {
            m_Board.Sprites = SpriteSheetLoader::GetInstance().GetSheet("Classic - Alt 3");
        }
        else if (m_Sheet == 4) {
            m_Board.Sprites = SpriteSheetLoader::GetInstance().GetSheet("Classic - Monochrome");
        }
        else if (m_Sheet == 5) {
            m_Board.Sprites = SpriteSheetLoader::GetInstance().GetSheet("Dark");
        }
        else if (m_Sheet == 6) {
            m_Board.Sprites = SpriteSheetLoader::GetInstance().GetSheet("Orange");
        }
    }    
}
