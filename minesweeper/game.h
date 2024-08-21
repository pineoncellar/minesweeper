#pragma once
#include "base.h"

using std::vector;
using std::tuple;
using std::make_tuple;
using std::array;
using std::find;

class mineMap
{
private:
    vector<vector<int>> map_data;
    int map_row, map_col, remain_block;

    // ˽�к������޸�������ĳһ���ֵ
    void setItem(int x, int y, int value);

public:
    // ���캯������ʼ��Ϊr��c�еĶ�ά����
    mineMap(int r, int c);

    // ��ʼ���׸�
    void init_game();

    // �����һ�񣬷���ֵ��
    //   -2     -1     0-8     
    // �޲���   ��   ��Χ����
    int left_kick(int x, int y);

    // ɨ����Χ8�������
    int search_mine_around(int x, int y);

    // �Ҽ���ĳ�����죬���ʻ�ȡ��
    int right_kick(int x, int y);

    void display_map();

    void openBlankBlock(vector<array<int, 3>>& blank_block, int x, int  y);
};

