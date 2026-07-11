#ifndef GAME_H
#define GAME_H
#include "../include/level.h"
#include "../include/ui.h"
#include "raylib.h"

typedef struct GameState
{
    Events *events;
    GameScreen currentScreen;
    unsigned int frameCounter;
    Level *level;
    Camera2D *camera;
    UIHandler *uiHandler;
}GameState;

void update_draw_frame(GameState *state);

#endif
