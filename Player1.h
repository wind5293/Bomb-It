#ifndef PLAYER_1_H_
#define PLAYER_1_H_

#include "commonFile.h"
#include "MainObject.h"

class Player1 : public MainObject
{
public:
    Player1();
    ~Player1();

    void HandleInputAction(SDL_Event events, SDL_Renderer* renderer);

private:

};

#endif // PLAYER_1_H_
