#ifndef PLAY_POWER_H
#define PLAY_POWER_H

#include "commonFile.h"
#include "BaseObject.h"

class PlayPower : public BaseObject
{
public:
    PlayPower();
    ~PlayPower();

    void setNum(const int& num) {number_ = num;}
    void addPos(const int& xPos);
    void Show(SDL_Renderer* renderer);
    void Init(SDL_Renderer* renderer);

    void Increase();
    void Decrease();

private:
    int number_;
    std::vector<int> pos_list_;
};

class PlayMoney : public BaseObject
{
public:
    PlayMoney();
    ~PlayMoney();

    void Init(SDL_Renderer* renderer);
    void Show(SDL_Renderer* renderer);

    void setPos(const int& x, const int& y) {x_pos_ = x; y_pos_ = y;}

private:
    int x_pos_;
    int y_pos_;
};

#endif // PLAY_POWER_H
