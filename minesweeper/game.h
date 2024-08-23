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
@Desc      :   扫雷后端数据处理头文件
*/
#pragma once
#include "base.h"

using std::vector;
using std::tuple;
using std::make_tuple;
using std::array;
using std::find;

class mineMap
{
private:
    int map_row, map_col;

    // 私有函数，修改数组中某一项的值
    void setItem(int x, int y, int value);

public:
    int map_data[row][col] = { 0 };

    // 构造函数，初始化为r行c列的二维数组
    mineMap(int r, int c);

    // 初始化雷格
    void init_game();

    // 左键打开一格，返回值：
    //   -2     -1     0-8     
    // 无操作   雷   周围雷数
    int left_kick(int x, int y);

    // 扫描周围8格的雷数
    int search_mine_around(int x, int y);

    // 右键对某个插旗，设问或取消
    int right_kick(int x, int y);

    void display_map();

    void openBlankBlock(vector<array<int, 3>>& blank_block, int x, int  y);

    void recover_block(int x, int y);
};

