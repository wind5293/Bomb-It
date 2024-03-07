#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "commonFile.h"

class BaseObject
{
protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
public:
    BaseObject();
    ~BaseObject();

    void setRect(const int& x, const int &y) {rect_.x = x; rect_.y = y;}

    SDL_Rect getRect() const
    {
        return rect_;
    }
    SDL_Texture* getObject() const
    {
        return p_object_;
    }
    bool loadMedia(std::string path, SDL_Renderer* screen);
    void render(SDL_Renderer* renderer, const SDL_Rect* rect_ = NULL);
    void Quit();
};

#endif // BASEOBJECT
