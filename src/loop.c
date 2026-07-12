#include "../include/loop.h"
#include "../include/ui.h"
#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stdbool.h>
#include <stdio.h>

void updateInputs(LoopState *state)
{
    // key inputs
    if (IsKeyReleased(KEY_G))
    {
        state->events->isGridActive = !state->events->isGridActive;
    }

    Vector2 mousePos = GetMousePosition();
    // Translate based on mouse right click
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f / state->camera->zoom);
        state->camera->target = Vector2Add(state->camera->target, delta);
    }
}

void startButtonEvent(Events *events) { events->isGameStarted = true; }

void exitButtonEvent(Events *events) { events->exitWindowRequested = true; }

void pauseButtonEvent(Events *events) { fprintf(stderr, "pause \n"); }
void playButtonEvent(Events *events) { fprintf(stderr, "play \n"); }
void doublePlayButtonEvent(Events *events) { fprintf(stderr, "double play \n"); }

void exitGamePlayButtonEvent(Events *events) { events->exitGameRequested = true; }

void beltButtonEvent(Events *events) { fprintf(stderr, "belt button \n"); }

void drawLogoScreen(UIAssets *uiAssets) {}

void updateGame(LoopState *state) {}

void drawTitleScreen(LoopState *state) {}

void drawGrid()
{
    for (int i = 0; i < LEVEL_WIDTH + 1; i++)
    {
        DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, LEVEL_WIDTH * CELL_SIZE, GRAY);
    }

    for (int i = 0; i < LEVEL_HEIGHT + 1; i++)
    {
        DrawLine(0, i * CELL_SIZE, LEVEL_HEIGHT * CELL_SIZE, i * CELL_SIZE, GRAY);
    }
}

void drawGameScreen(LoopState *state)
{
    BeginMode2D(*(state->camera));
    if (state->events->isGridActive)
    {
        drawGrid();
    }

    EndMode2D();
    DrawFPS(600, 20);
}

void draw_ending_screen() {}

void updateCamera(LoopState *state)
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
        state->camera->zoom = Clamp(expf(logf(state->camera->zoom) + scale), 0.125f, 2.5f);
    }
}

void handleExits(LoopState *state, Events *events)
{
    if (IsKeyPressed(KEY_ESCAPE) && state->currentScreen == GAMEPLAY)
    {
        events->exitGameRequested = true;
    }
    else if (WindowShouldClose() || (IsKeyPressed(KEY_ESCAPE) && state->currentScreen == TITLE))
    {
        events->exitWindowRequested = true;
    }

    if (events->exitWindowRequested)
    {
        // A request for close window has been issued, we can save data before closing
        // or just show a message asking for confirmation
        if (IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_Z))
        {
            events->exitWindow = true;
        }
        else if (IsKeyPressed(KEY_N))
        {
            switchVisiblityById(state->uiHandler, "closeDialog", false);
            events->exitWindowRequested = false;
        }
    }

    if (events->exitGameRequested)
    {
        if (IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_Z))
        {
            state->currentScreen = TITLE;
            events->isGameStarted = false;
            events->exitGameRequested = false;
            switchVisiblityById(state->uiHandler, "backToMenu", false);
        }
        else if (IsKeyPressed(KEY_N))
        {
            switchVisiblityById(state->uiHandler, "backToMenu", false);
            events->exitGameRequested = false;
        }
    }
}

void updateDrawFrame(LoopState *state)
{
    updateInputs(state);
    updateCamera(state);
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
        if (state->events->isGameStarted)
        {
            state->currentScreen = GAMEPLAY;
        }
    }
    break;
    case GAMEPLAY:
    {
        updateGame(state);
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

    updateUiEvents(state->uiHandler, state->events, state->currentScreen);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (state->currentScreen)
    {
    case LOGO:

        break;
    case TITLE:

        drawTitleScreen(state);

        break;
    case GAMEPLAY:

        drawGameScreen(state);

        break;
    case ENDING:

        draw_ending_screen();

        break;
    default:
        break;
    }

    renderSprites(state->uiHandler->sprites, state->uiHandler->countSprites, state->currentScreen);
    renderTexts(state->uiHandler->texts, state->uiHandler->countTexts, state->currentScreen);
    renderButtons(state->uiHandler->buttons, state->uiHandler->countButtons, state->currentScreen);
    renderSpriteButtons(state->uiHandler->spriteButtons, state->uiHandler->countSpriteButtons, state->currentScreen);
    renderDialogs(state->uiHandler->dialogs, state->uiHandler->countDialogs, state->currentScreen);
    EndDrawing();

    handleExits(state, state->events);

    if (state->events->exitWindowRequested)
    {
        switchVisiblityById(state->uiHandler, "closeDialog", true);
    }
    if (state->events->exitGameRequested)
    {
        switchVisiblityById(state->uiHandler, "backToMenu", true);
    }
}
