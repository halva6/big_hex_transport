#include "../include/ui.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void loadUIAssets(UIAssets *uiAssets)
{
    uiAssets->buildmanFactoryLogo = LoadTexture("assets/ui/BuildmanFactoryIcon.png");
    uiAssets->pause = LoadTexture("assets/ui/Pause.png");
    uiAssets->play = LoadTexture("assets/ui/Play.png");
    uiAssets->doublePlay = LoadTexture("assets/ui/DoublePlay.png");
    uiAssets->stylishUiEnchancement = LoadTexture("assets/ui/Stylish_UI_enhancement.png");
    uiAssets->exitGamePlay = LoadTexture("assets/ui/Exit.png");
}

void calcCenteredRect(u_int x, u_int y, u_int textSize, u_int fontsize, Rectangle *rect, u_int padding)
{
    rect->x = x - padding;
    rect->y = y - padding;
    rect->width = textSize + (padding * 2);
    rect->height = fontsize + (padding * 2);
}

void calcRectButtonCentered(UIButton *button, Rectangle *rect, int padding)
{
    int textSize = MeasureText(button->text, button->fontSize);
    button->textX = (SCREEN_WIDTH / 2) - (textSize / 2);
    calcCenteredRect(button->textX, button->textY, textSize, button->fontSize, rect, padding);
}

void calcRectDialogCentered(UIDialog *dialog, Rectangle *rect, int padding)
{
    int textSize = MeasureText(dialog->text, dialog->fontSize);
    dialog->textX = (SCREEN_WIDTH / 2) - (textSize / 2);
    calcCenteredRect(dialog->textX, dialog->textY, textSize, dialog->fontSize, rect, padding);
}

void calcTextCentered(char *text, u_int fontSize, Vector2 *pos)
{
    int textSize = MeasureText(text, fontSize);
    pos->x = (int)(SCREEN_WIDTH / 2) - (int)(textSize / 2);
}

void createUI(UIHandler *uiHandler)
{
    // texts
    uiHandler->countTexts = 2;
    Vector2 posTitle = {0, 50};
    UIText title = {"Big Hex Transport", 50, posTitle, BLACK, TITLE, "title", true};
    calcTextCentered(title.text, title.fontSize, &posTitle);
    title.pos = posTitle;

    Vector2 posDescription = {0, 100};
    UIText description = {"Try your best and merge all hex numbers!", 25, posDescription, BLACK, TITLE, "des", true};
    calcTextCentered(description.text, description.fontSize, &posDescription);
    description.pos = posDescription;
    uiHandler->texts = malloc(uiHandler->countTexts * sizeof(UIText));
    uiHandler->texts[0] = title;
    uiHandler->texts[1] = description;

    // text buttons
    uiHandler->countButtons = 2;
    Rectangle startButtonRect;
    UIButton startButton = {"Start Game", 30, 0, 200, BLACK, startButtonRect, WHITE, LIGHTGRAY, GRAY, BLACK, NORMAL, TITLE, "start", true};
    calcRectButtonCentered(&startButton, &startButtonRect, 10);
    startButton.rect = startButtonRect;

    Rectangle exitButtonRect;
    UIButton exitButton = {"Exit", 30, 0, 300, BLACK, exitButtonRect, WHITE, LIGHTGRAY, GRAY, BLACK, NORMAL, TITLE, "exit", true};
    calcRectButtonCentered(&exitButton, &exitButtonRect, 10);
    exitButton.rect = exitButtonRect;
    uiHandler->buttons = malloc(uiHandler->countButtons * sizeof(UIButton));
    uiHandler->buttons[0] = startButton;
    uiHandler->buttons[1] = exitButton;

    // sprite buttons
    uiHandler->countSpriteButtons = 4;
    // calculate uiHandler->assets->pause.height / 3 because there are three states of the button
    Rectangle pauseButtonRect = {0, 0, uiHandler->assets->pause.width, (int)(uiHandler->assets->pause.height / 3)};
    UISpriteButton pauseButton = {uiHandler->assets->pause, pauseButtonRect, (Vector2){32, 16}, NORMAL, GAMEPLAY, "pause", true};

    Rectangle playButtonRect = {0, 0, uiHandler->assets->play.width, (int)(uiHandler->assets->play.height / 3)};
    UISpriteButton playButton = {uiHandler->assets->play, playButtonRect, (Vector2){96, 16}, NORMAL, GAMEPLAY, "play", true};

    Rectangle doublePlayButtonRect = {0, 0, uiHandler->assets->doublePlay.width, (int)(uiHandler->assets->doublePlay.height / 3)};
    UISpriteButton doublePlayButton = {uiHandler->assets->doublePlay, doublePlayButtonRect, (Vector2){160, 16}, NORMAL, GAMEPLAY, "doublePlay", true};

    Rectangle exitGameButtonRect = {0, 0, uiHandler->assets->exitGamePlay.width, (int)(uiHandler->assets->exitGamePlay.height / 3)};
    UISpriteButton exitGameButton = {uiHandler->assets->exitGamePlay, exitGameButtonRect, (Vector2){430, 16}, NORMAL, GAMEPLAY, "exitGamePlay", true};
    uiHandler->spriteButtons = malloc(uiHandler->countSpriteButtons * sizeof(UISpriteButton));
    uiHandler->spriteButtons[0] = pauseButton;
    uiHandler->spriteButtons[1] = playButton;
    uiHandler->spriteButtons[2] = doublePlayButton;
    uiHandler->spriteButtons[3] = exitGameButton;

    // sprites (only ui sprites)
    uiHandler->countSprites = 2;
    UISprite randomBeautifulThing = {uiHandler->assets->stylishUiEnchancement, 0, 0, GAMEPLAY, "thing", true};
    UISprite logo = {uiHandler->assets->buildmanFactoryLogo, 59, 20, LOGO, "logo", true};
    uiHandler->sprites = malloc(uiHandler->countSprites * sizeof(UISprite));
    uiHandler->sprites[0] = randomBeautifulThing;
    uiHandler->sprites[1] = logo;

    uiHandler->countDialogs = 2;
    Rectangle dialogRect;
    UIDialog closeDialog = {"Are you sure you want to exit program? [Y/N]", 20, 0, SCREEN_HEIGHT / 2, WHITE, RED, dialogRect, "closeDialog", false};
    calcRectDialogCentered(&closeDialog, &dialogRect, 10);
    closeDialog.rect = dialogRect;

    UIDialog backToMenuDialog = {
        "Are you sure you want to return to the main menu? [Y/N]", 20, 0, SCREEN_HEIGHT / 2, WHITE, RED, dialogRect, "backToMenu", false};
    calcRectDialogCentered(&backToMenuDialog, &dialogRect, 10);
    backToMenuDialog.rect = dialogRect;
    uiHandler->dialogs = malloc(uiHandler->countDialogs * sizeof(UIDialog));
    uiHandler->dialogs[0] = closeDialog;
    uiHandler->dialogs[1] = backToMenuDialog;
}

void renderButtons(UIButton *uiButtons, u_int count, GameScreen screen)
{
    for (int i = 0; i < count; i++)
    {
        if (screen == uiButtons[i].screen && uiButtons[i].visible)
        {
            switch (uiButtons[i].buttonState)
            {
            case NORMAL:
                DrawRectangleRec(uiButtons[i].rect, uiButtons[i].backgroundColorNormal);
                break;
            case HOVER:
                DrawRectangleRec(uiButtons[i].rect, uiButtons[i].backgroundColorHover);
                break;
            case PRESSED:
                DrawRectangleRec(uiButtons[i].rect, uiButtons[i].backgroundColorPressed);
                break;
            }

            DrawRectangleLinesEx(uiButtons[i].rect, 2.0f, uiButtons[i].lineColor);
            DrawText(uiButtons[i].text, uiButtons[i].textX, uiButtons[i].textY, uiButtons[i].fontSize, uiButtons[i].textColor);
        }
    }
}

void renderSpriteButtons(UISpriteButton *uiSpriteButtons, u_int count, GameScreen screen)
{
    for (int i = 0; i < count; i++)
    {
        if (uiSpriteButtons[i].screen == screen && uiSpriteButtons[i].visible)
        {
            uiSpriteButtons[i].srcRect.y = (float)(uiSpriteButtons[i].buttonTexture.height / 3.0f) * uiSpriteButtons[i].buttonState;
            DrawTextureRec(uiSpriteButtons[i].buttonTexture, uiSpriteButtons[i].srcRect, uiSpriteButtons[i].pos, WHITE);
        }
    }
}

void renderTexts(UIText *texts, u_int count, GameScreen screen)
{
    for (int i = 0; i < count; i++)
    {
        if (texts[i].screen == screen && texts[i].visible)
        {
            DrawText(texts[i].text, texts[i].pos.x, texts[i].pos.y, texts[i].fontSize, texts[i].textColor);
        }
    }
}
void renderSprites(UISprite *sprites, u_int count, GameScreen screen)
{
    for (int i = 0; i < count; i++)
    {
        if (sprites[i].screen == screen && sprites[i].visible)
        {
            DrawTexture(sprites[i].texture, sprites[i].x, sprites[i].y, WHITE);
        }
    }
}

void renderDialogs(UIDialog *dialogs, u_int count, GameScreen screen)
{
    for (int i = 0; i < count; i++)
    {
        if (dialogs[i].visible)
        {
            DrawRectangleRec(dialogs[i].rect, dialogs->fillColor);
            DrawText(dialogs[i].text, dialogs[i].textX, dialogs[i].textY, dialogs[i].fontSize, dialogs[i].textColor);
        }
    }
}

void unloadUI(UIHandler *uiHandler)
{
    free(uiHandler->texts);
    uiHandler->countTexts = 0;

    free(uiHandler->buttons);
    uiHandler->countButtons = 0;

    free(uiHandler->spriteButtons);
    uiHandler->countSpriteButtons = 0;

    free(uiHandler->sprites);
    uiHandler->countSprites = 0;

    free(uiHandler->dialogs);
    uiHandler->countDialogs = 0;

    UnloadTexture(uiHandler->assets->buildmanFactoryLogo);
    UnloadTexture(uiHandler->assets->pause);
    UnloadTexture(uiHandler->assets->play);
    UnloadTexture(uiHandler->assets->doublePlay);
    UnloadTexture(uiHandler->assets->stylishUiEnchancement);
}

void updateUiEvents(UIHandler *uiHandler, Events *events, GameScreen screen)
{
    Vector2 mousePos = GetMousePosition();
    for (int i = 0; i < uiHandler->countButtons; i++)
    {
        if (uiHandler->buttons[i].screen == screen && uiHandler->buttons[i].visible)
        {
            if (CheckCollisionPointRec(mousePos, uiHandler->buttons[i].rect) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                uiHandler->buttons[i].buttonState = PRESSED;
            }
            else if (CheckCollisionPointRec(mousePos, uiHandler->buttons[i].rect) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                uiHandler->buttons[i].func(events);
            }
            else if (CheckCollisionPointRec(mousePos, uiHandler->buttons[i].rect))
            {
                uiHandler->buttons[i].buttonState = HOVER;
            }
            else
            {
                uiHandler->buttons[i].buttonState = NORMAL;
            }
        }
    }

    for (int i = 0; i < uiHandler->countSpriteButtons; i++)
    {
        if (uiHandler->spriteButtons[i].screen == screen && uiHandler->spriteButtons[i].visible)
        {
            Rectangle spriteRect = {uiHandler->spriteButtons[i].pos.x, uiHandler->spriteButtons[i].pos.y,
                                    uiHandler->spriteButtons[i].buttonTexture.width, uiHandler->spriteButtons[i].buttonTexture.height / 3.0f};
            if (CheckCollisionPointRec(mousePos, spriteRect) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                uiHandler->spriteButtons[i].buttonState = PRESSED;
            }
            else if (CheckCollisionPointRec(mousePos, spriteRect) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                uiHandler->spriteButtons[i].func(events);
            }
            else if (CheckCollisionPointRec(mousePos, spriteRect))
            {
                uiHandler->spriteButtons[i].buttonState = HOVER;
            }
            else
            {
                uiHandler->spriteButtons[i].buttonState = NORMAL;
            }
        }
    }
}

void connectButtonById(UIHandler *uiHandler, const char *id, void (*func)(Events *))
{
    for (int i = 0; i < uiHandler->countButtons; i++)
    {
        if (strcmp(uiHandler->buttons[i].id, id) == 0)
        {
            uiHandler->buttons[i].func = func;
            return;
        }
    }

    for (int i = 0; i < uiHandler->countSpriteButtons; i++)
    {
        if (strcmp(uiHandler->spriteButtons[i].id, id) == 0)
        {
            uiHandler->spriteButtons[i].func = func;
            return;
        }
    }
}

void switchVisiblityById(UIHandler *uiHandler, const char *id, bool visible)
{
    for (int i = 0; i < uiHandler->countDialogs; i++)
    {
        if (strcmp(uiHandler->dialogs[i].id, id) == 0)
        {
            uiHandler->dialogs[i].visible = visible;
            return;
        }
    }

    for (int i = 0; i < uiHandler->countSprites; i++)
    {
        if (strcmp(uiHandler->sprites[i].id, id) == 0)
        {
            uiHandler->sprites[i].visible = visible;
            return;
        }
    }

    for (int i = 0; i < uiHandler->countTexts; i++)
    {
        if (strcmp(uiHandler->texts[i].id, id) == 0)
        {
            uiHandler->texts[i].visible = visible;
            return;
        }
    }
    for (int i = 0; i < uiHandler->countButtons; i++)
    {
        if (strcmp(uiHandler->buttons[i].id, id) == 0)
        {
            uiHandler->buttons[i].visible = visible;
            return;
        }
    }

    for (int i = 0; i < uiHandler->countSpriteButtons; i++)
    {
        if (strcmp(uiHandler->spriteButtons[i].id, id) == 0)
        {
            uiHandler->spriteButtons[i].visible = visible;
            return;
        }
    }
}
