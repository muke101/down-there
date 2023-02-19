#include "down-there.h"

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
    //free(level_map[0]);
    for (int i=0; i < LINES-1; i++){
        level_map[i] = level_map[i+1];
    }
}

void move_left(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.x += 1;
    }
    for (int i=0; i < LINES; i++){
        for (int j=COLS-1; j > 0; j--){
            level_map[i][j] = level_map[i][j-1];
        }
    }
}

void move_right(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.x -= 1;
    }
    for (int i=0; i < LINES; i++){
        for (int j=0; j < COLS-1; j++){
            level_map[i][j] = level_map[i][j+1];
        }
    }
}

void print_map(){
    for (int y = 0; y < LINES; y++){
        for (int x = 0; x < COLS; x++){
            int level_y = window_start.y + y;
            int level_x = window_start.x + x;
            mvaddch(y, x, level_map[level_y][level_x]);
        }
    }

    for (int i=0; i < num_elems; i++){
        struct Element elem = elements[i];
        for (int y=elem.start.y; y < elem.start.y + elem.size.y && y < LINES; y++){
            for (int x=elem.start.x; x < elem.start.x + elem.size.x && x < COLS; x++){
                int elem_y = y - elem.start.y;
                int elem_x = x - elem.start.x;
                if (elem.data[elem_y][elem_x])
                    mvaddch(y, x, elem.data[elem_y][elem_x]);
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
        level_map[i] = malloc(sizeof(char)*COLS*2);
    }
    srand(time(NULL));
    char c;
    for (int i = 0; i < LINES*2; i++){
        c = (char)(rand() % (127 + 1 - 32) + 32);
        memset(level_map[i], c, COLS);
    }

    print_map();
}
