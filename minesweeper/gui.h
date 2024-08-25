/*- encoding: utf-8 -*/
/*
██████╗  ██╗███╗      ██╗███████╗
██╔══██╗██║████╗    ██║██╔════╝
██████╔╝██║██╔██╗  ██║█████╗
██╔═══╝  ██║██║╚██╗██║██╔══╝
██║          ██║██║  ╚████║███████╗
╚═╝          ╚═╝╚═╝    ╚═══╝╚══════╝

@Author    :   地窖上的松
@Contact   :   pine@hydroroll.team
@License   :   DWTFYWWI LICENSE
@Desc      :   扫雷前端gui头文件
*/
#pragma once
#include "base.h"

// 按钮类
class Button
{
    friend void set_button_style(int state, Button button); // 友元函数，设置按钮格式
private:
    int x;
    int y;
    int width;
    int height;

protected:
    bool isIn(const ExMessage& msg) const;  // 判断鼠标是否在按钮里面
    wstring text;                      // 按钮文本
    bool change_flag;     // 按钮状态是否改变

public:
    Button(int x = 0, int y = 0, int width = 100, int height = 60, const std::wstring& text = L"按钮");
    bool state(const ExMessage& msg);       // 按钮状态

    const wstring& getText() const;    // 获取按钮文本
    void setText(const std::wstring& text); // 设置按钮文本

    //  按钮样式
    int linestyle = PS_SOLID;        //线条样式
    int button_color = DARKGRAY;        //按钮颜色
    int in_color = LIGHTGRAY;       //当鼠标在按钮上的颜色
    int click_clolor = LIGHTGRAY;  //当按下按钮时按钮的颜色
};


class mineGui
{
private:
    IMAGE img_num[10];
    IMAGE img_icon[4]; // mine, flag, puzzle, clock
    IMAGE img_emoji_before[emoji_before_num];
    IMAGE img_emoji_playing[emoji_playing_num];
    IMAGE img_emoji_win[emoji_win_num];
    IMAGE img_emoji_lose[emoji_lose_num];

    /*
    IMAGE img_mine;
    IMAGE img_flag;
    IMAGE img_puzzle;
    IMAGE img_panel;
    */

    time_t start_time;
    int last_second;

    Button* restart;
    Button* default_theme;
    Button* glass_theme;
    Button* classic_theme;

public:
    // 构造函数，显示初始化图像
    mineGui();

    void init_ui();
    void init_game();

    // 在某格显示0-8图像
    void left_kick_show(int x, int y, int num);

    void right_kick_show(int x, int y, int num);

    void mine_show(int map[row][col]);

    void update_time();

    int button_check(const ExMessage& msg);

    void show_emoji(int state);

    void change_theme(int theme, int map[row][col]);
};

void set_button_style(int state, Button button);