#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>
#include "commonFile.h"
#include "baseObject.h"
#include "BombObject.h"

class MainObject : public baseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_LEFT = 1,
        WALK_RIGHT = 2,
        WALK_UP = 3,
        WALK_DOWN = 4,
    };
    bool loadMedia(std::string path, SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);
    void HandleInputAction(SDL_Event events, SDL_Renderer* renderer);
    void SetClip();

    void doPlayer(Map& map_data_);
    void checkToMap(Map& map_data_);
    void updateImagePlayer(SDL_Renderer* renderer);

    void set_x_pos_(float xPos) {x_pos_ = xPos;}
    void set_y_pos_(float yPos) {y_pos_ = yPos;}

    int get_width_frame_() {return width_frame_;}
    int get_height_frame_() {return height_frame_;}

protected:
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
};

#endif // MAIN_OBJECT_H_
