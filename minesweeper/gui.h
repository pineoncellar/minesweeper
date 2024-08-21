#pragma once
#include "base.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

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

public:
    // ���캯������ʾ��ʼ��ͼ��
    mineGui();

    void init_ui();

    // ��ĳ����ʾ0-8ͼ��
    void left_kick_show(int x, int y, int num);

    //
    void right_kick_show(int x, int y, int num);

    void mine_show();

    void update_time();

};