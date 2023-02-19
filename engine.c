#include "down-there.h"
#include <curses.h>

char **level_map;
struct Element *elements;
int num_elems;
struct Tuple map_size;
struct Tuple window_start;

void reallocate_map(){

}

void move_upwards(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.y += 1;
    }
    window_start.y -= 1;
}

void move_downwards(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.y -= 1;
    }
    window_start.y += 1;
}

void move_left(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.x += 1;
    }
    window_start.x -= 1;
}

void move_right(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.x -= 1;
    }
    window_start.x += 1;
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
                if (y >= window_start.y && y < 2*LINES-1
                    && x >= window_start.x && x < 2*COLS-1){
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
