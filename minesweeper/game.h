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
@Desc      :   ɨ�׺�����ݴ���ͷ�ļ�
*/
#pragma once
#include "base.h"

class mineMap
{
public:
    int map_data[row][col] = { 0 };

    // ���캯��
    mineMap();
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
    // debugչʾ��ͼ
    void display_map();
    // ��ĳ��ָ�Ϊδ��״̬����ֹ�ظ���
    void recover_block(int x, int y);
};

