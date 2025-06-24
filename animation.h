#pragma once

#include <stdint.h>



typedef struct {
	uint8_t id, x, y, length;
} SpriteInfo;

//{.id = 0, .x =  0, .y = 0, .length = 1},
static const SpriteInfo vcreamspridle[] = {
	
    {.id = 0, .x = 0, .y = 0, .length = 1},
};
static const SpriteInfo vcreamspridle1[] = {
	
    {.id = 1, .x = 32, .y = 0, .length = 12},
    {.id = 1, .x = 64, .y = 0, .length = 12},
    {.id = 1, .x = 96, .y = 0, .length = 12},
    {.id = 1, .x = 128, .y = 0, .length = 12},
    {.id = 1, .x =  0, .y = 32, .length = 12},
    {.id = 1, .x = 32, .y = 32, .length = 12},
    {.id = 1, .x = 64, .y = 32, .length = 12},
    {.id = 1, .x = 96, .y = 32, .length = 12},
    {.id = 1, .x = 128, .y = 32, .length = 12}


};
static const SpriteInfo vcreamspridle2[] = {
    {.id = 2, .x = 32, .y = 128, .length = 12},
    {.id = 2, .x = 64, .y = 128, .length = 12},
    {.id = 2, .x = 96, .y = 128, .length = 12},
    {.id = 2, .x = 128, .y = 128, .length = 12},
    {.id = 2, .x = 0, .y = 160, .length = 12},
    {.id = 2, .x = 0, .y = 160, .length = 12},
    {.id = 2, .x = 32, .y = 160, .length = 12},
    {.id = 2, .x = 64, .y = 160, .length = 12},
    {.id = 2, .x = 96, .y = 160, .length = 12},
    {.id = 2, .x = 128, .y = 160, .length = 12},
    {.id = 2, .x = 128, .y = 160, .length = 12},
    {.id = 2, .x = 0, .y = 192, .length = 12},
    {.id = 2, .x = 32, .y = 192, .length = 12},
    {.id = 2, .x = 64, .y = 192, .length = 12}
};
static const SpriteInfo vcreamsprwalk[] = {
    {.id = 3, .x = 32, .y = 64, .length = 13},
    {.id = 3, .x = 64, .y = 64, .length = 13},
    {.id = 3, .x = 96, .y = 64, .length = 13},
    {.id = 3, .x = 128, .y = 64, .length = 13}
};
static const SpriteInfo vcreamsprcomputer[] = {
    {.id = 4, .x = 64, .y = 192, .length = 13},
    {.id = 4, .x = 96, .y = 192, .length = 13},
    {.id = 4, .x = 128, .y = 192, .length = 13},
    {.id = 4, .x = 0, .y = 224, .length = 13},
    {.id = 4, .x = 32, .y = 224, .length = 13}
};