
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
    bool ret = baseObject::loadMedia(path, renderer);
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
        frame_clip_[0].x = 0;
        frame_clip_[0].y = 0;
        frame_clip_[0].w = frame_width_;
        frame_clip_[0].h = frame_height_;

        frame_clip_[1].x = frame_width_;
        frame_clip_[1].y = 0;
        frame_clip_[1].w = frame_width_;
        frame_clip_[1].h = frame_height_;

        frame_clip_[2].x = 2 * frame_width_;
        frame_clip_[2].y = 0;
        frame_clip_[2].w = frame_width_;
        frame_clip_[2].h = frame_height_;

        frame_clip_[3].x = 3 * frame_width_;
        frame_clip_[3].y = 0;
        frame_clip_[3].w = frame_width_;
        frame_clip_[3].h = frame_height_;

        frame_clip_[4].x = 4 * frame_width_;
        frame_clip_[4].y = 0;
        frame_clip_[4].w = frame_width_;
        frame_clip_[4].h = frame_height_;

        frame_clip_[5].x = 5 * frame_width_;
        frame_clip_[5].y = 0;
        frame_clip_[5].w = frame_width_;
        frame_clip_[5].h = frame_height_;

        frame_clip_[6].x = 6 * frame_width_;
        frame_clip_[6].y = 0;
        frame_clip_[6].w = frame_width_;
        frame_clip_[6].h = frame_height_;

        frame_clip_[7].x = 7 * frame_width_;
        frame_clip_[7].y = 0;
        frame_clip_[7].w = frame_width_;
        frame_clip_[7].h = frame_height_;
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
