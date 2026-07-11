#ifndef GAME_H
#define GAME_H
#include "../include/level.h"
#include "../include/ui.h"
#include "main.h"
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

void startButtonEvent(Events *events);
void exitButtonEvent(Events *events);
void pauseButtonEvent(Events *events);
void playButtonEvent(Events *events);
void doublePlayButtonEvent(Events *events);
void exitGamePlayButtonEvent(Events *events);

#endif
