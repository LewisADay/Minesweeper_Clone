
#include "Application.h"

#include <raylib.h>
#include <LoggingAD/LoggingAD.h>

#include "Board.h"
#include "SpriteSheetLoader.h"

Application::Application()
    : m_CurrentScene(TITLE), m_Board(30, 16, 99)
{
    LoggingAD::SetConfig({ .OutputLevel = LoggingAD::LogLevel::Trace });
        
    const int screenWidth = 800;
    const int screenHeight = 450;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Minesweeper Clone");

    SpriteSheetLoader::GetInstance().LoadSheetsFromIni("resources/spritesheets/sheets.ini");
    m_SpriteSheet = SpriteSheetLoader::GetInstance().GetSheet("Classic");

    SetTargetFPS(60);
}

void Application::Run() {
    bool useVisibility = true;
    int sheet = 0;
    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_R)) { // Regenerate the board
            m_Board = Board{ 30, 16, 99 };
        }
        if (IsKeyPressed(KEY_V)) { // Toggle visibility check on/off
            useVisibility = !useVisibility;
        }
        if (IsKeyPressed(KEY_F)) { // Change sprite sheet
            sheet = (sheet + 1) % 7;
            if (sheet == 0) {
                m_SpriteSheet = SpriteSheetLoader::GetInstance().GetSheet("Classic");
            }
            else if (sheet == 1) {
                m_SpriteSheet = SpriteSheetLoader::GetInstance().GetSheet("Classic - Alt 1");
            }
            else if (sheet == 2) {
                m_SpriteSheet = SpriteSheetLoader::GetInstance().GetSheet("Classic - Alt 2");
            }
            else if (sheet == 3) {
                m_SpriteSheet = SpriteSheetLoader::GetInstance().GetSheet("Classic - Alt 3");
            }
            else if (sheet == 4) {
                m_SpriteSheet = SpriteSheetLoader::GetInstance().GetSheet("Classic - Monochrome");
            }
            else if (sheet == 5) {
                m_SpriteSheet = SpriteSheetLoader::GetInstance().GetSheet("Dark");
            }
            else if (sheet == 6) {
                m_SpriteSheet = SpriteSheetLoader::GetInstance().GetSheet("Orange");
            }
        }

        BeginDrawing();

        ClearBackground(DARKGRAY);

        // Draw board
        m_Board.Render({ 0, 0 }, { (float)GetScreenWidth(), (float)GetScreenHeight() }, *m_SpriteSheet, useVisibility);

        EndDrawing();
    }
    CloseWindow();
}
