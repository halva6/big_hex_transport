#ifndef MAIN_H
#define MAIN_H
#include "raylib.h"
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 720
#define SCREEN_HEIGHT 720
#define TARGET_FPS 60

#define CELL_SIZE 20
#define LEVEL_WIDTH 100
#define LEVEL_HEIGHT 100

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

typedef struct Events
{
    bool isGridActive;
    bool isGameStarted;
    bool isPaused;
    bool isPlayed;
    bool isDoublePlayed;
    bool exitWindowRequested;
    bool exitWindow;
    bool exitGameRequested;
} Events;

int main();
#endif
