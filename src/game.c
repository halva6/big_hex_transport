#include "../include/game.h"

void update_inputs(GameInputs *inputs)
{
    // key inputs
    if (IsKeyReleased(KEY_G))
    {
        inputs->isGridActive = !inputs->isGridActive;
    }
}

void update_game(GameState *state) { update_inputs(state->inputs); }

void draw_logo_screen() { DrawText("Logo", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, BLACK); }

void draw_title_screen() { DrawText("Title", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, BLACK); }

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

void draw_game_screen(GameState *state)
{
    if (state->inputs->isGridActive)
    {
        draw_grid();
    }
    DrawFPS(600, 20);
}

void draw_ending_screen() {}

void update_draw_frame(GameState *state)
{
    switch (state->currentScreen)
    {
    case LOGO:
    {
        state->frameCounter++;

        if (state->frameCounter > 60)
        {
            state->currentScreen = TITLE;
            printf("Title");
        }
    }
    break;
    case TITLE:
    {
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            state->currentScreen = GAMEPLAY;
        }
    }
    break;
    case GAMEPLAY:
    {
        update_game(state);
    }
    break;
    case ENDING:
    {
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            state->currentScreen = TITLE;
        }
    }
    break;
    default:
        break;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    switch (state->currentScreen)
    {
    case LOGO:
    {
        draw_logo_screen();
    }
    break;
    case TITLE:
    {
        draw_title_screen();
    }
    break;
    case GAMEPLAY:
    {
        draw_game_screen(state);
    }
    break;
    case ENDING:
    {
        draw_ending_screen();
    }
    break;
    default:
        break;
    }
    EndDrawing();
}
