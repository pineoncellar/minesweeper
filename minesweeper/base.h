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

#define block_pixel 50  // ����������
#define row 9           // ����
#define col 9           // ����
#define mine_num 10           // ����

bool writeLog(const string& strToWrite); // ��־��¼����

