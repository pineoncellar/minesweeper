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