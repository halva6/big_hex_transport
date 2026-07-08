#include "../include/main.h"
#include <raylib.h>

void create_game_level(int *level)
{
    for (int i = 0; i < LEVEL_WIDTH * LEVEL_HEIGHT; i++)
    {
        level[i] = 0;
    }
}

void print_level(int *level)
{
    for (int i = 0; i < LEVEL_WIDTH * LEVEL_HEIGHT; i++)
    {
        if (i != 0 && i % LEVEL_WIDTH == 0)
        {
            printf("\n");
        }
        printf("%d ", level[i]);
    }
    printf("\n");
}

void draw_grid()
{
    int row = 0;
    for (int col = 0; col < LEVEL_WIDTH; col++)
    {
        for (int row = 0; row < LEVEL_HEIGHT; row++)
        {

            Rectangle rect = {col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            DrawRectangleLinesEx(rect, 0.5f, GRAY);
        }
    }
}

int main()
{
    int level[LEVEL_WIDTH * LEVEL_HEIGHT];
    create_game_level(level);
    // print_level(level);
    // start raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Big Hex Transport");
    SetTargetFPS(TARGET_FPS);

    Image image = LoadImage("assets/face64.png");    // Loaded in CPU memory (RAM)
    Texture2D texture = LoadTextureFromImage(image); // Image converted to texture, GPU memory (VRAM)
    Image image2 = LoadImage("assets/face32.png");   // Loaded in CPU memory (RAM)
    Texture2D texture2 = LoadTextureFromImage(image2);
    Image image3 = LoadImage("assets/face16.png"); // Loaded in CPU memory (RAM)
    Texture2D texture3 = LoadTextureFromImage(image3);
    UnloadImage(image);
    UnloadImage(image2);
    UnloadImage(image3);

    printf("asiouhdiouas \n");

    bool is_grid_on = false;
    while (!WindowShouldClose())
    {
        if (IsKeyReleased(KEY_G))
        {
            is_grid_on = !is_grid_on;
        }

        BeginDrawing();
        if (is_grid_on)
        {
            draw_grid();
        }
        ClearBackground(RAYWHITE);
        DrawTexture(texture, 64, 64, WHITE);
        DrawTexture(texture2, 64, 128, WHITE);
        DrawTexture(texture3, 64, 192, WHITE);
        DrawText("First Window", 500, 100, 32, GRAY);
        DrawFPS(600, 20);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
