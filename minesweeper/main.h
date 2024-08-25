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
@Desc      :   扫雷主流程头文件
*/
#pragma once
#include "gui.h"
#include "game.h"

int* get_mouse_action(); // 获取鼠标操作
int open_blank_block(int x, int y); // 开空格
void minesweeper_init(); // 游戏整体初始化
void mouse_operation(int mouse_action[3]); // 处理鼠标操作
