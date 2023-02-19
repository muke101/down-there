#include "down-there.h"

char **level_map;
struct Element *elements;
int num_elems;
struct Tuple map_size;
struct Tuple window_start;

void reallocate_map(){
    if (window_start.y + LINES >= map_size.y){
        char **new_map = malloc(sizeof(char *)*(map_size.y+LINES));
        for (int i=map_size.y; i < map_size.y+LINES; i++){
            new_map[i] = malloc(sizeof(char)*map_size.x);
            memset(new_map[i], 'x', map_size.x);
        }
        memcpy(new_map, level_map, map_size.y*sizeof(char *));
        free(level_map);
        level_map = new_map;
        struct Tuple start, end;
        start.y = map_size.y, end.y = map_size.y+LINES;
        start.x = 0, end.x = map_size.x;
        fill_map(start, end);
        map_size.y += LINES;
    }
    else if (window_start.y == 0){
        char **new_map = malloc(sizeof(char *)*(map_size.y+LINES));
        for (int i=0; i < LINES; i++){
            new_map[i] = malloc(sizeof(char)*map_size.x);
        }
        memcpy(new_map+LINES, level_map, map_size.y*sizeof(char *));
        free(level_map);
        level_map = new_map;
        struct Tuple start, end;
        start.y = 0, end.y = LINES;
        start.x = 0, end.x = map_size.x;
        fill_map(start, end);
        map_size.y += LINES;
        window_start.y += LINES;
        for (int i=0; i < num_elems; i++){
            elements[i].start.y += LINES;
        }
    }
    else if (window_start.x == 0){
        for (int y = 0; y < map_size.y; y++){
            char *new_row = malloc(sizeof(char)*(map_size.x+COLS));
            memcpy(new_row+COLS, level_map[y], map_size.x);
            free(level_map[y]);
            level_map[y] = new_row;
        }
        struct Tuple start, end;
        start.y = 0, end.y = map_size.y;
        start.x = 0, end.x = COLS;
        fill_map(start, end);
        map_size.x += COLS;
        window_start.x += COLS;
        for (int i=0; i < num_elems; i++){
            elements[i].start.x += COLS;
        }
    }
    else if (window_start.x + COLS >= map_size.x){
        for (int y = 0; y < map_size.y; y++){
            char *new_row = malloc(sizeof(char)*(map_size.x+COLS));
            memcpy(new_row, level_map[y], map_size.x);
            free(level_map[y]);
            level_map[y] = new_row;
        }
        struct Tuple start, end;
        start.y = 0, end.y = map_size.y;
        start.x = map_size.x, end.x = map_size.x+COLS;
        fill_map(start, end);
        map_size.x += COLS;
    }
}

void move_upwards(){
    /* for (int i=0; i < num_elems; i++){ */
    /*     elements[i].start.y += 1; */
    /* } */
    window_start.y -= 1;
    reallocate_map();
}

void move_downwards(){
    /* for (int i=0; i < num_elems; i++){ */
    /*     elements[i].start.y -= 1; */
    /* } */
    window_start.y += 1;
    reallocate_map();
}

void move_left() {
    /* for (int i = 0; i < num_elems; i++) { */
    /*     elements[i].start.x += 1; */
    /* } */
    window_start.x -= 1;
    reallocate_map();
}

void move_right(){
    /* for (int i=0; i < num_elems; i++){ */
    /*     elements[i].start.x -= 1; */
    /* } */
    window_start.x += 1;
    reallocate_map();
}


void trigger_convo(){
    struct Tuple convo_start;
    struct Tuple convo_size;
    convo_size.x = COLS - 2;
    convo_size.y = 10;
    convo_start.x = 0;
    convo_start.y = LINES - 13;

    for (int y = convo_start.y; y < convo_start.y + convo_size.y; y++) {
        for (int x = convo_start.x; x < convo_start.x + convo_size.x; x++) {
            mvaddch(y, x, '_');
        }
    }
    refresh();
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

void fill_map(struct Tuple start, struct Tuple end){
    srand(time(NULL));
    int c_gen, c;
    for (int i = start.y; i < end.y; i++) {
        c_gen = rand() % 2;
        switch (c_gen) {
            case 0:
                c = '~';
                break;
            case 1:
                c = ' ';
                break;
        }
        char *row = level_map[i];
        memset(row+start.x, (char)c, end.x-start.x);
    }
}

void initialise(struct Element* elems, int n_elems){
    map_size.y = LINES+1;
    map_size.x = COLS+1;
    window_start.y = 1;
    window_start.x = 1;
    elements = elems;
    num_elems = n_elems;

    level_map = malloc(sizeof(char *)*map_size.y);
    for (int i = 0; i < map_size.y; i++){
        level_map[i] = malloc(sizeof(char)*map_size.x);
    }
    struct Tuple start, end;
    start.y = 0, start.x = 0;
    end.y = map_size.y, end.x = map_size.x;
    fill_map(start, end);

    print_map();
}
