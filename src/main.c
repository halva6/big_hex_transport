#include "../include/main.h"
#include "../include/loop.h"
#include "../include/ui.h"
#include <raylib.h>
#include <stdbool.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
GameState webState;
#endif

void initGame(Events *events, UIHandler *uiHandler, LoopState *state)
{

    events->isGridActive = false;
    events->exitWindow = false;
    events->exitWindowRequested = false;

    loadUIAssets(uiHandler->assets);
    createUI(uiHandler);

    state->events = events;
    state->currentScreen = LOGO;
    state->frameCounter = 0;
    state->uiHandler = uiHandler;
}

#if defined(PLATFORM_WEB)
void webLoop(void) { updateDrawFrame(&webState); }
#endif

int main()
{
    // start raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Big Hex Transport");

    Events events;
    Camera2D camera;
    camera.zoom = 1.0f;

    UIHandler uiHandler;
    UIAssets uiAssets;
    uiHandler.assets = &uiAssets;

    LoopState state;

    initGame(&events, &uiHandler, &state);
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

    unloadUI(&uiHandler);
    CloseWindow();

    return 0;
}
