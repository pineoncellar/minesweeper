#include "gui.h"

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

mineGui::mineGui()
{
    initgraph((row + 2) * block_pixel, col * block_pixel, EW_SHOWCONSOLE); // 初始化窗口

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
    putimage(row * block_pixel, 0, img_panel + 0);
    putimage((row + 0.5) * block_pixel, 0.5 * block_pixel, img_panel + 2);
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
