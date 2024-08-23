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
@Desc      :   程序基础变量与函数
*/

#include "base.h"

bool writeLog(const string& strToWrite)
{
    std::cout << strToWrite;
    // 构造输出文件流对象，以追加模式打开文件
    std::ofstream loggerFile("debug.log", std::ios::app);

    // 检查文件是否成功打开
    if (!loggerFile) {
        std::cerr << "Logger File Notationed fail open appended status 'std::ios::app'" << std::endl;
        return false;
    }

    // 写入字符串到文件
    loggerFile << strToWrite;

    // 关闭文件
    loggerFile.close();

    // 成功写入
    return true;
}


// 随机数算法初始化
random_device rd; // 从操作系统获取一个随机数
mt19937_64 mt(rd()); // 将此随机数作为种子，使用梅森旋转法生成随机数
uniform_int_distribution<int> dist(0, row * col); // 设定随机数输出范围为row*col

// 获取随机数
int dice()
{
    return dist(mt);
}