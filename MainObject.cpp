#include <iostream>
#include "MainObject.h"

#define PLAYER_SPEED 8
#define BLANK_TILE 0

MainObject::MainObject()
{
    frame_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    width_frame_ = 0;
    height_frame_ = 0;
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.down_ = 0;
    input_type_.right_ = 0;
    input_type_.up_ = 0;
}

MainObject::~MainObject()
{

}

bool MainObject::loadMedia(std::string path, SDL_Renderer* renderer)
{
    bool ret = baseObject::loadMedia(path, renderer);
    if (ret)
    {
        width_frame_ = rect_.w / 8;
        height_frame_ = rect_.h;
    }
    return ret;
}

void MainObject::SetClip()
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

void MainObject::Show(SDL_Renderer* renderer)
{
    if (status_ == WALK_LEFT)
    {
        loadMedia("img/player_left.png", renderer);
    }
    else if (status_ == WALK_RIGHT)
    {
        loadMedia("img/player_right.png", renderer);
    }
    if (input_type_.left_ == 1 || input_type_.right_ == 1)
    {
        frame_++;
        if (frame_ == 8) frame_ = 0;
    }
    else frame_ = 0;

    rect_.x = x_pos_;
    rect_.y = y_pos_;

    SDL_Rect* current_clip = &frame_clip_[frame_];

    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopy(renderer, p_object_, current_clip, &renderQuad);
}

//void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* renderer)
//{
//    if (events.type == SDL_KEYDOWN)
//    {
//        switch(events.key.keysym.sym)
//        {
//        case SDLK_a:
//            status_ = WALK_LEFT;
//            input_type_.left_ = 1;
//            input_type_.right_ = 0;
//            input_type_.down_ = 0;
//            input_type_.up_ = 0;
//            break;
//        case SDLK_d:
//            status_ = WALK_RIGHT;
//            input_type_.left_ = 0;
//            input_type_.right_ = 1;
//            input_type_.down_ = 0;
//            input_type_.up_ = 0;
//            break;
//        case SDLK_w:
//            status_ = WALK_UP;
//            input_type_.left_ = 0;
//            input_type_.right_ = 0;
//            input_type_.down_ = 0;
//            input_type_.up_ = 1;
//            break;
//        case SDLK_s:
//            status_ = WALK_DOWN;
//            input_type_.left_ = 0;
//            input_type_.right_ = 0;
//            input_type_.down_ = 1;
//            input_type_.up_ = 0;
//            break;
//        default:
//            break;
//        }
//    }
//    else if (events.type == SDL_KEYUP)
//    {
//        switch(events.key.keysym.sym)
//        {
//        case SDLK_a:
//            input_type_.left_ = 0;
//            break;
//        case SDLK_d:
//            input_type_.right_ = 0;
//            break;
//        case SDLK_w:
//            input_type_.up_ = 0;
//            break;
//        case SDLK_s:
//            input_type_.down_ = 0;
//            break;
//        default:
//            break;
//        }
//    }
//}

void MainObject::doPlayer(Map& map_data_)
{
    x_val_ = 0;
    y_val_ = 0;

    if (input_type_.left_ == 1)
    {
        x_val_ -= PLAYER_SPEED;
    }
    else if (input_type_.right_ == 1)
    {
        x_val_ += PLAYER_SPEED;
    }
    else if (input_type_.up_ == 1)
    {
        y_val_ -= PLAYER_SPEED;
    }
    else if (input_type_.down_ == 1)
    {
        y_val_ += PLAYER_SPEED;
    }

    checkToMap(map_data_);
}

void MainObject::checkToMap(Map& map_data)
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

            if (val1 != BLANK_TILE || val2 != BLANK_TILE)
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

            if (val1 != BLANK_TILE || val2 != BLANK_TILE)
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

            if (val1 != BLANK_TILE || val2 != BLANK_TILE)
            {
                y_pos_ = y2 * TILE_SIZE;
                y_pos_ -= height_frame_;
                y_val_ = 0;
            }
        }
        else if (y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];

            if (val1 != BLANK_TILE || val2 != BLANK_TILE)
            {
                y_pos_ = (y1 + 1) * TILE_SIZE;
                y_val_ = 0;
            }
        }
    }

    x_pos_ += x_val_;
    y_pos_ += y_val_;

}

