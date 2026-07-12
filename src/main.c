#include "../include/main.h"
#include "../include/level.h"
#include "../include/loop.h"
#include "../include/ui.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
GameState webState;
#endif

void unloadGameAssets(Level *level)
{
    for (int i = 0; i < level->countSpawner; i++)
    {
        UnloadTexture(level->spawner[i].texture);
    }
    free(level->spawner);
}

void initGame(Level *level, Events *events, UIHandler *uiHandler, LoopState *state)
{
    createGameLevel(level->levelArr);

    level->countConveyorBelt = 40;
    level->countAdder = 5;
    level->countLeftShift = 3;
    level->countSplitter = 3;
    level->countSpawner = 3;
    prepareSpawner(level);

    events->isGridActive = false;
    events->exitWindow = false;
    events->exitWindowRequested = false;

    loadUIAssets(uiHandler->assets);
    createUI(uiHandler);

    state->events = events;
    state->currentScreen = LOGO;
    state->frameCounter = 0;
    state->level = level;
    state->uiHandler = uiHandler;
}

#if defined(PLATFORM_WEB)
void webLoop(void) { updateDrawFrame(&webState); }
#endif

int main()
{
    // start raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Big Hex Transport");

    Level level;
    Events events;
    Camera2D camera;
    camera.zoom = 1.0f;

    UIHandler uiHandler;
    UIAssets uiAssets;
    uiHandler.assets = &uiAssets;

    LoopState state;

    initGame(&level, &events, &uiHandler, &state);
    state.camera = &camera;

    connectButtonById(state.uiHandler, "start", &startButtonEvent);
    connectButtonById(state.uiHandler, "exit", &exitButtonEvent);
    connectButtonById(state.uiHandler, "pause", &pauseButtonEvent);
    connectButtonById(state.uiHandler, "play", &playButtonEvent);
    connectButtonById(state.uiHandler, "doublePlay", &doublePlayButtonEvent);
    connectButtonById(state.uiHandler, "exitGamePlay", &exitGamePlayButtonEvent);
    connectButtonById(state.uiHandler, "beltButton", &beltButtonEvent);

#if defined(PLATFORM_WEB)
    web_state = state;
    web emscripten_set_main_loop(webLoop, 0, 1);
#else
    SetTargetFPS(60);
    // Main game loop
    while (!events.exitWindow)
    {
        updateDrawFrame(&state);
    }
#endif

    unloadGameAssets(&level);
    CloseWindow();

    return 0;
}
