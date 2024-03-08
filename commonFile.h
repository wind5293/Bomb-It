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

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const std::string title = "SDL Project";

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

typedef struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* fileName;
};

#endif // COMMONFILE
