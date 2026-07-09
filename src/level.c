#include "../include/level.h"
#include <stdio.h>
#include <stdlib.h>

void create_game_level(unsigned int *level)
{
    for (int i = 0; i < LEVEL_WIDTH * LEVEL_HEIGHT; i++)
    {
        level[i] = 0;
    }
}

void prepare_spawner(Level *level)
{
    int randomPos[level->countSpawner];
    randomPos[0] = GetRandomValue(0, ((LEVEL_WIDTH - 1) * (LEVEL_HEIGHT - 1)) - 1);

    for (int i = 1; i < level->countSpawner; i++)
    {
        randomPos[i] = GetRandomValue(0, ((LEVEL_WIDTH - 1) * (LEVEL_HEIGHT - 1)) - 1);
        while (randomPos[i] == randomPos[i - 1])
        {
            randomPos[i] = GetRandomValue(0, ((LEVEL_WIDTH - 1) * (LEVEL_HEIGHT - 1)) - 1);
        }
    }

    level->spawner = malloc(level->countSpawner * sizeof(Spawner));
    Texture2D spawTex = LoadTexture("assets/game/Spawner.png");
    for (int i = 0; i < level->countSpawner; i++)
    {
        level->levelArr[randomPos[i]] = 1;
        level->levelArr[randomPos[i] + 1] = 1;
        level->levelArr[randomPos[i] + LEVEL_WIDTH] = 1;
        level->levelArr[randomPos[i] + LEVEL_WIDTH + 1] = 1;

        Spawner spawner;
        spawner.texture = spawTex;
        spawner.width = 40;
        spawner.height = 40;
        spawner.y = (int)randomPos[i] / LEVEL_WIDTH;
        spawner.x = (int)(randomPos[i] % LEVEL_HEIGHT);

        level->spawner[i] = spawner;
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
