
#include <iostream>
#include "BombObject.h"

BombObject::BombObject()
{
    is_placed_ = false;
}

BombObject::~BombObject()
{

}

bool BombObject::loadImageBomb(SDL_Renderer* renderer)
{
    bool ret = false;
    ret = baseObject::loadMedia("img//bomb.png", renderer);

    return ret;
}
