#ifndef GAME_H
#define GAME_H
#include "../include/level.h"
#include <raylib.h>

typedef struct UIAssets
{
    Texture2D buildmanFactoryLogo;
    Texture2D play;
    Texture2D pause;
    Texture2D doublePlay;
    Texture2D stylishUiEnchancement;
}
UIAssets;

typedef struct UIText
{
    char *text;
    int fontSize;
    Color textColor;
}
UIText ;

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;
typedef struct GameInputs
{
    bool isGridActive;
    bool isGameStarted;
    bool isPaused;
    bool isPlayed;
    bool isDoublePlayed;
} GameInputs;

typedef struct ButtonEvents
{
    Rectangle titleStartButton;
    Rectangle titleExitButton;
    Rectangle playButton;
    Rectangle pauseButton;
    Rectangle doublePlayButton;
}
ButtonEvents;

typedef struct GameState
{
    GameInputs *inputs;
    ButtonEvents *events;
    GameScreen currentScreen;
    unsigned int frameCounter;
    Level *level;
    UIAssets *uiAssets;
    bool exitWindowRequested;
    bool exitWindow;
}GameState;

void update_draw_frame(GameState *state);

#endif
