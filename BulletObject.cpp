
#include <iostream>
#include "BulletObject.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type_ = SPHERE_BULLET;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(const int &x_border, const int &y_border)
{
    if (bullet_direct_ == DIRECT_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_direct_ == DIRECT_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_direct_ == DIRECT_UP)
    {
        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_direct_ == DIRECT_UP_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_direct_ == DIRECT_UP_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
        rect_.y -= y_val_;
        if (rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if (bullet_direct_ == DIRECT_DOWN_LEFT)
    {
        rect_.x -= x_val_;
        if (rect_.x < 0)
        {
            is_move_ = false;
        }
        rect_.y += y_val_;
        if (rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
    else if (bullet_direct_ == DIRECT_DOWN_RIGHT)
    {
        rect_.x += x_val_;
        if (rect_.x > x_border)
        {
            is_move_ = false;
        }
        rect_.y += y_val_;
        if (rect_.y > y_border)
        {
            is_move_ = false;
        }
    }
}

bool BulletObject::loadImageBullet(SDL_Renderer* renderer)
{
    bool ret = false;
    if (bullet_type_ == SPHERE_BULLET)
    {
        ret = loadMedia("img//sphere_bullet.png", renderer);
    }
    else if (bullet_type_ == LASER_BULLET)
    {
        ret = loadMedia("img//laser_bullet.png", renderer);
    }
    return ret;
}
