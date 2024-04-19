#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include <vector>

#include "commonFile.h"
#include "BaseObject.h"
#include "BulletObject.h"


class mainObject : public BaseObject
{
public:
    mainObject();
    ~mainObject();

    enum WALK_TYPE
    {
        WALK_NONE = -1,
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };

    bool loadMedia(std::string path, SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);
    void handleInputAction(SDL_Event events, SDL_Renderer* renderer);
    void setClip();

    void doPlayer(Map& map_data);
    void checkToMap(Map& map_data);
    void setMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;};
    void CenterEntityOnMap(Map& map_data);
    void updateImagePlayer(SDL_Renderer* renderer);

    SDL_Rect get_rect_frame();

    void set_bullet_list_ (std::vector<BulletObject*> bullet_list_)
    {
        p_bullet_list_ = bullet_list_;
    }
    std::vector<BulletObject*> get_bullet_object() const { return p_bullet_list_; }

    void HandleBullet(SDL_Renderer* renderer);
    void removeBullet(const int& i);

    void increaseMoney();

    void setComeBackTime(const int& cb_t) {come_back_time_ = cb_t;}

    int getCollectedMoney() const {return money_collected;}

private:
    std::vector<BulletObject*> p_bullet_list_;
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

    int map_x_;
    int map_y_;
    int come_back_time_;

    int money_collected;
};

#endif // MAIN_OBJECT_H
