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
@Desc      :   扫雷前端gui
*/
#include "gui.h"

extern int linestyle;
extern int button_color;
extern int in_color;
extern int click_clolor;

// 主题图片路径列表
wstring icon_default[13] = {
    L"./images/default/0.png",
    L"./images/default/1.png",
    L"./images/default/2.png",
    L"./images/default/3.png",
    L"./images/default/4.png",
    L"./images/default/5.png",
    L"./images/default/6.png",
    L"./images/default/7.png",
    L"./images/default/8.png",
    L"./images/default/9.png",
    L"./images/default/mine.png",
    L"./images/default/flag.png",
    L"./images/default/puzzle.png",
};

wstring icon_glass[13] = {
    L"./images/glass/0.png",
    L"./images/glass/1.png",
    L"./images/glass/2.png",
    L"./images/glass/3.png",
    L"./images/glass/4.png",
    L"./images/glass/5.png",
    L"./images/glass/6.png",
    L"./images/glass/7.png",
    L"./images/glass/8.png",
    L"./images/glass/9.png",
    L"./images/glass/mine.png",
    L"./images/glass/flag.png",
    L"./images/glass/puzzle.png",
};

wstring icon_classic[13] = {
    L"./images/classic/0.png",
    L"./images/classic/1.png",
    L"./images/classic/2.png",
    L"./images/classic/3.png",
    L"./images/classic/4.png",
    L"./images/classic/5.png",
    L"./images/classic/6.png",
    L"./images/classic/7.png",
    L"./images/classic/8.png",
    L"./images/classic/9.png",
    L"./images/classic/mine.png",
    L"./images/classic/flag.png",
    L"./images/classic/puzzle.png",
};

// 从字符串路径读取图片
void read_img(IMAGE* img, const wchar_t* img_path_str, int num = 0, int r = block_pixel, int c = block_pixel)
{
    wchar_t img_path_char[50] = { 0 };
    wsprintf(img_path_char, img_path_str, num);
    loadimage(img, img_path_char, r, c);
}

// 重载，提供给字符串数组路径使用
void read_img(IMAGE* img, wstring img_path_str, int r = block_pixel, int c = block_pixel)
{
    wchar_t img_path_char[50] = { 0 };
    wcscpy_s(img_path_char, img_path_str.c_str()); // 需先转化成char数组
    loadimage(img, img_path_char, r, c);
}

// 0-默认状态，1-鼠标悬浮，2-鼠标点击
void set_button_style(int state, Button button)
{
    int color = state == 0 ? button.button_color : 1 ? button.in_color : button.click_clolor; // 根据state选取颜色

    // 设置样式
    setlinestyle(button.linestyle, 1);
    setfillcolor(color);
    settextstyle(20, 0, L"微软雅黑");
    // 绘制
    fillrectangle(button.x, button.y, button.x + button.width, button.y + button.height);
    RECT rect = { button.x, button.y, button.x + button.width, button.y + button.height };
    drawtext(button.text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

// 构造函数，读取图片
mineGui::mineGui()
{
    // 输入默认图片数组
    for (int i = 0; i < 10; i++)
    {
        read_img(img_num + i, *(icon_default + i));
    }
    for (int i = 0; i < 3; i++)
    {
        read_img(img_icon + i, *(icon_default + i + 10));
    }
    // 输入时钟图片，需要不同的长宽
    read_img(img_icon + 3, L"./images/clock.jpg", 40, 80);
    // 输入emoji表情
    for (int i = 0; i < emoji_before_num; i++)
    {
        read_img(img_emoji_before + i, L"./images/emoji/before/%d.png", i);
    }
    for (int i = 0; i < emoji_playing_num; i++)
    {
        read_img(img_emoji_playing + i, L"./images/emoji/playing/%d.png", i);
    }
    for (int i = 0; i < emoji_win_num; i++)
    {
        read_img(img_emoji_win + i, L"./images/emoji/win/%d.png", i);
    }
    for (int i = 0; i < emoji_lose_num; i++)
    {
        read_img(img_emoji_lose + i, L"./images/emoji/lose/%d.png", i);
    }
}

// 程序开始前调用，初始化窗口
void mineGui::init_ui()
{
    initgraph((row + 2) * block_pixel, col * block_pixel, EW_SHOWCONSOLE); // 初始化窗口
    setbkcolor(LIGHTGRAY); // 背景颜色
    setbkmode(TRANSPARENT); // 字体背景
    setlinecolor(BLACK); // 线条颜色
    cleardevice(); // 显示背景颜色

    rectangle(row * block_pixel + 10, 280, row * block_pixel + 90, 430); // 绘制矩形
    settextstyle(22, 0, L"微软雅黑");
    RECT rect = { row * block_pixel + 10, 280, row * block_pixel + 90, 310 };
    drawtext(L"更换主题", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    restart = new Button(row * block_pixel + 20, 200, 60, 30, L"重新开始"); // 初始化按钮
    default_theme = new Button(row * block_pixel + 20, 310, 60, 30, L"默认主题");
    glass_theme = new Button(row * block_pixel + 20, 350, 60, 30, L"青青草原");
    classic_theme = new Button(row * block_pixel + 20, 390, 60, 30, L"复古像素");
}

// 游戏开始前调用，初始化游戏地图
void mineGui::init_game()
{
    rectangle(row * block_pixel + 10, 280, row * block_pixel + 90, 430); // 绘制矩形
    settextstyle(22, 0, L"微软雅黑");
    RECT rect = { row * block_pixel + 10, 280, row * block_pixel + 90, 310 };
    drawtext(L"更换主题", &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    // 初始化图像
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            putimage(j * block_pixel, i * block_pixel, img_num + 9);
        }
    }
    show_emoji(0);
    // 初始化计时
    last_second = -1;
    start_time = clock();
    this->update_time();
}

// 修改主题
void mineGui::change_theme(int theme, int map[row][col])
{
    // 读取新的图片数据
    switch (theme)
    {
    case 1: // 默认
    {
        for (int i = 0; i < 10; i++)
        {
            read_img(img_num + i, *(icon_default + i));
        }
        for (int i = 0; i < 3; i++)
        {
            read_img(img_icon + i, *(icon_default + i + 10));
        }
        break;
    }
    case 2: // 草
    {
        for (int i = 0; i < 10; i++)
        {
            read_img(img_num + i, *(icon_glass + i));
        }
        for (int i = 0; i < 3; i++)
        {
            read_img(img_icon + i, *(icon_glass + i + 10));
        }
        break;
    }
    case 3: // 经典
    {
        for (int i = 0; i < 10; i++)
        {
            read_img(img_num + i, *(icon_classic + i));
        }
        for (int i = 0; i < 3; i++)
        {
            read_img(img_icon + i, *(icon_classic + i + 10));
        }
        break;
    }
    }
    //绘制新界面
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < col; y++)
        {
            switch (map[x][y])
            {
            case -1:
            case 0: // 未打开格
            {
                putimage(x * block_pixel, y * block_pixel, img_num + 9);
                break;
            }
            case 9:
            case 10: // 插旗
            {
                putimage(x * block_pixel, y * block_pixel, img_icon + 1);
                break;
            }
            case 19:
            case 20: // 设问
            {
                putimage(x * block_pixel, y * block_pixel, img_icon + 2);
                break;
            }
            default: // 100，已打开格
            {
                // 计算周围雷格数量
                int mine_around_num = 0;
                for (int i = x - 1; i <= x + 1; i++)
                {
                    for (int j = y - 1; j <= y + 1; j++)
                    {
                        if (i >= 0 && i < row && j >= 0 && j < col) // 确保索引有效，出界则直接略过
                        {
                            if (map[i][j] == -1 || map[i][j] == 9 || map[i][j] == 19)
                                mine_around_num++;
                        }
                    }
                }
                putimage(x * block_pixel, y * block_pixel, img_num + mine_around_num);
                break;
            }
            }
        }
    }
}


// 在某格显示0-8图像
void mineGui::left_kick_show(int x, int y, int num)
{
    putimage(x * block_pixel, y * block_pixel, img_num + num);
}

// 在某格显示未打开格图，插旗，设问图像，对应0,1,2
void mineGui::right_kick_show(int x, int y, int num)
{
    if (num == 0)
        putimage(x * block_pixel, y * block_pixel, img_num + 9);
    else
        putimage(x * block_pixel, y * block_pixel, img_icon + num);
}

// 踩雷，显示所有雷格
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
    // 计算时间
    time_t now_time;
    int used_time, minute, second;
    now_time = clock();
    used_time = now_time - start_time;
    second = used_time / 1000 % 60; // 秒
    minute = used_time / (60 * 1000) % 60; // 分

    if (second == last_second) // 减小更新频率，防止闪烁
        return;
    last_second = second;

    wchar_t show_time[20] = {};
    wsprintf(show_time, L"%02d:%02d", minute, second); // 格式化输出

    settextstyle(27, 0, L"微软雅黑");
    RECT rect = { row * block_pixel, 100, row * block_pixel + 100, 150 };
    putimage(row * block_pixel + 10, 100, img_icon + 3); // 显示图片，将旧的时间数字盖去
    drawtext(show_time, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE); // 显示时间
}

// 检查并更新按钮状态，返回某键被按下：-1-无，0-restart，1,2,3三个切换主题按键
int mineGui::button_check(const ExMessage& msg)
{
    if (restart->state(msg))
    {
        writeLog("restart.\n");
        return 0;
    }
    else if (default_theme->state(msg))
    {
        writeLog("default_theme\n");
        return 1;
    }
    else if (glass_theme->state(msg))
    {
        writeLog("glass_theme\n");
        return 2;
    }
    else if (classic_theme->state(msg))
    {
        writeLog("classic_theme\n");
        return 3;
    }
    return -1;
}

// 更新emoji表情，0-before, 1-playing, 2-win, 3-lose
void mineGui::show_emoji(int state)
{
    switch (state)
    {
    case 0:
    {
        // 随机抽取一个表情放置
        putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_emoji_before + (dice() % emoji_before_num));
        break;
    }
    case 1:
    {
        putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_emoji_playing + (dice() % emoji_playing_num));
        break;
    }
    case 2:
    {
        putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_emoji_win + (dice() % emoji_win_num));
        break;
    }
    case 3:
    {
        putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_emoji_lose + (dice() % emoji_lose_num));
        break;
    }
    }
}

Button::Button(int x, int y, int width, int height, const std::wstring& text)
{
    // 变量初始化
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text = text;
    this->change_flag = false;

    set_button_style(0, *this);
}


// 按钮状态检查
bool Button::state(const ExMessage& msg)
{
    if ((msg.message == WM_LBUTTONDOWN) && isIn(msg))	// 按钮被点击
    {

        set_button_style(2, *this);

        change_flag = true;
        return true;
    }
    else if (isIn(msg))	// 鼠标悬浮
    {
        set_button_style(1, *this);

        change_flag = true;
        return false;
    }
    else	// 按钮状态改变时，恢复按钮原来的状态，防止屏闪
    {
        if (change_flag)
        {
            set_button_style(0, *this);
            change_flag = false;
        }
        return false;
    }
}


// 设置按钮文本
void Button::setText(const std::wstring& text)
{
    this->text = text;
}

// 判断鼠标是否在按钮里面
bool Button::isIn(const ExMessage& msg) const
{
    if (msg.x >= this->x && msg.x <= this->x + width && msg.y >= this->y && msg.y <= this->y + height)
    {
        return true;
    }
    return false;
}
