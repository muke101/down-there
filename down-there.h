//
// Created by wenjie on 18/02/23.
//
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <math.h>
#include <string.h>

#ifndef DOWN_THERE_DOWN_THERE_H
#define DOWN_THERE_DOWN_THERE_H

struct Tuple{
    int x;
    int y;
};

struct Element{
    struct Tuple start;
    struct Tuple size;
    char **data;
};

struct Size read_element(char **element, char* file);

void initialise(struct Element* elems);

void print_map();

void move_upwards();

void move_downwards();

void move_right();

void move_left();

#endif //DOWN_THERE_DOWN_THERE_H
