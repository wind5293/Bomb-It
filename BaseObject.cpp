#include <iostream>
#include "commonFile.h"
#include "BaseObject.h"

BaseObject::BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject::~BaseObject()
{
    Quit();
}

bool BaseObject::loadMedia(std::string path, SDL_Renderer* renderer)
{
    Quit();
    //bool success = true;
    SDL_Texture* texture = NULL;

    SDL_Surface* loadSurface = IMG_Load(path.c_str());
    if (loadSurface != NULL){
        SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));

        texture = SDL_CreateTextureFromSurface(renderer, loadSurface);
        if (texture != NULL){
            rect_.w = loadSurface->w;
            rect_.h = loadSurface->h;
        }

        SDL_FreeSurface(loadSurface);
    }
    p_object_ = texture;
    return p_object_ != NULL;
}

void BaseObject::render(SDL_Renderer* renderer, const SDL_Rect* clip /* = NULL */)
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};

    SDL_RenderCopy(renderer, p_object_, clip, &renderquad);
}

void BaseObject::Quit()
{
    if (p_object_ != NULL)
    {
        SDL_DestroyTexture(p_object_);
        p_object_ = NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
}
