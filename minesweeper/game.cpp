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
@Desc      :   ɨ�׺�����ݴ���
*/
#include "game.h"

mineMap::mineMap()
{}

// ��ʼ���׸�
void mineMap::init_game()
{
    // ȫ����0
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            map_data[i][j] = 0;
    //����
    for (int i = 0; i < mine_num;)
    {
        // dice()����0 - (row*col)�������
        int x = dice() / col;
        int y = dice() / row;; // �����ȡx, y

        //std::cout << "i: " << i << "  x: " << x << "  y: " << y << std::endl;
        if (map_data[x][y] == 0) // ����˸�Ϊը������Ϊը��
        {
            map_data[x][y] = -1;
            i++;
        }
    }
}

// �����һ�񣬷���ֵ��
//   -2     -1     0-8     
// �޲���   ��   ��Χ����
int mineMap::left_kick(int x, int y)
{
    if (map_data[x][y] > 8)
    {
        return -2;
    }
    else if (map_data[x][y] == -1)
        return -1;
    else
    {
        map_data[x][y] += 100; // �򿪹��ĸ��Ӿ�+100
        return search_mine_around(x, y);
    }
}

// ɨ����Χ8�������
int mineMap::search_mine_around(int x, int y)
{
    int mine_around_num = 0;
    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < row && j >= 0 && j < col) // ȷ��������Ч��������ֱ���Թ�
            {
                if (map_data[i][j] == -1 || map_data[i][j] == 9 || map_data[i][j] == 19)
                    mine_around_num++;
            }
        }
    }
    return mine_around_num;
}

// �Ҽ���ĳ�����죬���ʻ�ȡ�������أ�0-ȡ�����ʣ�1-���죬2-���ʣ�3-�˸��ѱ��򿪣�����
int mineMap::right_kick(int x, int y)
{
    if (map_data[x][y] < 8)
    {
        map_data[x][y] += 10;
        return 1;
    }
    else if (map_data[x][y] < 18)
    {
        map_data[x][y] += 10;
        return 2;
    }
    else if (map_data[x][y] > 90)
    {
        return 3;
    }
    else
    {
        map_data[x][y] -= 20;
        return 0;
    }
}

// ��ӡ��ͼ
void mineMap::display_map()
{
    writeLog("\n");
    for (int a = 0; a < row; a++)
    {
        for (int b = 0; b < col; b++)
        {
            stringstream ss;     // ������ͨ���ַ�����ת��Ϊ�ַ���
            string mine_num_str;
            ss << map_data[b][a];
            ss >> mine_num_str;
            writeLog(mine_num_str);

            if (map_data[b][a] == 0 || map_data[b][a] == 9)
                writeLog("    ");  // 1λ����4���ո�
            else if(map_data[b][a] == 100)
                writeLog("  "); // 100��2
            else 
                writeLog("   "); // ��λ����-1��3��
        }
        writeLog("\n");
    }
}

// �򿪿ո�ʱ���ظ�����left_kick���ô˺�������Ӱ��
void mineMap::recover_block(int x, int y)
{
    map_data[x][y] -= 100;
}




