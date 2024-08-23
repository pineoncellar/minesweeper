#include "gui.h"

extern int linestyle;
extern int button_color;
extern int in_color;
extern int click_clolor;

string icon_default[13] = {
    "./images/default/0.png",
    "./images/default/1.png",
    "./images/default/2.png",
    "./images/default/3.png",
    "./images/default/4.png",
    "./images/default/5.png",
    "./images/default/6.png",
    "./images/default/7.png",
    "./images/default/8.png",
    "./images/default/9.png",
    "./images/default/mine.png",
    "./images/default/flag.png",
    "./images/default/puzzle.png",
};

string icon_glass[13] = {
    "./images/glass/0.png",
    "./images/glass/1.png",
    "./images/glass/2.png",
    "./images/glass/3.png",
    "./images/glass/4.png",
    "./images/glass/5.png",
    "./images/glass/6.png",
    "./images/glass/7.png",
    "./images/glass/8.png",
    "./images/glass/9.png",
    "./images/glass/mine.png",
    "./images/glass/flag.png",
    "./images/glass/puzzle.png",
};

string icon_classic[13] = {
    "./images/classic/0.png",
    "./images/classic/1.png",
    "./images/classic/2.png",
    "./images/classic/3.png",
    "./images/classic/4.png",
    "./images/classic/5.png",
    "./images/classic/6.png",
    "./images/classic/7.png",
    "./images/classic/8.png",
    "./images/classic/9.png",
    "./images/classic/mine.png",
    "./images/classic/flag.png",
    "./images/classic/puzzle.png",
};

// �ӵ��ַ���·����ȡͼƬ
void read_img(IMAGE *img, const char *img_path_str,int num, int r = block_pixel, int c = block_pixel)
{
    char img_path_char[50] = { 0 };
    sprintf_s(img_path_char, img_path_str, num);
    loadimage(img, img_path_char, r, c);
}

// ���أ��ṩ���ַ�������·��ʹ��
void read_img(IMAGE *img, string img_path_str, int r= block_pixel, int c = block_pixel)
{
    char img_path_char[50] = { 0 };
    strcpy_s(img_path_char, img_path_str.c_str()); // ����ת����char����
    loadimage(img, img_path_char, r, c);
}

// 0-Ĭ��״̬��1-���������2-�����
void set_button_style(int state, Button button)
{
    int color = state == 0 ? button.button_color : 1 ? button.in_color : button.click_clolor; // ����stateѡȡ��ɫ

    // ������ʽ
    setlinestyle(button.linestyle , 1);
    setfillcolor(color);
    settextstyle(20, 0, "΢���ź�");
    // ����
    fillrectangle(button.x, button.y, button.x + button.width, button.y + button.height);
    RECT rect = { button.x, button.y, button.x + button.width, button.y + button.height };
    drawtext(button.text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

mineGui::mineGui(int theme = 0)
{
    initgraph((row + 2) * block_pixel, col * block_pixel, EW_SHOWCONSOLE); // ��ʼ������
    setbkcolor(LIGHTGRAY); // ������ɫ
    setbkmode(TRANSPARENT); // ���屳��
    setlinecolor(BLACK); // ������ɫ
    cleardevice(); // ���´���״̬����ʾ������ɫ

    // ����Ĭ��ͼƬ����
    for (int i = 0; i < 10; i++)
    {
        read_img(img_num + i, *(icon_default + i));
    }
    for (int i = 0; i < 3; i++)
    {
        read_img(img_icon + i, *(icon_default + i+10));
    }
    // ����emoji����
    for (int i = 0; i < emoji_before_num; i++)
    {
        read_img(img_emoji_before + i, "./images/emoji/before/%d.png", i);
    }
    for (int i = 0; i < emoji_playing_num; i++)
    {
        read_img(img_emoji_playing + i, "./images/emoji/playing/%d.png", i);
    }
    for (int i = 0; i < emoji_win_num; i++)
    {
        read_img(img_emoji_win + i, "./images/emoji/win/%d.png", i);
    }
    for (int i = 0; i < emoji_lose_num; i++)
    {
        read_img(img_emoji_lose + i, "./images/emoji/lose/%d.png", i);
    }
    // ��ʼ����ť
    restart = new Button(row * block_pixel + 12, 300, 75, 30, "���¿�ʼ");
    change_style = new Button(row * block_pixel + 12, 350, 75, 30, "�л�����");
}

void mineGui::init_ui()
{
    // ��ʼ��ͼ��
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            putimage(j * block_pixel, i * block_pixel, img_num + 9);
        }
    }
    show_emoji(0);
    // putimage(row * block_pixel, 0, img_panel + 0);
    // putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_panel + 2);
}

// ��ĳ����ʾ0-8ͼ��
void mineGui::left_kick_show(int x, int y, int num)
{
    putimage(x * block_pixel, y * block_pixel, img_num + num);
}

// ��ĳ����ʾδ�򿪸�ͼ�����죬����ͼ�񣬶�Ӧ0,1,2
void mineGui::right_kick_show(int x, int y, int num)
{
    if (num == 0)
        putimage(x * block_pixel, y * block_pixel, img_num + 9);
    else
        putimage(x * block_pixel, y * block_pixel, img_icon + num);
}

// ���ף���ʾ�����׸�
void mineGui::mine_show(int map[row][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (map[i][j] == -1 || map[i][j] == 9 || map[i][j] == 19)
                putimage(i * block_pixel, j * block_pixel, img_icon + 0);
        }
    }
}

void mineGui::update_time()
{
    
}

bool mineGui::button_check(const ExMessage& msg)
{
    if (restart->state(msg))
    {
        cout << "restart." << endl;
        return true;
    }
    else if (change_style->state(msg))
    {
        cout << "change_style" << endl;
        return false;
    }
}

// ����emoji���飬0-before, 1-playing, 2-win, 3-lose
void mineGui::show_emoji(int state)
{
    switch (state)
    {
    case 0:
    {
        // �����ȡһ���������
        putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_emoji_before + (rand() % emoji_before_num));
        break;
    }
    case 1:
    {
        putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_emoji_playing + (rand() % emoji_playing_num));
        break;
    }
    case 2:
    {
        putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_emoji_win + (rand() % emoji_win_num));
        break;
    }
    case 3:
    {
        putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_emoji_lose + (rand() % emoji_lose_num));
        break;
    }
    }
}


Button::Button(int x, int y, int width, int height, const std::string& text)
{
    // ������ʼ��
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = text;
    this->change_flag = false;

    set_button_style(0, *this);
}

// ��ť״̬
bool Button::state(const ExMessage& msg)
{
    if (msg.message == WM_MOUSEMOVE && isIn(msg))	// �������
    {
        set_button_style(1, *this);

        change_flag = true;
        return false;
    }
    else if ((msg.message == WM_LBUTTONUP) && isIn(msg))	// ��ť�����
    {
        set_button_style(2, *this);

        change_flag = true;
        return true;
    }
    else	// ��ť״̬�ı�ʱ���ָ���ťԭ����״̬����ֹ����
    {
        if (change_flag)
        {
            set_button_style(0, *this);
            change_flag = false;
        }
        return false;
    }
}

// ��ȡ��ť�ı�
const std::string& Button::getText() const
{
    return text;
}

// ���ð�ť�ı�
void Button::setText(const std::string& text)
{
    this->text = text;
}

// �ж�����Ƿ��ڰ�ť����
bool Button::isIn(const ExMessage& msg) const
{
    if (msg.x >= this->x && msg.x <= this->x + width && msg.y >= this->y && msg.y <= this->y + height)
    {
        return true;
    }
    return false;
}
