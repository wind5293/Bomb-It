
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

private:

};

#endif // PLAYER_2asd_H_
