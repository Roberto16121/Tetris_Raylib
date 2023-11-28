#include <iostream>
#include <raylib.h>
#include "game.h"
#include "colors.h"
double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() {


    const int screenWidth = 500;
    const int screenHeight = 620;

    InitWindow(screenWidth, screenHeight, "Tetris_Raylib");
    Game game = Game();

    SetTargetFPS(60);

    Font font = LoadFontEx("Roboto-Regular.ttf", 64, 0, 0);

    while (WindowShouldClose() == false) {
        game.HandleInput();
        if (EventTriggered(0.4))
        {
            game.MoveBlockDown();
        }


        BeginDrawing();
        ClearBackground(darkBlue);

        DrawTextEx(font, "Score", { 365,15 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320,55,170,60 }, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf_s(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
      
        DrawTextEx(font, scoreText, { 320+(170-textSize.x)/2,65}, 38, 2, WHITE);

        DrawTextEx(font, "High Score", { 325,120 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320,160,170,60 }, 0.3, 6, lightBlue);

        char highText[100];
        sprintf_s(highText, "%d", game.hightScore);
        if(std::strlen(highText) > 5)
        {
            textSize = MeasureTextEx(font, highText, 30, 2);
            DrawTextEx(font, highText, { 320 + (170 - textSize.x) / 2,160 }, 30, 2, WHITE);
        }
        else
        {
            textSize = MeasureTextEx(font, highText, 38, 2);
            DrawTextEx(font, highText, { 320 + (170 - textSize.x) / 2,160 }, 38, 2, WHITE);
        }

        


        DrawTextEx(font, "Next", { 370,225 }, 38, 2, WHITE);
        DrawRectangleRounded({ 320,275,170,180 }, 0.3, 6, lightBlue);

        if(game.GameOver)
            DrawTextEx(font, "GAME OVER", { 320,450 }, 30, 2, WHITE);
       

        game.Draw();


        EndDrawing();
    }

    CloseWindow();
    return 0;
}