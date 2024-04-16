#include <iostream>
#include "commonFile.h"
#include "baseObject.h"
#include "gameMap.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "Player1.h"
#include "Player2.h"

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
    ImpTimer fps_timer;

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

    Player1 p_player_1_;
    p_player_1_.loadMedia("img/player_left.png", gRenderer);
    p_player_1_.SetClip();

    Player2 p_player_2_;
    p_player_2_.loadMedia("img/player_right.png", gRenderer);
    p_player_2_.set_x_pos_(SCREEN_WIDTH - p_player_1_.get_width_frame_() - 1);
    p_player_2_.set_y_pos_(SCREEN_HEIGHT - p_player_1_.get_height_frame_() - 1);
    p_player_2_.SetClip();

    bool isQuit = false;
    while (!isQuit)
    {
        fps_timer.start();

        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_QUIT)
            {
                isQuit = true;
            }
            p_player_1_.HandleInputAction(events, gRenderer);
            p_player_2_.HandleInputAction(events, gRenderer);
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        Map map_data = game_map.getMap();

        gBackground.render(gRenderer, NULL);

        game_map.drawMap(gRenderer);

        p_player_1_.HandleBomb(gRenderer);
        p_player_1_.doPlayer(map_data);
        p_player_1_.Show(gRenderer);

        p_player_2_.HandleBomb(gRenderer);
        p_player_2_.doPlayer(map_data);
        p_player_2_.Show(gRenderer);

        std::vector<BombObject*> bomb_arr_1 = p_player_1_.get_bomb_list();
        for (int i = 0; i < bomb_arr_1.size(); i++)
        {
            BombObject* p_bomb = bomb_arr_1.at(i);
            if (p_bomb != NULL)
            {

            }
        }

        SDL_RenderPresent(gRenderer);

        int real_imp_time = fps_timer.getTicks();
        int time_one_flame = 1000 / FRAME_PER_SECOND; //ms
        if (real_imp_time < time_one_flame)
        {
            int delay_time = time_one_flame - real_imp_time;
            SDL_Delay(delay_time);
        }
    }
    close();
    return 0;
}
