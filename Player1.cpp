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
    if (events.type == SDL_KEYDOWN)
    {
        if (events.key.keysym.sym == SDLK_r)
        {
            std::cout << "Player 1 placed a bomb" << std::endl;
            BombObject* p_bomb = new BombObject();
            p_bomb->loadImageBomb(renderer);
            p_bomb->setRect(this->rect_.x / TILE_SIZE * TILE_SIZE, this->rect_.y / TILE_SIZE * TILE_SIZE);
            p_bomb->set_is_placed(true);

            if (p_bomb_list_1.size() <= 3)
                p_bomb_list_1.push_back(p_bomb);
        }
    }
}

void Player1::HandleBomb(SDL_Renderer* renderer)
{
    for (int i = 0; i < p_bomb_list_1.size(); i++)
    {
        BombObject* p_bomb_ = p_bomb_list_1.at(i);
        if (p_bomb_ != NULL)
        {
            if (p_bomb_->get_is_placed())
            {
                p_bomb_->render(renderer);
            }
            else {
                p_bomb_list_1.erase(p_bomb_list_1.begin() + i);
                if (p_bomb_ != NULL)
                {
                    delete p_bomb_;
                    p_bomb_ = NULL;
                }
            }
        }
    }
}
