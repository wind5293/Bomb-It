#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "commonFile.h"

class baseObject
{
public:
    baseObject();
    ~baseObject();

    void setRect(const int& x, const int& y) {rect_.x = x; rect_.y = y;}

    SDL_Rect getRect()
    {
        return rect_;
    }
    SDL_Texture* getObject()
    {
        return p_object_;
    }

    virtual bool loadMedia(std::string path, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer, const SDL_Rect* clip = NULL);
    void Quit();

protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
};

#endif // BASE_OBJECT_H_
