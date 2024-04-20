
#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "BaseObject.h"
#include "commonFile.h"

class BulletObject : public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    enum BULLET_DIRECT
    {
        DIRECT_LEFT = 20,
        DIRECT_RIGHT = 21,
        DIRECT_UP = 22,
        DIRECT_UP_LEFT = 23,
        DIRECT_UP_RIGHT = 24,
        DIRECT_DOWN_LEFT = 25,
        DIRECT_DOWN_RIGHT = 26,
    };

    enum BulletType
    {
        SPHERE_BULLET = 30,
        LASER_BULLET = 31,
    };

    void set_x_val(const int &x) {x_val_ = x;}
    void set_y_val(const int &y) {y_val_ = y;}
    void set_bullet_direct(const unsigned int &bulletDirect) {bullet_direct_ = bulletDirect;}

    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}
    unsigned int get_bullet_direct() const {return bullet_direct_;};

    void set_is_move(const bool& isMove) {is_move_ = isMove;}
    bool get_is_move() const {return is_move_;}

    void set_bullet_type(const unsigned int &bulletType) {bullet_type_ = bulletType;}
    unsigned int get_bullet_type() const {return bullet_type_;}

    void HandleMove(const int &x, const int &y);
    bool loadImageBullet(SDL_Renderer* renderer);
private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int bullet_direct_;
    unsigned int bullet_type_;
};

#endif // BULLET_OBJECT_H_
