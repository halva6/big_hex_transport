#ifndef LEVEL_H
#define LEVEL_H
#include "../include/main.h"

typedef struct Level
{
    unsigned int level[LEVEL_WIDTH * LEVEL_HEIGHT];
    unsigned int count_conveyor_belt;
    unsigned int count_adder;
    unsigned int count_left_shift;
    unsigned int count_splitter;
    unsigned int count_spawner;
}Level;

void create_game_level(unsigned int *level);
void print_level(unsigned int *level);

#endif
