#include <iostream>
#include "commonFile.h"
#include "BaseObject.h"
#include "TextObject.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

  // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
        return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
        return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
        return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
        return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
        return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
        return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
        return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
        return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

//SDL_Surface* SDLCommonFunc::LoadImg(std::string path)
//{
//    SDL_Surface* load_image = NULL;
//    SDL_Surface
//}

int SDLCommonFunc::Hello(SDL_Renderer* renderer, TTF_Font* font)
{
    BaseObject MenuObject;

    bool loadImageOK = MenuObject.loadMedia("img\\background.png", renderer);
    if (loadImageOK == false)
    {
        return 1;
    }

    const int kMenuItemNum = 1;
    SDL_Rect pos_arr[kMenuItemNum];
    pos_arr[0].x = 560;
    pos_arr[0].y = 500;

    TextObject text_menu[kMenuItemNum];
    text_menu[0].setText("Touch to play");
    text_menu[0].setColor(TextObject::WHITE_TEXT);
    text_menu[0].loadFromRenderText(font, renderer);

    bool selected[kMenuItemNum] = {0};
    SDL_Event event;

    int xm;
    int ym;

    while (true)
    {
        MenuObject.render(renderer);

        text_menu[0].RenderText(renderer, pos_arr[0].x, pos_arr[0].y);
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                return 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_LEFT)
                    return 0;
                break;
            default:
                break;
            }
        }

        SDL_RenderPresent(renderer);
    }

    return 1;
}

int SDLCommonFunc::Tutorial(SDL_Renderer* renderer, TTF_Font* font)
{
    BaseObject MenuObject;

    bool loadImageOK = MenuObject.loadMedia("img\\background.png", renderer);
    if (loadImageOK == false)
    {
        return 1;
    }

    SDL_Rect pos_arr;
    pos_arr.x = 530;
    pos_arr.y = 400;


    TextObject text_menu;
    text_menu.setText("CLICK HERE TO PLAY");
    text_menu.setColor(TextObject::BLACK_TEXT);
    text_menu.loadFromRenderText(font, renderer);

    bool selected = 0;
    SDL_Event event;

    int xm;
    int ym;

    while (true)
    {
        MenuObject.render(renderer);
        text_menu.RenderText(renderer, pos_arr.x, pos_arr.y);

        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                return 1;
                break;
            case SDL_MOUSEMOTION:
                xm = e.motion.x;
                ym = e.motion.y;

                if (xm >= pos_arr.x && xm < pos_arr.x + text_menu.getWidth() &&
                    ym >= pos_arr.y && ym < pos_arr.y + text_menu.getHeight() )
                {
                    if (selected == false)
                    {
                        selected = true;
                        std::cout << 1 << std::endl;
                        text_menu.setColor(TextObject::RED_TEXT);
                        text_menu.loadFromRenderText(font, renderer);
                    }
                }
                else
                {
                    if (selected == true)
                    {
                        selected = false;
                        text_menu.setColor(TextObject::WHITE_TEXT);
                        text_menu.loadFromRenderText(font, renderer);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                xm = e.button.x;
                ym = e.button.y;

                if (xm >= pos_arr.x && xm < pos_arr.x + text_menu.getWidth() &&
                    ym >= pos_arr.y && ym < pos_arr.y + text_menu.getHeight() )
                {
                    return 0;
                }
                break;
            default:
                break;
            }
        }
        SDL_RenderPresent(renderer);
    }
    return 1;
}

