#pragma once
#include "gui.h"
#include "game.h"

using std::string;
using std::stringstream;

int* get_mouse_action();
int open_blank_block(int x, int y);
void minesweeper_init();
void mouse_operation(int mouse_action[3]);
