#include <iostream>
#include "commonFile.h"
#include "baseObject.h"
#include "gameMap.h"
#include "MainObject.h"

baseObject gBackground;

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not be initialized! SDL error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering is not enabled";
        }
        gWindow = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            std::cout << "Window could not be created! SDL error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                std::cout << "Renderer could not be initialized! SDL error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!IMG_Init(imgFlags) && imgFlags)
                {
                    std::cout << "SDL_Image could not be initialized! SDL error: " << SDL_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadBackground()
{
    bool ret = gBackground.loadMedia("img\\background.png", gRenderer);
    return ret;
}

void close()
{
    gBackground.Quit();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (!init())
    {
        std::cout << "Failed to initialize!" << std::endl;
        return -1;
    }
    if (!loadBackground())
    {
        std::cout << "Failed to load background!" << std::endl;
        return -1;
    }

    gameMap game_map;
    game_map.loadMap("map/map_data.dat");
    game_map.loadTile(gRenderer);

    MainObject p_player_;
    p_player_.loadMedia("img/player_left.png", gRenderer);
    p_player_.SetClip();

    bool isQuit = false;
    while (!isQuit)
    {
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
            {
                isQuit = true;
            }
            p_player_.HandleInputAction(events, gRenderer);
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        Map map_data = game_map.getMap();

        gBackground.render(gRenderer, NULL);

        game_map.drawMap(gRenderer);

        p_player_.doPlayer(map_data);
        p_player_.Show(gRenderer);

        SDL_RenderPresent(gRenderer);

        SDL_Delay(50);
    }
    close();
    return 0;
}
