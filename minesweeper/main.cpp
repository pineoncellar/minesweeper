//#define _CRT_SECURE_NO_WARNINGS 1
#include "main.h"

bool DEAD = false;
bool WIN = false;

int* get_mouse_action();

int main()
{
    writeLog("\nstart.\n");
    // 游戏初始化
    mineGui gui;
    mineMap map(row, col);
    gui.init_ui();
    map.init_game();

    int* mouse_action;
    int mouse_x, mouse_y, tmp_block_content;

    while (true)
    {
        gui.update_time();
        mouse_action = get_mouse_action();
        switch (*(mouse_action + 2))
        {
            case 0:continue;
            case 1: // 左键
            { 
                mouse_x = *(mouse_action + 0);
                mouse_y = *(mouse_action + 1);
                
                tmp_block_content = map.left_kick(mouse_x, mouse_y);
                map.display_map();
                switch (tmp_block_content)
                {
                    case -2: continue; // 此格被插旗，直接跳过
                    case -1: {
                        gui.mine_show();
                        while (true)
                        {
                            int ret = MessageBox(GetHWnd(), "你踩到雷了！", "hit", MB_OKCANCEL);
                            if (ret == IDOK)
                            {
                                // 新的一局
                                gui.init_ui();
                                map.init_game();
                                break;
                            }
                            else if (ret == IDCANCEL)
                            {
                                exit(502);
                            }
                        }
                    };
                    default: {
                        gui.left_kick_show(mouse_x, mouse_y, tmp_block_content); 
                    };
                }
                break;
            }
            case 2: 
            {
                mouse_x = *(mouse_action + 0);
                mouse_y = *(mouse_action + 1);

                tmp_block_content = map.right_kick(mouse_x, mouse_y);
                gui.right_kick_show(mouse_x, mouse_y, tmp_block_content);
                break;
            }
            default:break;
        }
        std::cout << "x: " << *(mouse_action) << " y: " << *(mouse_action + 1) << " action: " << *(mouse_action + 2) << std::endl;
    }
}

/*
int main()
{
    initgraph(Col * IMGW, Row * IMGW, EW_SHOWCONSOLE);
    //播放开始音乐
    //music();
    srand((unsigned int)time(NULL));

    int mine[Row][Col] = { 0 };//埋雷区数组

    Showmine(mine);

    //创造图片数组
    IMAGE img[12];

    for (int i = 0; i < 12; i++)
    {
        char filename[50] = { 0 };
        sprintf_s(filename, "./images/%d.jpg", i);
        loadimage(img + i, filename, IMGW, IMGW);
    }
    //主函数*************************************
     //********************************************
    while (true)
    {
        //鼠标操作
        Mouseoperation(mine);
        //转换数组数据到图形
        drapmap(mine, img); // 每次循环更新一次地图
        //判断生死
        if (DEAD)//输了
        {
            int ret = MessageBox(GetHWnd(), "你踩到雷了！", "hit", MB_OKCANCEL);
            if (ret == IDOK)
            {
                Showmine(mine);
                showmap(mine);
                DEAD = false;

            }
            else if (ret == IDCANCEL)
            {
                exit(502);
            }
        }
        else if (WIN)
        {
            int ret = MessageBox(GetHWnd(), "你赢了！是否再来一局？", "hit", MB_OKCANCEL);
            if (ret == IDOK)
            {
                Showmine(mine);
                showmap(mine);
                WIN = false;
            }
            else if (ret == IDCANCEL)
            {
                exit(502);
            }

        }
        int count = 0;
        for (int i = 0; i < Row; i++)
        {
            for (int j = 0; j < Col; j++)
            {
                if (mine[i][j] >= 0 && mine[i][j] <= 8)
                {
                    ++count;
                }
            }
        }
        // std::cout << "count = " << count << std::endl;
        if (count == Row * Col - Num)
        {
            WIN = true;
        }
    }


    getchar();
    return 0;
}
*/

/*
void music()
{
    PlaySound(TEXT("DJ OKAWARI - Luv Letter (情书)"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    PlaySound(TEXT("Dream_It_Possible"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
*/

int* get_mouse_action()
{
    // 定义消息结构体
    ExMessage msg;
    static int mouse_res[3] = { 0 };
    mouse_res[2] = 0;
    if (peekmessage(&msg, EM_MOUSE))
    {
        mouse_res[0] = msg.x / block_pixel; // 鼠标所点下的格子
        mouse_res[1] = msg.y / block_pixel;


        if (msg.message == WM_LBUTTONDOWN) // 左键
        {
            mouse_res[2] = 1;
        }
        else if (msg.message == WM_RBUTTONDOWN)// 右键
        {
            mouse_res[2] = 2;
        }
    }
    return mouse_res;
}