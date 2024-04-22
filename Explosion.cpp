
#include <iostream>
#include "Explosion.h"

ExplosionObject::ExplosionObject()
{
    frame_width_ = 0;
    frame_height_ = 0;
    frame_ = 0;
}

ExplosionObject::~ExplosionObject()
{

}

bool ExplosionObject::loadMedia(std::string path, SDL_Renderer* renderer)
{
    bool ret = BaseObject::loadMedia(path, renderer);
    if (ret)
    {
        frame_width_ = rect_.w / 8;
        frame_height_ = rect_.h;
    }
    return ret;
}

void ExplosionObject::setClip()
{
    if (frame_width_ > 0 && frame_height_ > 0)
    {
        for (int i = 0; i < NUM_FRAME_EXP; i++)
        {
            frame_clip_[i].x = frame_width_ * (i / 2);
            frame_clip_[i].y = 0;
            frame_clip_[i].w = frame_width_;
            frame_clip_[i].h = frame_height_;
        }
    }
}

void ExplosionObject::Show(SDL_Renderer* renderer)
{
    SDL_Rect* current_clip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, frame_width_, frame_height_};

    if (current_clip != NULL)
    {
        renderQuad.w = current_clip->w;
        renderQuad.h = current_clip->h;
    }

    SDL_RenderCopy(renderer, p_object_, current_clip, &renderQuad);
}
