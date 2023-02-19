//
// Created by wenjie on 18/02/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <string.h>

#ifndef DOWN_THERE_DOWN_THERE_H
#define DOWN_THERE_DOWN_THERE_H

char **level_map;
char **element_map;

int placeholder();

void initialise();

void move_upwards();

void move_downwards();

void move_right();

void move_left();

#endif //DOWN_THERE_DOWN_THERE_H
