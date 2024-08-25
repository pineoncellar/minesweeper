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
@Desc      :   扫雷后端数据处理
*/
#include "game.h"

mineMap::mineMap()
{}

// 初始化雷格
void mineMap::init_game()
{
    // 全部设0
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            map_data[i][j] = 0;
    //埋雷
    for (int i = 0; i < mine_num;)
    {
        // dice()生成0 - (row*col)的随机数
        int x = dice() / col;
        int y = dice() / row;; // 随机获取x, y

        //std::cout << "i: " << i << "  x: " << x << "  y: " << y << std::endl;
        if (map_data[x][y] == 0) // 如果此格不为炸弹则设为炸弹
        {
            map_data[x][y] = -1;
            i++;
        }
    }
}

// 左键打开一格，返回值：
//   -2     -1     0-8     
// 无操作   雷   周围雷数
int mineMap::left_kick(int x, int y)
{
    if (map_data[x][y] > 8)
    {
        return -2;
    }
    else if (map_data[x][y] == -1)
        return -1;
    else
    {
        map_data[x][y] += 100; // 打开过的格子就+100
        return search_mine_around(x, y);
    }
}

// 扫描周围8格的雷数
int mineMap::search_mine_around(int x, int y)
{
    int mine_around_num = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < row && j >= 0 && j < col) // 确保索引有效，出界则直接略过
            {
                if (map_data[i][j] == -1 || map_data[i][j] == 9 || map_data[i][j] == 19)
                    mine_around_num++;
            }
        }
    }
    return mine_around_num;
}

// 右键对某个插旗，设问或取消。返回：0-取消设问，1-插旗，2-设问，3-此格已被打开，忽略
int mineMap::right_kick(int x, int y)
{
    if (map_data[x][y] < 8)
    {
        map_data[x][y] += 10;
        return 1;
    }
    else if (map_data[x][y] < 18)
    {
        map_data[x][y] += 10;
        return 2;
    }
    else if (map_data[x][y] > 90)
    {
        return 3;
    }
    else
    {
        map_data[x][y] -= 20;
        return 0;
    }
}

// 打印地图
void mineMap::display_map()
{
    writeLog("\n");
    for (int a = 0; a < row; a++)
    {
        for (int b = 0; b < col; b++)
        {
            stringstream ss;     // 将数字通过字符串流转换为字符串
            string mine_num_str;
            ss << map_data[b][a];
            ss >> mine_num_str;
            writeLog(mine_num_str);

            if (map_data[b][a] == 0 || map_data[b][a] == 9)
                writeLog("    ");  // 1位数带4个空格
            else if(map_data[b][a] == 100)
                writeLog("  "); // 100带2
            else 
                writeLog("   "); // 两位数和-1带3个
        }
        writeLog("\n");
    }
}

// 打开空格时会重复调用left_kick，用此函数消除影响
void mineMap::recover_block(int x, int y)
{
    map_data[x][y] -= 100;
}




