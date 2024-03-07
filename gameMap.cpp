#include <iostream>
#include "gameMap.h"
#include <fstream>

tileMat::tileMat()
{

}

tileMat::~tileMat()
{

}

void gameMap::loadMap(char* name)
{
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb");
    if (fp == NULL)
    {
        std::cout << "Could not open file!\n";
        return;
    }

    game_map.max_x_ = 0;
    game_map.max_y_ = 0;
    for (int i = 0; i < MAX_MAP_Y; i++)
    {
        for (int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf(fp, "%d", &game_map.tile[i][j]);
            int val = game_map.tile[i][j];
            if (val > 0){
                if (j > game_map.max_x_){
                    game_map.max_x_ = j;
                }
                if (i > game_map.max_y_){
                    game_map.max_y_ = i;
                }
            }
        }
    }
    game_map.max_x_ = (game_map.max_x_ + 1) * TILE_SIZE;
    game_map.max_y_ = (game_map.max_y_ + 1) * TILE_SIZE;

    game_map.start_x_ = 0;
    game_map.start_y_ = 0;
    game_map.fileName = name;

    fclose(fp);
}

void gameMap::loadTile(SDL_Renderer* renderer)
{
    char fileImg[10];
    FILE* fp = NULL;

}

//void gameMap::drawMap(SDL_Renderer* renderer)
//{
//
//}
