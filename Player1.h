#ifndef PLAYER_1_H_
#define PLAYER_1_H_

#include "commonFile.h"
#include "MainObject.h"
#include "Explosion.h"

class Player1 : public MainObject
{
public:
    Player1();
    ~Player1();

    void set_x_pos_(float xPos) {x_pos_ = xPos;}
    void set_y_pos_(float yPos) {y_pos_ = yPos;}
    void HandleInputAction(SDL_Event events, SDL_Renderer* renderer);

    void set_bomb_list(std::vector<BombObject*> bomb_list)
    {
        p_bomb_list_1 = bomb_list;
    }
    std::vector<BombObject*> get_bomb_list() const { return p_bomb_list_1; }
    void HandleBomb(SDL_Renderer* renderer);
    void exploreBomb(SDL_Renderer* renderer);

private:
    std::vector<BombObject*> p_bomb_list_1;
    std::vector<int> time_to_explore_;
};

#endif // PLAYER_1_H_
