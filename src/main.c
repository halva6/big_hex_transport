#include "../include/main.h"
#include "../include/game.h"
#include "../include/level.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
GameState webState;
#endif

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
}

#if defined(PLATFORM_WEB)
void web_loop(void) { update_draw_frame(&webState); }
#endif

int main()
{
    // start raylib
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Big Hex Transport");

    Level level;
    GameInputs inputs;
    GameState state;

    init_game(&level, &inputs, &state);

#if defined(PLATFORM_WEB)
    web_state = state;
    web emscripten_set_main_loop(web_loop, 0, 1);
#else
    SetTargetFPS(60);
    // Main game loop
    while (!WindowShouldClose())
    {
        update_draw_frame(&state);
    }
#endif

    CloseWindow();

    return 0;
}
