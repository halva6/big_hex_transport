#include "../include/level.h"

void create_game_level(unsigned int *level)
{
    for (int i = 0; i < LEVEL_WIDTH * LEVEL_HEIGHT; i++)
    {
        level[i] = 0;
    }
}

void print_level(unsigned int *level)
{
    for (int i = 0; i < LEVEL_WIDTH * LEVEL_HEIGHT; i++)
    {
        if (i != 0 && i % LEVEL_WIDTH == 0)
        {
            printf("\n");
        }
        printf("%d ", level[i]);
    }
    printf("\n");
}
