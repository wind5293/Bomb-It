#ifndef PLAYER_1_H_
#define PLAYER_1_H_

#include "commonFile.h"
#include "MainObject.h"

class Player1 : public MainObject
{
public:
    Player1();
    ~Player1();

    void set_x_pos_(float xPos) {x_pos_ = xPos;}
    void set_y_pos_(float yPos) {y_pos_ = yPos;}
    void HandleInputAction(SDL_Event events, SDL_Renderer* renderer);

private:

};

#endif // PLAYER_1_H_
