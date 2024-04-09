#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "commonFile.h"
#include "baseObject.h"

#define MAX_TILES 20

class tileMat : public baseObject
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

    Map getMap() const {return game_map_;}
private:
    Map game_map_;
    tileMat tile_mat[MAX_TILES];
};

#endif // GAME_MAP_H_
