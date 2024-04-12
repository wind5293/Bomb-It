#ifndef BOMB_OBJECT_H_
#define BOMB_OBJECT_H_

#include "commonFile.h"
#include "baseObject.h"

class BombObject : public baseObject
{
public:
    BombObject();
    ~BombObject();

private:
    int frame_width_;
    int frame_height;
};

#endif // BOMB_OBJECT_H_
