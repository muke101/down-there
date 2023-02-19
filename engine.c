#include "down-there.h"
#include <curses.h>
#include <stdlib.h>

char **level_map;
struct Element *elements;
int num_elems;
struct Tuple map_size;
struct Tuple window_start;

void reallocate_map(){
    if (window_start.y + LINES == map_size.y){
        reallocarray(level_map, map_size.y+LINES, sizeof(char *));
        //fill_map
    }
    else if (window_start.y == 0){
        char **new_map = malloc(sizeof(char *)*(map_size.y+LINES));
        for (int i=0; i < LINES; i++){
            new_map[i] = malloc(sizeof(char)*COLS);
        }
        memcpy(new_map+LINES, level_map, map_size.y*sizeof(char *));
        free(level_map);
        level_map = new_map;
        //fill
    }
    else if (window_start.x == 0){
        for (int y = 0; y < map_size.y; y++){
            char *new_row = malloc(sizeof(char)*(map_size.x+COLS));
            memcpy(new_row+COLS, level_map[y], map_size.x);
            free(level_map[y]);
            level_map[y] = new_row;
        }
    }
    else if (window_start.x == map_size.x){
        for (int y = 0; y < map_size.y; y++){
            reallocarray(level_map[y], map_size.y+COLS, sizeof(char));
        }
    }
}

void move_upwards(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.y += 1;
    }
    window_start.y -= 1;
    reallocate_map();
}

void move_downwards(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.y -= 1;
    }
    window_start.y += 1;
    reallocate_map();
}

void move_left(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.x += 1;
    }
    window_start.x -= 1;
    reallocate_map();
}

void move_right(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.x -= 1;
    }
    window_start.x += 1;
    reallocate_map();
}

void print_map(){
    for (int y = 0; y < LINES; y++){
        for (int x = 0; x < COLS; x++){
            int map_y = window_start.y + y;
            int map_x = window_start.x + x;
            mvaddch(y, x, level_map[map_y][map_x]);
        }
    }

    for (int i=0; i < num_elems; i++){
        struct Element elem = elements[i];
        for (int y=elem.start.y; y < elem.start.y + elem.size.y;  y++){
            for (int x=elem.start.x; x < elem.start.x + elem.size.x; x++){
                if (y >= window_start.y && y < window_start.y + LINES - 1
                    && x >= window_start.x && x < window_start.x + COLS - 1){
                    int elem_y = y - elem.start.y;
                    int elem_x = x - elem.start.x;
                    int window_y = y - window_start.y;
                    int window_x = x - window_start.x;
                    if (elem.data[elem_y][elem_x])
                        mvaddch(window_y, window_x, elem.data[elem_y][elem_x]);
                }
            }
        }
    }

    mvaddch(LINES/2 - 1, COLS/2 - 1, 'O');

    refresh();
}

void initialise(struct Element* elems, int n_elems){
    map_size.y = LINES*2;
    map_size.x = COLS*2;
    window_start.y = LINES - 1;
    window_start.x = COLS - 1;
    elements = elems;
    num_elems = n_elems;

    level_map = malloc(sizeof(char *)*LINES*2);
    for (int i = 0; i < LINES*2; i++){
        level_map[i] = malloc(sizeof(char)*COLS*3);
    }
    srand(time(NULL));
    char c;
    for (int i = 0; i < LINES*2; i++){
        c = (char)(rand() % (127 + 1 - 32) + 32);
        memset(level_map[i], c, COLS*3);
    }

    print_map();
}
