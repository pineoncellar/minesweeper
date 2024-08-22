#pragma once
#include "base.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

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
    std::string text;                      // 按钮文本
    bool change_flag;     // 按钮状态是否改变

public:
    Button(int x = 0, int y = 0, int width = 100, int height = 60, const std::string& text = "按钮");
    bool state(const ExMessage& msg);       // 按钮状态

    const std::string& getText() const;    // 获取按钮文本
    void setText(const std::string& text); // 设置按钮文本

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
    IMAGE img_icon[3];
    IMAGE img_panel[40];

    /*
    IMAGE img_mine;
    IMAGE img_flag;
    IMAGE img_puzzle;
    IMAGE img_panel;
    IMAGE img_emoji_before;
    IMAGE img_emoji_playing;
    IMAGE img_emoji_win;
    IMAGE img_emoji_lose;
    */

    time_t start_time;
    time_t now_time;

    Button* restart;
    Button* change_style;

public:
    // 构造函数，显示初始化图像
    mineGui();

    void init_ui();

    // 在某格显示0-8图像
    void left_kick_show(int x, int y, int num);

    void right_kick_show(int x, int y, int num);

    void mine_show();

    void update_time();

    bool button_check(const ExMessage& msg);
};

void set_button_style(int state, Button button);