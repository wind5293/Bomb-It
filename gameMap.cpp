#include <iostream>
#include "gameMap.h"
#include <fstream>

void gameMap::loadMap(char* name)
{
    std::ifstream fp;
    fp.open(name);
    if (!fp.is_open())
    {
        //std::cout << "Could not open file!\n";
        return;
    }

    game_map_.max_x_ = 0;
    game_map_.max_y_ = 0;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            fp >> game_map_.tile[i][j];
            int val = game_map_.tile[i][j];
            //std::cout << val << " ";
            if (val > 0){
                if (j > game_map_.max_x_){
                    game_map_.max_x_ = j;
                }
                if (i > game_map_.max_y_){
                    game_map_.max_y_ = i;
                }
            }
        }
        //std::cout << std::endl;
    }
    game_map_.max_x_ = (game_map_.max_x_ + 1) * TILE_SIZE;
    game_map_.max_y_ = (game_map_.max_y_ + 1) * TILE_SIZE;

    game_map_.start_x_ = 0;
    game_map_.start_y_ = 0;
    game_map_.fileName = name;

    fp.close();
}

void gameMap::loadTile(SDL_Renderer* renderer)
{
    char fileImg[50];
    FILE* fp = NULL;
    //std::ifstream fp;

    for (int i = 0; i < MAX_TILES; i++)
    {
        sprintf_s(fileImg, "map/%d.png", i);
        //std::cout << fileImg << std::endl;

        fopen_s(&fp, fileImg, "rb");
        if (fp == NULL)
        {
            continue;
        }
        fclose(fp);

        tile_mat[i].loadMedia(fileImg, renderer);
    }
}

void gameMap::drawMap(SDL_Renderer* renderer) //Wrong something here
{
    int x1 = 0;
    int x2 = 0;
    int y1 = 0;
    int y2 = 0;

    int map_x = 0;
    int map_y = 0;

    map_x = game_map_.start_x_ / TILE_SIZE;
    x1 = (game_map_.start_x_ % TILE_SIZE) * -1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    map_y = game_map_.start_y_ / TILE_SIZE;
    y1 = (game_map_.start_y_ % TILE_SIZE) * -1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

    //std::cout << map_x << " " << x1 << " " << x2 << " " << map_y << " " << y1 << " " << y2 << std::endl;
    for (int i = y1; i < y2; i += TILE_SIZE)
    {
        map_x = game_map_.start_x_ / TILE_SIZE;

        for (int j = x1; j < x2; j += TILE_SIZE)
        {
            int val = game_map_.tile[map_y][map_x];
            //std::cout << val << " ";
            if (val > 0)
            {
                tile_mat[val].setRect(j, i);
                tile_mat[val].render(renderer);
            }
            map_x++;
        }
        map_y++;
    }
}
