#ifndef LEVEL_H
#define LEVEL_H
#include "../include/main.h"
#include <raylib.h>

typedef struct ConveyorBelt
{
    Vector2 pos;
    Texture2D texture;
}
ConveyorBelt;

typedef struct Spawner
{

    Texture2D texture;
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
}
Spawner;

typedef struct Level
{
    unsigned int levelArr[LEVEL_WIDTH * LEVEL_HEIGHT];
    unsigned int countConveyorBelt;
    unsigned int countAdder;
    unsigned int countLeftShift;
    unsigned int countSplitter;
    unsigned int countSpawner;
    Spawner *spawner;
}Level;

void create_game_level(unsigned int *levelArr);
void prepare_spawner(Level *level);
void print_level(unsigned int *levelArr);

#endif
