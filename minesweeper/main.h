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
@Desc      :   ɨ��������ͷ�ļ�
*/
#pragma once
#include "gui.h"
#include "game.h"

int* get_mouse_action(); // ��ȡ������
int open_blank_block(int x, int y); // ���ո�
void minesweeper_init(); // ��Ϸ�����ʼ��
void mouse_operation(int mouse_action[3]); // ����������
