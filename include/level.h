#ifndef LEVEL_H
#define LEVEL_H
#include "../include/main.h"
#include <raylib.h>
#include <sys/types.h>

typedef struct ConveyorBelt
{
    Vector2 pos;
    Texture2D texture;
}
ConveyorBelt;

typedef struct Spawner
{

    Texture2D texture;
    u_int x;
    u_int y;
    u_int width;
    u_int height;
}
Spawner;

typedef struct Level
{
    u_int levelArr[LEVEL_WIDTH * LEVEL_HEIGHT];
    u_int countConveyorBelt;
    u_int countAdder;
    u_int countLeftShift;
    u_int countSplitter;
    u_int countSpawner;
    Spawner *spawner;
}Level;

void createGameLevel(u_int *levelArr);
void prepareSpawner(Level *level);
void printLevel(u_int *levelArr);

#endif
