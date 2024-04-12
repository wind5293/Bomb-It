
#include <iostream>
#include "Player2.h"

Player2::Player2()
{
    x_pos_ = 0;
    y_pos_ = 0;
}

Player2::~Player2()
{

}

void Player2::HandleInputAction(SDL_Event events, SDL_Renderer* renderer)
{
    if (events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_LEFT:
            status_ = WALK_LEFT;
            input_type_.left_ = 1;
            input_type_.right_ = 0;
            input_type_.down_ = 0;
            input_type_.up_ = 0;
            break;
        case SDLK_RIGHT:
            status_ = WALK_RIGHT;
            input_type_.left_ = 0;
            input_type_.right_ = 1;
            input_type_.down_ = 0;
            input_type_.up_ = 0;
            break;
        case SDLK_UP:
            status_ = WALK_UP;
            input_type_.left_ = 0;
            input_type_.right_ = 0;
            input_type_.down_ = 0;
            input_type_.up_ = 1;
            break;
        case SDLK_DOWN:
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
        case SDLK_LEFT:
            input_type_.left_ = 0;
            break;
        case SDLK_RIGHT:
            input_type_.right_ = 0;
            break;
        case SDLK_UP:
            input_type_.up_ = 0;
            break;
        case SDLK_DOWN:
            input_type_.down_ = 0;
            break;
        default:
            break;
        }
    }

    if (events.type == SDL_KEYDOWN)
    {
        if (events.key.keysym.sym == SDLK_SPACE)
        {
            std::cout << "Player 2 placed a bomb" << std::endl;
        }
    }
}