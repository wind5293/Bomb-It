#include <iostream>
#include "PlayPower.h"

PlayPower::PlayPower()
{
    number_ = 0;
}

PlayPower::~PlayPower()
{

}

void PlayPower::addPos(const int& xp)
{
    pos_list_.push_back(xp);
}

void PlayPower::Init(SDL_Renderer* renderer)
{
    loadMedia("img//player_pw.png", renderer);
    number_ = 3;

    if (pos_list_.size() > 0)
    {
        pos_list_.clear();
    }
    addPos(20);
    addPos(60);
    addPos(100);
}

void PlayPower::Show(SDL_Renderer* renderer)
{
    for (int i = 0; i < pos_list_.size(); i++)
    {
        rect_.x = pos_list_.at(i);
        rect_.y = 0;
        render(renderer);
    }
}

void PlayPower::Decrease()
{
    number_--;
    pos_list_.pop_back();
}

void PlayPower::Increase()
{
    number_++;
    int last_pos = pos_list_.back();
    last_pos += 40;
    pos_list_.push_back(last_pos);
}

PlayMoney::PlayMoney()
{
    x_pos_ = 0;
    y_pos_ = 0;
}

PlayMoney::~PlayMoney()
{

}

void PlayMoney::Init(SDL_Renderer* renderer)
{
    bool ret = BaseObject::loadMedia("img//money_img.png", renderer);
}

void PlayMoney::Show(SDL_Renderer* renderer)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    render(renderer);
}

