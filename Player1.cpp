#include <iostream>
#include "Player1.h"

Player1::Player1()
{

}

Player1::~Player1()
{

}

void Player1::HandleInputAction(SDL_Event events, SDL_Renderer* renderer)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_a:
            status_ = WALK_LEFT;
            input_type_.left_ = 1;
            input_type_.right_ = 0;
            input_type_.down_ = 0;
            input_type_.up_ = 0;
            break;
        case SDLK_d:
            status_ = WALK_RIGHT;
            input_type_.left_ = 0;
            input_type_.right_ = 1;
            input_type_.down_ = 0;
            input_type_.up_ = 0;
            break;
        case SDLK_w:
            status_ = WALK_UP;
            input_type_.left_ = 0;
            input_type_.right_ = 0;
            input_type_.down_ = 0;
            input_type_.up_ = 1;
            break;
        case SDLK_s:
            status_ = WALK_DOWN;
            input_type_.left_ = 0;
            input_type_.right_ = 0;
            input_type_.down_ = 1;
            input_type_.up_ = 0;
            break;
        default:
            break;
        }
    }
    else if (events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_a:
            input_type_.left_ = 0;
            break;
        case SDLK_d:
            input_type_.right_ = 0;
            break;
        case SDLK_w:
            input_type_.up_ = 0;
            break;
        case SDLK_s:
            input_type_.down_ = 0;
            break;
        default:
            break;
        }
    }
}
