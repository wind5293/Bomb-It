#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "commonFile.h"
#include "BaseObject.h"

class mainObject : public BaseObject
{
public:
    mainObject();
    ~mainObject();

    enum WALK_TYPE
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };

    bool loadMedia(std::string path, SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);
    void handleInputAction(SDL_Event events, SDL_Renderer* renderer);
    void setClip();
    void doPlayer(Map& map_data);
    void checkToMap(Map& map_data);

private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[8];
    Input input_type_;
    int frame_;
    int status_;

    bool on_ground_ = false;
};

#endif // MAIN_OBJECT_H
