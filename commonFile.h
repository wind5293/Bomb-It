#ifndef COMMON_FILE_H_
#define COMMON_FILE_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event e;

const int SCREEN_WIDTH = 1020;
const int SCREEN_HEIGHT = 510;
const std::string windowTitle = "Bomb It Project";

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#define BLANK_TILE 0
#define TILE_SIZE 51
#define MAX_MAP_X 20
#define MAX_MAP_Y 9

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* fileName;
};

#endif // COMMON_FILE_H_
