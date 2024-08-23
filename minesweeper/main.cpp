//#define _CRT_SECURE_NO_WARNINGS 1
#include "main.h"

mineGui gui(0);
mineMap map(row, col);
int remain_block;

int main()
{
    // 刷新随机数种子
    srand((unsigned int)time(NULL));
    // 游戏初始化
    gui.init_ui();
    map.init_game();
    remain_block = row * col;
    cout << "remain_block: " << remain_block << std::endl;

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
                // map.display_map();
                // cout << "x = " << mouse_x << " y = " << mouse_y << " tmp_block_content: " << tmp_block_content << std::endl;
                switch (tmp_block_content)
                {
                    case -2: continue; // 此格被插旗，直接跳过
                    case 10: // 游戏胜利
                    {} 
                    case -1: // 此格是雷
                    {
                        gui.mine_show(map.map_data);
                        while (true)
                        {
                            int ret = MessageBox(GetHWnd(), "你踩到雷了！", "hit", MB_OKCANCEL);
                            if (ret == IDOK)
                            {
                                // 新的一局
                                gui.init_ui();
                                map.init_game();
                                remain_block = row * col;
                                cout << "restart" << endl;
                                break;
                            }
                            else if (ret == IDCANCEL)
                            {
                                exit(502);
                            }
                        }
                        break;
                    }
                    case 0: // 此格为空，需要把周围的空格全开了
                    {
                        map.recover_block(mouse_x, mouse_y);// 消除重复调用left_kick的影响
                        open_blank_block(mouse_x, mouse_y);
                        break;
                    }
                    default: 
                    {
                        remain_block--;
                        gui.left_kick_show(mouse_x, mouse_y, tmp_block_content); 
                        break;
                    };
                }
                if (remain_block == mine_num) // 游戏胜利
                    while (true)
                    {
                        int ret = MessageBox(GetHWnd(), "你胜利了！", "hit", MB_OKCANCEL);
                        if (ret == IDOK)
                        {
                            // 新的一局
                            gui.init_ui();
                            map.init_game();
                            remain_block = row * col;
                            break;
                        }
                        else if (ret == IDCANCEL)
                        {
                            exit(502);
                        }
                    }
                break;
            }
            case 2: 
            {
                mouse_x = *(mouse_action + 0);
                mouse_y = *(mouse_action + 1);

                tmp_block_content = map.right_kick(mouse_x, mouse_y);
                if (tmp_block_content != 3)
                    gui.right_kick_show(mouse_x, mouse_y, tmp_block_content);
                break;
            }
            default:break;
        }
        std::cout << "x: " << *(mouse_action) << " y: " << *(mouse_action + 1) << " action: " << *(mouse_action + 2) << "  remain_block: " << remain_block << std::endl;
    }
}

/*
void music()
{
    PlaySound(TEXT("DJ OKAWARI - Luv Letter (情书)"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    PlaySound(TEXT("Dream_It_Possible"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
*/

int* get_mouse_action()
{
    // 获取鼠标消息
    ExMessage msg;
    msg = getmessage();

    static int mouse_res[3] = { 0 };
    mouse_res[2] = 0;

    // 检查按键
    bool stat = gui.button_check(msg);
    if (stat) // 重开游戏
    {
        while (true)
        {
            int ret = MessageBox(GetHWnd(), "要重新开始吗？", "hit", MB_OKCANCEL);
            if (ret == IDOK)
            {
                // 新的一局
                gui.init_ui();
                map.init_game();
                remain_block = row * col;
                break;
            }
            else if (ret == IDCANCEL)
            {
                break;
            }
        }
    }

    // 分析鼠标按下的键
    mouse_res[0] = msg.x / block_pixel; // 计算鼠标所点下的格子
    mouse_res[1] = msg.y / block_pixel;

    if (mouse_res[0] >= row) // 除去面板上的鼠标点击
        return mouse_res;

    if (msg.message == WM_LBUTTONDOWN) // 按下左键
    {
        mouse_res[2] = 1;
    }
    else if (msg.message == WM_RBUTTONDOWN)// 右键
    {
        mouse_res[2] = 2;
    }
    return mouse_res;
}


// 打开某格，若此格为空则递归检测其周围8格
int open_blank_block(int x, int y)
{
    int tmp_block_content;
    
    tmp_block_content = map.left_kick(x, y);
    if (tmp_block_content == 0) // 此格为空，检测周围8格
    {
        //cout << "x = " << x << ", y = " << y << endl;
        //remain_block--;
        for (int i = x - 1; i <= x + 1; i++)
        {
            for (int j = y - 1; j <= y + 1; j++)
            {
                //cout << "i = " << i << ", j = " << j << endl;
                if (i >= 0 && i < row && j >= 0 && j < col) // 确保在棋盘内且不重复
                {
                    open_blank_block(i, j);
                }
            }
        }
    }
    else if (tmp_block_content == 10) // 游戏胜利
        return 10;
    else if (tmp_block_content == -2) // 此格插了旗或者已经开过了，则啥也不干
        return -1;
    // 为不为空都将此格展示出来
    remain_block--;
    gui.left_kick_show(x, y, tmp_block_content);
    return 0;
}