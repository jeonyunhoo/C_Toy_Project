#include "raylib.h"
#include "player.h"

int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "My RPG Game");
    SetTargetFPS(60);

    Player player;
    InitPlayer(&player);

    while (!WindowShouldClose()) {

        UpdatePlayer(&player);

        BeginDrawing();
        {
            ClearBackground(RAYWHITE);

            DrawText("Use arrow keys to move!", 10, 10, 20, DARKGRAY);

            DrawPlayer(player);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}