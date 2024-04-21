#include <iostream>
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
    width_frame_ = 0;
    height_frame_ = 0;

    x_val_ = 0.0;
    y_val_ = 0.0;

    x_pos_ = 0.0;
    y_pos_ = 0.0;

    on_ground_ = false;
    come_back_time_ = 0;
    frame_ = 0;

    animation_a_ = 0;
    animation_b_ = 0;
    input_type_.left_ = 0;
    type_move_ = STATIC_THREAT;
}

ThreatsObject::~ThreatsObject()
{

}

bool ThreatsObject::loadMedia(std::string path, SDL_Renderer* renderer)
{
    bool ret = BaseObject::loadMedia(path, renderer);
    if (ret)
    {
        width_frame_ = rect_.w / THREAT_FRAME_NUM;
        height_frame_ = rect_.h;
    }
    return ret;
}

void ThreatsObject::setClips()
{
    if (width_frame_ > 0 && height_frame_ > 0)
    {
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = width_frame_;
        frame_clip_[0].h = height_frame_;

        frame_clip_[1].x = width_frame_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = width_frame_;
        frame_clip_[1].h = height_frame_;

        frame_clip_[2].x = 2 * width_frame_;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = width_frame_;
        frame_clip_[2].h = height_frame_;

        frame_clip_[3].x = 3 * width_frame_;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = width_frame_;
        frame_clip_[3].h = height_frame_;

        frame_clip_[4].x = 4 * width_frame_;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = width_frame_;
        frame_clip_[4].h = height_frame_;

        frame_clip_[5].x = 5 * width_frame_;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = width_frame_;
        frame_clip_[5].h = height_frame_;

        frame_clip_[6].x = 6 * width_frame_;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = width_frame_;
        frame_clip_[6].h = height_frame_;

        frame_clip_[7].x = 7 * width_frame_;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = width_frame_;
        frame_clip_[7].h = height_frame_;
    }
}

void ThreatsObject::Show(SDL_Renderer* renderer)
{
    if (come_back_time_ == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if (frame_ >= THREAT_FRAME_NUM)
        {
            frame_ = 0;
        }
    }
    SDL_Rect* currentClip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, rect_.w / THREAT_FRAME_NUM, rect_.h};

    SDL_RenderCopy(renderer, p_object_, currentClip, &renderQuad);
}

SDL_Rect ThreatsObject::get_rect_frame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame_;
    rect.h = height_frame_;

    return rect;
}

void ThreatsObject::doPlayer(Map& map_data)
{
    if (come_back_time_ == 0)
    {
        x_val_ = 0;
        y_val_ += THREAT_GRAVITY_SPEED;

        if (y_val_ >= THREAD_MAX_FALL_SPEED)
        {
            y_val_ = THREAD_MAX_FALL_SPEED;
        }

        if (input_type_.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }
        else if (input_type_.right_ == 1)
        {
            x_val_ += THREAT_SPEED;
        }

        checkToMap(map_data);
    }
    else if (come_back_time_ > 0)
    {
        come_back_time_--;
        if (come_back_time_ == 0)
        {
            initThreats();
        }
    }
}

void ThreatsObject::initThreats()
{
    x_val_ = 0;
    y_val_ = 0;
    if (x_pos_ > 256)
    {
        x_pos_ -= 256;
        animation_a_ -= 256;
        animation_b_ -= 256;
    }
    else
    {
        x_pos_ = 0;
    }
    y_pos_ = 0;
    come_back_time_ = 0;
    input_type_.left_ = 1;
}

void ThreatsObject::checkToMap(Map& map_data)
{
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    //Check horizontal
    int height_min = (height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE);

    x1 = (x_pos_ + x_val_) / TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

    y1 = y_pos_ / TILE_SIZE;
    y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if (x_val_ > 0) //main object is moving to right
        {
            int val1 = map_data.tile[y1][x2];
            int val2 = map_data.tile[y2][x2];

            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                x_pos_ = x2 * TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }

        }
        else if (x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];

            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                x_pos_ = (x1 + 1) * TILE_SIZE;
                x_val_ = 0;
            }
        }
    }

    //check vertical
    int width_min_ = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = x_pos_ / TILE_SIZE;
    x2 = (x_pos_ + width_min_) / TILE_SIZE;

    y1 = (y_pos_ + y_val_) / TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

    if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) //Object is inside the map
    {
        if (y_val_ > 0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];

            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= height_frame_;
                y_val_ = 0;

                on_ground_ = true;

//                if (status_ == WALK_NONE)
//                {
//                    status_ = WALK_NONE;
//                }
            }
        }
        else if (y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if ((val1 != BLANK_TILE && val1 != STATE_MONEY) || (val2 != BLANK_TILE && val2 != STATE_MONEY))
            {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

    if (x_pos_ < 0) x_pos_ = 0;
    else if (x_pos_ + width_frame_ > map_data.max_x_) x_pos_ = map_data.max_x_ - width_frame_ - 1;

    //Xu li roi xuong vuc
    if (y_pos_ > map_data.max_y_)
    {
        come_back_time_ = 60;
    }

}

void ThreatsObject::implementMoveType(SDL_Renderer* renderer)
{
    if (type_move_ == STATIC_THREAT)
    {
        ;//
    }
    else {
        if (on_ground_ == true)
        {
            if (x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                loadMedia("img/threat_left.png", renderer);
            }
            else if (x_pos_ < animation_a_)
            {
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                loadMedia("img/threat_right.png", renderer);
            }
        }
        else
        {
            if (input_type_.left_ == 1)
            {
                loadMedia("img/threat_left.png", renderer);
            }
            else
            {
                loadMedia("img/threat_right.png", renderer);
            }
        }
    }
}

void ThreatsObject::initBullet(BulletObject* p_bullet, SDL_Renderer* renderer)
{
    if (p_bullet != NULL)
    {
        p_bullet->set_bullet_type(BulletObject::LASER_BULLET);
        bool ret = p_bullet->loadImageBullet(renderer);
        if (ret)
        {
            p_bullet->loadImageBullet(renderer);
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_direct(BulletObject::DIRECT_LEFT);
            p_bullet->setRect(rect_.x - 40, y_pos_ + 10);
            p_bullet->set_x_val(20);
    //        p_bullet->set_y_val();

            bullet_list_.push_back(p_bullet);
        }
    }
}

void ThreatsObject::makeBullet(SDL_Renderer* renderer, const int& x_limit, const int& y_limit)
{
    for (int i = 0; i < bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = bullet_list_.at(i);
        if (p_bullet != NULL)
        {
            if (p_bullet->get_is_move() == true)
            {
                int bullet_distance_ = rect_.x + width_frame_ - p_bullet->getRect().x;
                if (bullet_distance_ < 300 && bullet_distance_ > 0)
                {
                    p_bullet->HandleMove(x_limit, y_limit);
                    p_bullet->render(renderer);
                }
                else
                {
                    p_bullet->set_is_move(false);
                }

            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->setRect(rect_.x - 40, y_pos_ + 10);
            }
        }
    }
}

void ThreatsObject::removeBullet(const int& i)
{
    int sz = bullet_list_.size();
    if (sz > 0 && i < sz)
    {
        BulletObject* p_bullet = bullet_list_.at(i);
        bullet_list_.erase(bullet_list_.begin() + i);

        if (p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

