#pragma once
#include "base.h"

using std::string;
using std::stringstream;
using std::cout;
using std::endl;

// ��ť��
class Button
{
    friend void set_button_style(int state, Button button); // ��Ԫ���������ð�ť��ʽ
private:
    int x;
    int y;
    int width;
    int height;

protected:
    bool isIn(const ExMessage& msg) const;  // �ж�����Ƿ��ڰ�ť����
    std::string text;                      // ��ť�ı�
    bool change_flag;     // ��ť״̬�Ƿ�ı�

public:
    Button(int x = 0, int y = 0, int width = 100, int height = 60, const std::string& text = "��ť");
    bool state(const ExMessage& msg);       // ��ť״̬

    const std::string& getText() const;    // ��ȡ��ť�ı�
    void setText(const std::string& text); // ���ð�ť�ı�

    //  ��ť��ʽ
    int linestyle = PS_SOLID;        //������ʽ
    int button_color = DARKGRAY;        //��ť��ɫ
    int in_color = LIGHTGRAY;       //������ڰ�ť�ϵ���ɫ
    int click_clolor = LIGHTGRAY;  //�����°�ťʱ��ť����ɫ
};


class mineGui
{
private:
    IMAGE img_num[10];
    IMAGE img_icon[3];
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
    time_t now_time;

    Button* restart;
    Button* change_style;

public:
    // ���캯������ʾ��ʼ��ͼ��
    mineGui(int theme);

    void init_ui();

    // ��ĳ����ʾ0-8ͼ��
    void left_kick_show(int x, int y, int num);

    void right_kick_show(int x, int y, int num);

    void mine_show(int map[row][col]);

    void update_time();

    bool button_check(const ExMessage& msg);

    void show_emoji(int state);
};

void set_button_style(int state, Button button);