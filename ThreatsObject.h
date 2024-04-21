#ifndef THREATS_OBJECT_H_
#define THREATS_OBJECT_H_

#include "commonFile.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define THREAD_MAX_FALL_SPEED 10
#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_SPEED 3

class ThreatsObject : public BaseObject
{
public:
    ThreatsObject();
    ~ThreatsObject();

    enum TYPEMOVE
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
    };

    void set_x_val(int xVal) {x_val_ = xVal;}
    void set_y_val(int yVal) {y_val_ = yVal;}
    void set_x_pos(int xPos) {x_pos_ = xPos;}
    void set_y_pos(int yPos) {y_pos_ = yPos;}

    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}

    void SetMapXY(const int &mp_x, const int &mp_y) {map_x_ = mp_x; map_y_ = mp_y;}

    void setClips();
    bool loadMedia(std::string path, SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);

    SDL_Rect get_rect_frame();

    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}

    void doPlayer(Map& map_data);
    void checkToMap(Map& map_data);

    void initThreats();

    void set_type_move(const int & typeMove) {type_move_ = typeMove;}
    void setAnimationPos(const int& pos_a, const int& pos_b) {animation_a_ = pos_a; animation_b_ = pos_b;}
    void set_input_left(const int& ipLeft) {input_type_.left_ = ipLeft;}
    void implementMoveType(SDL_Renderer* renderer);

    std::vector<BulletObject*> getBulletList() const {return bullet_list_;}
    void set_bullet_list_ (std::vector<BulletObject*>& bl_list) {bullet_list_ = bl_list;}

    void initBullet(BulletObject* p_bullet, SDL_Renderer* renderer);
    void makeBullet(SDL_Renderer* renderer, const int& x_limit, const int& y_limit);
    void removeBullet(const int& i);

private:
    //int status_;
    int frame_;
    SDL_Rect frame_clip_[THREAT_FRAME_NUM];
    float width_frame_;
    float height_frame_;

    bool on_ground_;
    int come_back_time_;

    float x_pos_;
    float y_pos_;

    float x_val_;
    float y_val_;

    int map_x_;
    int map_y_;

    int type_move_;
    int animation_a_;
    int animation_b_;
    Input input_type_;

    std::vector<BulletObject*> bullet_list_;
};

#endif // THREAD_OBJECT_H_
