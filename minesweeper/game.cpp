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

void mineMap::setItem(int x, int y, int value) 
{
    // ȷ������ֵ��ȷ
    if (x >= 0 && x < map_row && y >= 0 && y < map_col) 
    {
        map_data[x][y] = value;
    }
}

mineMap::mineMap(int r, int c)
{
    map_row = r;
    map_col = c;
}
    
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

    /*
    // ��ĳһ��
    tuple<int, vector<array<int,3>>> open(int row, int col)
    {
        vector<array<int,3>> blank_block(0);
        //array<int, 3> newArray = { 4, 5, 6 };
        //blank_block.push_back(newArray)
        tuple<int, vector<array<int, 3>>> res;

        if (map_data[row][col] == -1) // ����
        {
            res = make_tuple(-1, blank_block);
            return res;
        }
        else
        {
            int mine_around_num = search_mine_around(row, col);

            if (mine_around_num != 0)
            {
                res = make_tuple(mine_around_num, blank_block);
                return res;
            }
            else // ��Χ8��û���ף�ֱ�Ӱ����еĿո���
            {
                openBlankBlock(blank_block, row, col);
                res = make_tuple(0, blank_block);
            }

        }
    }
    */
    
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
            if (i >= 0 && i < map_row && j >= 0 && j < map_col) // ȷ��������Ч��������ֱ���Թ�
            {
                if (map_data[i][j] == -1 || map_data[i][j] == 9||map_data[i][j] == 19)
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

void mineMap::openBlankBlock(vector<array<int, 3>>& blank_block, int x, int  y)
{
    int mine_around_num = search_mine_around(x, y);

    // ������������ӽ�������
    array<int, 3> newArray = { x, y, mine_around_num };
    if (find(blank_block.begin(), blank_block.end(), newArray) != blank_block.end()) // ȷ�����鲻�ظ����
        blank_block.push_back(newArray);

    // ����Χ8�����ף����������Χ8��**δ�����ĸ���**���ο��ո�
    if (mine_around_num == 0)
    {
        for (int i = x - 1; i <= x + 1; i++)
        {
            for (int j = y - 1; j <= y + 1; j++)
            {
                if (i >= 0 && i < map_row && j >= 0 && j < map_col) // ȷ��������Ч
                {
                    mine_around_num = search_mine_around(i, j);
                    if (find(blank_block.begin(), blank_block.end(), newArray) == blank_block.end()) // ȷ�����ظ����ո�
                        openBlankBlock(blank_block, i, j);
                }
            }
        }
    }
}

void mineMap::display_map()
{
    for (int a = 0; a < row; a++)
    {
        for (int b = 0; b < col; b++)
        {
            stringstream ss;     // ������ͨ���ַ�����ת��Ϊ�ַ���
            string mine_num_str;
            ss << map_data[b][a];
            ss >> mine_num_str;
            writeLog(mine_num_str);

            if (map_data[b][a] == 0)
            {
                writeLog("    ");  // 0��4���ո�-1��3
            }
            else
            {
                writeLog("   ");
            }
        }
        writeLog("\n");
    }
    writeLog("\n");
}

// �򿪿ո�ʱ���ظ�����left_kick���ô˺�������Ӱ��
void mineMap::recover_block(int x, int y)
{
    map_data[x][y] -= 100;
}




