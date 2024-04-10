
#include <iostream>
#include "ImpTimer.h"

ImpTimer::ImpTimer()
{
    start_tick_ = 0;
    paused_tick_ = 0;

    is_paused_ = false;
    is_started_ = false;
}

ImpTimer::~ImpTimer()
{

}

void ImpTimer::start()
{
    is_started_ = true;
    is_paused_ = false;

    start_tick_ = SDL_GetTicks();
}

void ImpTimer::stop()
{
    is_paused_ = false;
    is_started_ = false;
}

void ImpTimer::pause()
{
    if (is_started_ && !is_paused_)
    {
        is_paused_ = true;
        paused_tick_ = SDL_GetTicks() - start_tick_;
    }
}

void ImpTimer::unpause()
{


    if (!is_paused_)
    {
        is_paused_ = false;
        start_tick_ = SDL_GetTicks() - paused_tick_;
        paused_tick_ = 0;
    }
}

int ImpTimer::getTicks()
{
    if (is_started_)
    {
        if (is_paused_)
        {
            return paused_tick_;
        }
        else {
            return SDL_GetTicks() - start_tick_;
        }
    }
    return 0;
}

bool ImpTimer::isStarted()
{
    return is_started_;
}

bool ImpTimer::isPaused()
{
    return is_paused_;
}

