#pragma once
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <tuple>
#include <array>
#include <easyx.h>
#include <graphics.h>
#include <time.h>


using std::string;
using std::stringstream;

#define block_pixel 50  // 格子像素数
#define row 9           // 行数
#define col 9           // 列数
#define mine_num 10           // 列数

// 各状态emoji数量
#define emoji_before_num 2
#define emoji_playing_num 2
#define emoji_win_num 2
#define emoji_lose_num 4

bool writeLog(const string& strToWrite); // 日志记录函数

