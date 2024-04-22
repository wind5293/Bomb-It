
#ifndef EXPLOSION_H_
#define EXPLOSION_H_

#include "commonFile.h"
#include "BaseObject.h"

#define NUM_FRAME_EXP 16

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject();
    ~ExplosionObject();

    void setClip();
    void setFrame(const int& fr) {frame_ = fr;}

    bool loadMedia(std::string path, SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);

    int get_frame_width() const {return frame_width_;}
    int get_frame_height() const {return frame_height_;}

private:
    unsigned int frame_;

    int frame_width_;
    int frame_height_;

    SDL_Rect frame_clip_[NUM_FRAME_EXP];
};

#endif // EXPLOSION_H_
