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
@Desc      :   ������������뺯��ͷ�ļ�
*/
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

// ��״̬emoji����
#define emoji_before_num 2
#define emoji_playing_num 2
#define emoji_win_num 2
#define emoji_lose_num 4

bool writeLog(const string& strToWrite); // ��־��¼����

