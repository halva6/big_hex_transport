#ifndef LOOP_H
#define LOOP_H
#include "../include/ui.h"
#include "main.h"
#include "raylib.h"

typedef struct LoopState
{
    Events *events;
    GameScreen currentScreen;
    unsigned int frameCounter;
    Camera2D *camera;
    UIHandler *uiHandler;
}LoopState;

void updateDrawFrame(LoopState *state);

void startButtonEvent(Events *events);
void exitButtonEvent(Events *events);
void pauseButtonEvent(Events *events);
void playButtonEvent(Events *events);
void doublePlayButtonEvent(Events *events);
void exitGamePlayButtonEvent(Events *events);
void beltButtonEvent(Events *events);

#endif
