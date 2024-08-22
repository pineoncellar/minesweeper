#include "gui.h"

extern int linestyle;
extern int button_color;
extern int in_color;
extern int click_clolor;

string img_name[18] = {
    "./images/0.png",
    "./images/1.png",
    "./images/2.png",
    "./images/3.png",
    "./images/4.png",
    "./images/5.png",
    "./images/6.png",
    "./images/7.png",
    "./images/8.png",
    "./images/9.png",
    "./images/mine.png",
    "./images/flag.png",
    "./images/puzzle.png",
    "./images/panel.png",
    "./images/emoji_before.png",
    "./images/emoji_playing.png",
    "./images/emoji_win.png",
    "./images/emoji_lose.png",
};

// 从字符串路径读取图片
void read_img(IMAGE img, string img_path_str)
{
    char img_path_char[block_pixel] = { 0 };
    strcpy_s(img_path_char, img_path_str.c_str()); // 需先转化成char数组
    loadimage(&img, img_path_char, block_pixel, block_pixel);
}

// 重载，提供给图片数组使用
void read_img(IMAGE *img, string img_path_str, int r= block_pixel, int c = block_pixel)
{
    char img_path_char[block_pixel] = { 0 };
    strcpy_s(img_path_char, img_path_str.c_str()); // 需先转化成char数组
    loadimage(img, img_path_char, r, c);
}

// 0-默认状态，1-鼠标悬浮，2-鼠标点击
void set_button_style(int state, Button button)
{
    int color = state == 0 ? button.button_color : 1 ? button.in_color : button.click_clolor; // 根据state选取颜色

    // 设置样式
    setlinestyle(button.linestyle , 1);
    setfillcolor(color);
    settextstyle(20, 0, "微软雅黑");
    // 绘制
    fillrectangle(button.x, button.y, button.x + button.width, button.y + button.height);
    RECT rect = { button.x, button.y, button.x + button.width, button.y + button.height };
    drawtext(button.text.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

mineGui::mineGui()
{
    initgraph((row + 2) * block_pixel, col * block_pixel, EW_SHOWCONSOLE); // 初始化窗口
    setbkcolor(LIGHTGRAY); // 背景颜色
    setbkmode(TRANSPARENT); // 字体背景
    setlinecolor(BLACK); // 线条颜色
    cleardevice(); // 更新窗口状态，显示背景颜色

    // 输入图片数组
    for (int i = 0; i < 10; i++)
    {
        read_img(img_num + i, *(img_name + i));
    }
    for (int i = 0; i < 3; i++)
    {
        read_img(img_icon + i, *(img_name + i+10));
    }
    for (int i = 1; i < 5; i++)
    {
        read_img(img_panel + i, *(img_name + i + 13));
    }
    read_img(img_panel + 0, *(img_name + 13), 100,450);
    /*
    read_img(img_mine, *(img_name + 10));
    read_img(img_flag, *(img_name + 11));
    read_img(img_puzzle, *(img_name + 12));
    read_img(img_panel, *(img_name + 13));
    read_img(img_emoji_before, *(img_name + 14));
    */
}

void mineGui::init_ui()
{
    // 初始化图像
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            putimage(j * block_pixel, i * block_pixel, img_num + 9);
        }
    }
    // putimage(row * block_pixel, 0, img_panel + 0);
    putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_panel + 2);

    restart = new Button(row * block_pixel + 12, 300, 75, 30, "重新开始");
    change_style = new Button(row * block_pixel + 12, 350, 75, 30, "切换主题");
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

void mineGui::mine_show()
{
    
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
    }
}


Button::Button(int x, int y, int width, int height, const std::string& text)
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

// 按钮状态
bool Button::state(const ExMessage& msg)
{
    if (msg.message == WM_MOUSEMOVE && isIn(msg))	// 鼠标悬浮
    {
        set_button_style(1, *this);

        change_flag = true;
        return false;
    }
    else if ((msg.message == WM_LBUTTONUP) && isIn(msg))	// 按钮被点击
    {
        set_button_style(2, *this);

        change_flag = true;
        return true;
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

// 获取按钮文本
const std::string& Button::getText() const
{
    return text;
}

// 设置按钮文本
void Button::setText(const std::string& text)
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
