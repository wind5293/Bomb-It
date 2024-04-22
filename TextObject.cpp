
#include <iostream>
#include "TextObject.h"

TextObject::TextObject()
{
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;

    texture_ = NULL;
}

TextObject::~TextObject()
{

}

bool TextObject::loadFromRenderText(TTF_Font* gFont, SDL_Renderer* renderer)
{
    SDL_Surface* text_surface_ = TTF_RenderText_Solid(gFont, str_val_.c_str(), text_color_);

    if (text_surface_)
    {
        texture_ = SDL_CreateTextureFromSurface(renderer, text_surface_);
        width_text_ = text_surface_->w;
        height_text_ = text_surface_->h;

        SDL_FreeSurface(text_surface_);
    }
    return texture_ != NULL;
}

void TextObject::Free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}

void TextObject::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color_.r = red;
    text_color_.g = green;
    text_color_.b = blue;
}

void TextObject::setColor(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = {255, 0, 0};
        text_color_ = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = {255, 255, 255};
        text_color_ = color;
    }
    else if (type == BLACK_TEXT)
    {
        SDL_Color color = {0, 0, 0};
        text_color_ = color;
    }
}

void TextObject::RenderText(SDL_Renderer* renderer,
                            int xp, int yp,
                            SDL_Rect* clip /* = NULL */,
                            double angle /* = 0.0 */,
                            SDL_Point* center /* = NULL */,
                            SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{
    SDL_Rect renderQuad = {xp, yp, width_text_, height_text_};
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture_, clip, &renderQuad, angle, center, flip);
}


