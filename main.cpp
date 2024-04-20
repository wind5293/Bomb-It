//SDL2Game.cpp : Defines the entry point for the console application
//-----------------------------------------------------------------

#include <iostream>
#include "commonFile.h"
#include "BaseObject.h"
#include "gameMap.h"
#include "mainObject.h"
#include "ImpTimer.h"
#include "ThreatsObject.h"
#include "Explosion.h"
#include "TextObject.h"
#include "PlayPower.h"

BaseObject gBackground;
TTF_Font* gFont_time;

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else {
        if ( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") )
        {
            std::cout << "Warning: Linear texture filtering is not enabled";
        }
        gWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL){
            std::cout << "Window could not be created! SDL error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!IMG_Init(imgFlags) && imgFlags)
                {
                    std::cout << "SDL_image could not initialize! SDL error: " << SDL_GetError() << std::endl;
                    success = false;
                }
            }

            if (TTF_Init() == -1)
            {
                std::cout << "TTF_Text could not initialise! SDL error: " << SDL_GetError() << std::endl;
                success = false;
            }

            gFont_time = TTF_OpenFont("game_resource//dlxfont_.ttf", 15);
            if (gFont_time == NULL)
            {
                success = false;
            }
        }
    }
    return success;
}

bool loadBackground()
{
    bool ret = gBackground.loadMedia("img\\background1.png", gRenderer);
    return ret;
}

void close()
{
    gBackground.Quit();

    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObject*> MakeThreadList()
{
    std::vector<ThreatsObject*> list_threats_;

    ThreatsObject* dynamic_threats = new ThreatsObject[20];
    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats + i);
        if (p_threat != NULL)
        {
            p_threat->loadMedia("img/threat_left.png", gRenderer);
            p_threat->setClips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i * 500);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->setAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);

            list_threats_.push_back(p_threat);
        }
    }


    ThreatsObject* threats_objects_ = new ThreatsObject[20];

    for (int i = 0; i < 20; i++)
    {
        ThreatsObject* p_threat_ = (threats_objects_ + i);
        if (p_threat_ != NULL)
        {
            p_threat_->loadMedia("img/threat_level.png", gRenderer);
            p_threat_->setClips();
            p_threat_->set_x_pos(700 + i * 1200);
            p_threat_->set_y_pos(250);

            p_threat_->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat_->set_input_left(0);

            BulletObject* p_bullet_ = new BulletObject();
            p_threat_->initBullet(p_bullet_, gRenderer);
        }
        list_threats_.push_back(p_threat_);
    }
    return list_threats_;
}

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    if (!init())
    {
        std::cout << "Failed to initialize!\n";
        return -1;
    }
    if (!loadBackground())
    {
        std::cout << "Failed to load background!\n";
    }

    gameMap game_map;
    game_map.loadMap("map/map01.dat");
    game_map.loadTile(gRenderer);

    mainObject p_player;
    p_player.loadMedia("img/player_right.png", gRenderer);
    p_player.setClip();

    PlayPower play_power;
    play_power.Init(gRenderer);

    PlayMoney play_money;
    play_money.Init(gRenderer);
    play_money.setPos(SCREEN_WIDTH * 0.5 - 300, 8);


    std::vector<ThreatsObject*> threats_list = MakeThreadList();

    ExplosionObject exp_main;
    bool tRet = exp_main.loadMedia("img/exp3.png", gRenderer);
    if (tRet != true)
    {
        return -1;
    }
    exp_main.setClip();

    int num_be_wounded = 0;

    TextObject time_game;
    time_game.setColor(TextObject::BLACK_TEXT);

    TextObject mark_game;
    mark_game.setColor(TextObject::BLACK_TEXT);
    UINT mark_value = 0;

    TextObject money_game;
    money_game.setColor(TextObject::BLACK_TEXT);

    bool isQuit = false;
    SDL_Event e;
    while (!isQuit){
        fps_timer.start();

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                isQuit = true;
            }
            std::cout << "e.type: " << e.type << std::endl;
            p_player.handleInputAction(e, gRenderer);

        }
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        Map map_data = game_map.getMap();

        gBackground.render(gRenderer, NULL);

        p_player.HandleBullet(gRenderer);
        p_player.setMapXY(map_data.start_x_, map_data.start_y_);
        p_player.doPlayer(map_data);
        p_player.Show(gRenderer);

        game_map.setMap(map_data);
        game_map.drawMap(gRenderer);

        play_power.Show(gRenderer);
        play_money.Show(gRenderer);

        for (int i = 0; i < threats_list.size(); i++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->implementMoveType(gRenderer);
                p_threat->doPlayer(map_data);
                p_threat->makeBullet(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(gRenderer);

                SDL_Rect rect_player = p_player.get_rect_frame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBullet_list = p_threat->getBulletList();
                for (int j = 0; j < tBullet_list.size(); j++)
                {
                    BulletObject* pt_bullet = tBullet_list.at(j);
                    if (pt_bullet != NULL)
                    {
                        bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->getRect(), rect_player);
                        if (bCol1 == true)
                        {
                            p_threat->removeBullet(j);
                            break;
                        }
                    }
                }

                SDL_Rect rect_threat = p_threat->get_rect_frame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
                if (bCol1 || bCol2)
                {
                    num_be_wounded++;
                    if (num_be_wounded <= 3)
                    {
                        p_player.setRect(0, 0);
                        p_player.setComeBackTime(60);
                        SDL_Delay(100);
                        play_power.Decrease();
                        play_power.render(gRenderer);
                        continue;
                    }
                    else {
                        int result = MessageBoxW(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP);
                        if (result == IDOK)
                        {
                            p_threat->Quit();
                            close();
                            SDL_Quit();

                            return 0;
                        }
                    }
                }
            }
        }

        int frame_exp_width = exp_main.get_frame_width();
        int frame_exp_height = exp_main.get_frame_height();

        std::vector<BulletObject*> bullet_arr = p_player.get_bullet_object();
        for (int r = 0; r < bullet_arr.size(); r++)
        {
            BulletObject* p_bullet = bullet_arr.at(r);
            if (p_bullet != NULL)
            {
                for (int t = 0; t < threats_list.size(); t++)
                {
                    ThreatsObject* obj_threat = threats_list.at(t);
                    if (obj_threat != NULL)
                    {
                        SDL_Rect tRect;
                        tRect.x = obj_threat->getRect().x;
                        tRect.y = obj_threat->getRect().y;
                        tRect.w = obj_threat->get_width_frame();
                        tRect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->getRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
                        if (bCol == true)
                        {
                            mark_value++;
                            for (int ex = 0; ex < NUM_FRAME_EXP; ex++)
                            {
                                int x_pos = p_bullet->getRect().x - frame_exp_width * 0.5;
                                int y_pos = p_bullet->getRect().y - frame_exp_height * 0.5;

                                exp_main.setFrame(ex);
                                exp_main.setRect(x_pos, y_pos);
                                exp_main.Show(gRenderer);
                            }
                            p_player.removeBullet(r);
                            obj_threat->Quit();
                            threats_list.erase(threats_list.begin() + t);
                        }
                    }
                }
            }
        }

        //Show game time
        std::string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 300 - time_val;

        if (val_time <= 0)
        {
            int result = MessageBoxW(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONINFORMATION);
            if (result == IDOK)
            {
                bool isQuit = true;
                break;
            }
        }
        else
        {
            std::string str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.setText(str_time);
            time_game.loadFromRenderText(gFont_time, gRenderer);
            time_game.RenderText(gRenderer, SCREEN_WIDTH - 200, 15);
        }

        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Mark: ");
        strMark += val_str_mark;

        mark_game.setText(strMark);
        mark_game.loadFromRenderText(gFont_time, gRenderer);
        mark_game.RenderText(gRenderer, SCREEN_WIDTH * 0.5 - 50, 15);

        int collected_money = p_player.getCollectedMoney();
        std::string money_str = std::to_string(collected_money);

        money_game.setText(money_str);
        money_game.loadFromRenderText(gFont_time, gRenderer);
        money_game.RenderText(gRenderer, SCREEN_WIDTH * 0.5 - 250, 15);

        SDL_RenderPresent(gRenderer);

        int real_imp_time = fps_timer.getTicks();
        int time_one_flame = 1000 / FRAME_PER_SECOND; //ms
        if (real_imp_time < time_one_flame)
        {
            int delay_time = time_one_flame - real_imp_time;
            SDL_Delay(delay_time);
        }
    }

    for (int i = 0; i < threats_list.size(); i++)
    {
        ThreatsObject* p_threat = threats_list.at(i);
        if (p_threat)
        {
            p_threat->Quit();
            p_threat = NULL;
        }
    }
    threats_list.clear();

    close();
    return 0;
}
