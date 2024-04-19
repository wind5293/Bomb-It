#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "commonFile.h"
#include "BaseObject.h"

#define MAX_TILES 20

class tileMat : public BaseObject
{
public:
    tileMat() {;}
    ~tileMat() {;}
};

class gameMap
{
public:
    gameMap() {;}
    ~gameMap() {;}

    void loadMap(char* name);
    void loadTile(SDL_Renderer* renderer);
    void drawMap(SDL_Renderer* renderer);
    Map getMap() const {return game_map_;};
    void setMap(Map& map_data) {game_map_ = map_data;};

private:
    Map game_map_;
    tileMat tile_mat[MAX_TILES];
};

#endif // GAME_MAP_H_
