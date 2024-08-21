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

bool writeLog(const string& strToWrite); // 日志记录函数

