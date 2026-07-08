#include "../include/main.h"
#include "../include/game.h"
#include "../include/level.h"
#include <raylib.h>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
GameState webState;
#endif

void loadAssets(UIAssets *uiAssets)
{
    uiAssets->buildmanFactoryLogo = LoadTexture("assets/ui/BuildmanFactoryIcon.png");
    uiAssets->pause = LoadTexture("assets/ui/Pause.png");
    uiAssets->play = LoadTexture("assets/ui/Play.png");
    uiAssets->doublePlay = LoadTexture("assets/ui/DoublePlay.png");
    uiAssets->stylishUiEnchancement = LoadTexture("assets/ui/Stylish_UI_enhancement.png");
}

void unload_assets(UIAssets *uiAssets)
{
    UnloadTexture(uiAssets->buildmanFactoryLogo);
    UnloadTexture(uiAssets->pause);
    UnloadTexture(uiAssets->play);
    UnloadTexture(uiAssets->doublePlay);
    UnloadTexture(uiAssets->stylishUiEnchancement);
};
void init_game(Level *level, GameInputs *inputs, GameState *state)
{
    create_game_level(level->level);
    // print_level(level->level);

    level->count_conveyor_belt = 40;
    level->count_adder = 5;
    level->count_left_shift = 3;
    level->count_splitter = 3;
    level->count_spawner = 2;

    inputs->isGridActive = false;

    state->inputs = inputs;
    state->currentScreen = LOGO;
    state->frameCounter = 0;
    state->level = level;
    state->exitWindowRequested = false;
    state->exitWindow = false;
}

#if defined(PLATFORM_WEB)
void web_loop(void) { update_draw_frame(&webState); }
#endif

int main()
{
    // start raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Big Hex Transport");

    UIAssets uiAssets;
    loadAssets(&uiAssets);

    Level level;
    GameInputs inputs;
    ButtonEvents events;
    Camera2D camera;
    camera.zoom = 1.0f;
    GameState state;

    init_game(&level, &inputs, &state);
    state.uiAssets = &uiAssets;
    state.events = &events;
    state.camera = &camera;

#if defined(PLATFORM_WEB)
    web_state = state;
    web emscripten_set_main_loop(web_loop, 0, 1);
#else
    SetTargetFPS(60);
    // Main game loop
    while (!state.exitWindow)
    {
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
        {
            state.exitWindowRequested = true;
        }
        if (state.exitWindowRequested)
        {
            // A request for close window has been issued, we can save data before closing
            // or just show a message asking for confirmation
            if (IsKeyPressed(KEY_Y) || IsKeyPressed(KEY_Z))
            {
                state.exitWindow = true;
            }
            else if (IsKeyPressed(KEY_N))
            {
                state.exitWindowRequested = false;
            }
        }
        update_draw_frame(&state);
    }
#endif

    unload_assets(&uiAssets);
    CloseWindow();

    return 0;
}
