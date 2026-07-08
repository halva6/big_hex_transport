#include "../include/game.h"
#include "raymath.h"
void update_inputs(GameState *state)
{
    // key inputs
    if (IsKeyReleased(KEY_G))
    {
        state->inputs->isGridActive = !state->inputs->isGridActive;
    }
    Vector2 mousePos = GetMousePosition();
    if (CheckCollisionPointRec(mousePos, state->events->titleStartButton) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        state->inputs->isGameStarted = true;
    }
    if (CheckCollisionPointRec(mousePos, state->events->titleExitButton) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        state->exitWindowRequested = true;
    }

    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / state->camera->zoom);
        state->camera->target = Vector2Add(state->camera->target, delta);
    }
}

void update_game(GameState *state) {}

void draw_logo_screen(UIAssets *uiAssets)
{
    Vector2 pos = {59, 20};
    DrawTextureV(uiAssets->buildmanFactoryLogo, pos, WHITE);
}

void draw_text_button_centered(UIText *text, Rectangle *buttonRect, int padding, int height)
{
    int textSize = MeasureText(text->text, text->fontSize);
    int centerScreenWidth = (SCREEN_WIDTH / 2) - (textSize / 2);

    buttonRect->x = centerScreenWidth - padding;
    buttonRect->y = height - padding;
    buttonRect->width = textSize + (padding * 2);
    buttonRect->height = text->fontSize + (padding * 2);

    DrawRectangleLinesEx(*buttonRect, 2.0f, BLACK);

    DrawText(text->text, centerScreenWidth, height, text->fontSize, text->textColor);
}

void draw_text_rect_centered(UIText *text, int padding, int height, bool fill, Color color)
{
    int textSize = MeasureText(text->text, text->fontSize);
    int centerScreenWidth = (SCREEN_WIDTH / 2) - (textSize / 2);

    Rectangle rect;
    rect.x = centerScreenWidth - padding;
    rect.y = height - padding;
    rect.width = textSize + (padding * 2);
    rect.height = text->fontSize + (padding * 2);

    if (!fill)
    {
        DrawRectangleLinesEx(rect, 2.0f, color);
    }
    else
    {
        DrawRectangleRec(rect, color);
    }

    DrawText(text->text, centerScreenWidth, height, text->fontSize, text->textColor);
}

void draw_text_vertical_center(UIText *text, int height)
{
    int textSize = MeasureText(text->text, text->fontSize);
    int centerScreenWidth = (SCREEN_WIDTH / 2) - (textSize / 2);
    DrawText(text->text, centerScreenWidth, height, text->fontSize, BLACK);
}

void draw_title_screen(GameState *state)
{
    UIText title = {"Big Hex Transport", 50, BLACK};
    UIText start = {"Start Game", 30, BLACK};
    UIText exit = {"Exit", 30, BLACK};
    Rectangle startRect = {0, 0, 0, 0};
    Rectangle exitRect = {0, 0, 0, 0};
    draw_text_vertical_center(&title, 100);
    draw_text_button_centered(&start, &startRect, 10, 320);
    draw_text_button_centered(&exit, &exitRect, 10, 420);
    state->events->titleStartButton = startRect;
    state->events->titleExitButton = exitRect;
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

void draw_game_ui(GameState *state)
{
    DrawTexture(state->uiAssets->stylishUiEnchancement, 0, 0, WHITE);
    DrawTexture(state->uiAssets->pause, 32, 16, WHITE);
    DrawTexture(state->uiAssets->play, 96, 16, WHITE);
    DrawTexture(state->uiAssets->doublePlay, 160, 16, WHITE);
}

void draw_game_screen(GameState *state)
{
    BeginMode2D(*(state->camera));
    if (state->inputs->isGridActive)
    {
        draw_grid();
    }
    DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 20, MAROON);
    EndMode2D();

    draw_game_ui(state);
    DrawFPS(600, 20);
}

void draw_ending_screen() {}

void update_camera(GameState *state)
{
    // Zoom based on mouse wheel
    float wheel = GetMouseWheelMove();
    if (wheel != 0)
    {
        // Get the world point that is under the mouse
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *(state->camera));

        // Set the offset to where the mouse is
        state->camera->offset = GetMousePosition();

        // Set the target to match, so that the camera maps the world space point
        // under the cursor to the screen space point under the cursor at any zoom
        state->camera->target = mouseWorldPos;

        // Zoom increment
        // Uses log scaling to provide consistent zoom speed
        float scale = 0.2f * wheel;
        // the last to numbers are the min and the max
        state->camera->zoom = Clamp(expf(logf(state->camera->zoom) + scale), 1.0f, 2.0f);
    }
}

void update_draw_frame(GameState *state)
{
    update_inputs(state);
    update_camera(state);
    switch (state->currentScreen)
    {
    case LOGO:
    {
        state->frameCounter++;

        if (state->frameCounter > 60)
        {
            state->currentScreen = TITLE;
        }
    }
    break;
    case TITLE:
    {
        if (state->inputs->isGameStarted)
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
        draw_logo_screen(state->uiAssets);
    }
    break;
    case TITLE:
    {
        draw_title_screen(state);
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
    if (state->exitWindowRequested)
    {
        UIText closingText = {"Are you sure you want to exit program? [Y/N]", 20, WHITE};
        draw_text_rect_centered(&closingText, 10, SCREEN_HEIGHT / 2 - closingText.fontSize, true, RED);
    }
    EndDrawing();
}
