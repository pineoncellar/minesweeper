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

class mineMap
{
public:
    int map_data[row][col] = { 0 };

    // 构造函数
    mineMap();
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
    // debug展示地图
    void display_map();
    // 将某格恢复为未打开状态，防止重复打开
    void recover_block(int x, int y);
};

