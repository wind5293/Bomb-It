
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
            BombObject* p_bomb = new BombObject();
            p_bomb->loadImageBomb(renderer);
            p_bomb->setRect(this->rect_.x / TILE_SIZE * TILE_SIZE, this->rect_.y / TILE_SIZE * TILE_SIZE);
            p_bomb->set_is_placed(true);

            if (p_bomb_list_2.size() <= 3)
            {
                p_bomb_list_2.push_back(p_bomb);
                int timeToExplore = 30;
                time_to_explore_.push_back(timeToExplore);
            }
        }
    }
}

void Player2::HandleBomb(SDL_Renderer* renderer)
{
    for (int i = 0; i < p_bomb_list_2.size(); i++)
    {
        BombObject* p_bomb_ = p_bomb_list_2.at(i);
        if (p_bomb_ != NULL)
        {
            if (p_bomb_->get_is_placed())
            {
                p_bomb_->render(renderer);
            }
            else {
                p_bomb_list_2.erase(p_bomb_list_2.begin() + i);
                if (p_bomb_ != NULL)
                {
                    delete p_bomb_;
                    p_bomb_ = NULL;
                }
            }
        }
        if (time_to_explore_[i] == 0)
        {
            ExplosionObject exp_obj;

            exp_obj.loadMedia("img/exp3.png", renderer);
            exp_obj.setClip();
            exp_obj.setRect(p_bomb_->getRect().x, p_bomb_->getRect().y);
            exp_obj.Show(renderer);

            p_bomb_list_2.erase(p_bomb_list_2.begin() + i);
            if (p_bomb_ != NULL)
            {
                delete p_bomb_;
                p_bomb_ = NULL;
            }
        }
        else {
            time_to_explore_[i]--;
        }
    }
}
