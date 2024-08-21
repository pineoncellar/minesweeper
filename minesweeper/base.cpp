#include "base.h"

bool writeLog(const string& strToWrite)
{
    std::cout << strToWrite;
    // ��������ļ���������׷��ģʽ���ļ�
    std::ofstream loggerFile("debug.log", std::ios::app);

    // ����ļ��Ƿ�ɹ���
    if (!loggerFile) {
        std::cerr << "Logger File Notationed fail open appended status 'std::ios::app'" << std::endl;
        return false;
    }

    // д���ַ������ļ�
    loggerFile << strToWrite;

    // �ر��ļ�
    loggerFile.close();

    // �ɹ�д��
    return true;
}