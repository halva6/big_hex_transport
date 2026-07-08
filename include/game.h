#ifndef GAME_H
#define GAME_H
#include "../include/level.h"

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
typedef struct GameInputs
{
    bool isGridActive;
} GameInputs;

typedef struct GameState
{
    GameInputs *inputs;
    GameScreen currentScreen;
    unsigned int frameCounter;
    Level *level;
}GameState;

void update_draw_frame(GameState *state);

#endif
