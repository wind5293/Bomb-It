
#ifndef PLAYER_2_H_
#define PLAYER_2_H_

#include "commonFile.h"
#include "MainObject.h"

class Player2 : public MainObject
{
public:
    Player2();
    ~Player2();

    void HandleInputAction(SDL_Event events, SDL_Renderer* renderer);
    void set_bomb_list(std::vector<BombObject*> bomb_list)
    {
        p_bomb_list_2 = bomb_list;
    }
    std::vector<BombObject*> get_bomb_list() const { return p_bomb_list_2; }
    void HandleBomb(SDL_Renderer* renderer);

private:
    std::vector <BombObject*> p_bomb_list_2;
};

#endif // PLAYER_2asd_H_
