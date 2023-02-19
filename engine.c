#include "down-there.h"

char **level_map;
struct Element *elements;
int num_elems;
struct Tuple map_size;
struct Tuple window_start;

void move_upwards(){
    for (int i=0; i < num_elems; i++){
        elements[i].start.y += 1;
    }
    window_start.y -= 1;
    //free(level_map[LINES-1]);
    for (int i=LINES-1; i > 0; i--){
        level_map[i] = level_map[i-1];
    }
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
    int maxlines = LINES - 1;
    int maxcolumns = COLS - 1;

    for (int y = 0; y < maxlines; y++)
        for (int x = 0; x < maxcolumns; x++)
            mvaddch(y, x, level_map[y][x]);

    for (int i=0; i < num_elems; i++){
        struct Element elem = elements[i];
        for (int y=elem.start.y; y < elem.size.y && y < maxlines; y++){
            for (int x=elem.start.x; x < elem.size.x && x < maxcolumns; x++){
                if (elem.data[y][x])
                    mvaddch(y, x, elem.data[y][x]);
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
