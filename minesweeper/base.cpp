/*- encoding: utf-8 -*/
/*
�������������[  �����[�������[      �����[���������������[
�����X�T�T�����[�����U���������[    �����U�����X�T�T�T�T�a
�������������X�a�����U�����X�����[  �����U�����������[
�����X�T�T�T�a  �����U�����U�^�����[�����U�����X�T�T�a
�����U          �����U�����U  �^���������U���������������[
�^�T�a          �^�T�a�^�T�a    �^�T�T�T�a�^�T�T�T�T�T�T�a

@Author    :   �ؽ��ϵ���
@Contact   :   pine@hydroroll.team
@License   :   DWTFYWWI LICENSE
@Desc      :   ������������뺯��
*/

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


// ������㷨��ʼ��
random_device rd; // �Ӳ���ϵͳ��ȡһ�������
mt19937_64 mt(rd()); // �����������Ϊ���ӣ�ʹ��÷ɭ��ת�����������
uniform_int_distribution<int> dist(0, row * col); // �趨����������ΧΪrow*col

// ��ȡ�����
int dice()
{
    return dist(mt);
}