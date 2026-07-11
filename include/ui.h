#ifndef UI_H
#define UI_H
#include "main.h"
#include "raylib.h"
#include <sys/types.h>
typedef enum ButtonState {NORMAL=0,HOVER,PRESSED} ButtonState;

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
    u_int fontSize;
    Vector2 pos;
    Color textColor;
    GameScreen screen;

    const char* id;
    bool visible;
}
UIText ;

typedef struct UIButton
{
    // text properties
    char *text;
    u_int fontSize;
    u_int textX;
    u_int textY;
    Color textColor;

    // button properties
    Rectangle rect;
    Color backgroundColorNormal;
    Color backgroundColorHover;
    Color backgroundColorPressed;
    Color lineColor;
    ButtonState buttonState; // 0 -> normal, 1 -> hover, 2 -> pressed
    GameScreen screen;

    const char* id;
    bool visible;
    void (*func) (Events*);
}
UIButton;

typedef struct UISpriteButton
{
    Texture2D buttonTexture;
    Rectangle srcRect;
    Vector2 pos;
    ButtonState buttonState; // 0 -> normal, 1 -> hover, 2 -> pressed
    GameScreen screen;

    const char* id;
    bool visible;
    void (*func) (Events*);
}
UISpriteButton;

typedef struct UISprite
{
    Texture2D texture;
    int x;
    int y;
    GameScreen screen;

    const char* id;
    bool visible;
}
UISprite;

typedef struct UIDialog
{
    char *text;
    u_int fontSize;
    u_int textX;
    u_int textY;
    Color textColor;
    Color fillColor;

    Rectangle rect;

    const char* id;
    bool visible;

}
UIDialog ;

typedef struct UIHandler
{
    UIAssets *assets;

    UIText *texts;
    u_int countTexts;

    UIButton *buttons;
    u_int countButtons;

    UISpriteButton *spriteButtons;
    u_int countSpriteButtons;

    UISprite *sprites;
    u_int countSprites;

    UIDialog *dialogs;
    u_int countDialogs;

}
UIHandler ;

void loadUIAssets(UIAssets *uiAssets);

void createUI(UIHandler *uiHandler);

void renderButtons(UIButton *uiButtons, u_int count,GameScreen screen);

void renderSpriteButtons(UISpriteButton *uiSpriteButtons, u_int count,GameScreen screen);

void renderTexts(UIText *texts, u_int count,GameScreen screen);

void renderSprites(UISprite *sprites, u_int count,GameScreen screen);

void renderDialogs(UIDialog *dialogs, u_int count, GameScreen screen);

void unloadUI(UIHandler *uiHandler);

void updateUiEvents(UIHandler *uiHandler, Events *events, GameScreen screen);

void connectButtonById(UIHandler *uiHandler, const char *id, void (*func) (Events*));

void switchVisiblityById(UIHandler *uiHandler, const char *id, bool visible);
#endif
