#include "raylib.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib basic window");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Bem-Vindo ao Raylib!", 200, 200, 40, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
