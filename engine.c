#include "down-there.h"
#include <curses.h>

void move_upwards(){
    char prev_line[COLS+1];
    for (int i=LINES-2; i >= 0; i--){
        int read = mvinnstr(i, 0, prev_line, COLS);
        prev_line[read+1] = '\0';
        mvaddstr(i+1, 0, prev_line);
    }
    refresh();
}

void move_downwards(){
    char prev_line[COLS+1];
    for (int i=0; i <= LINES-2; i++){
        int read = mvinnstr(i, 0, prev_line, COLS);
        prev_line[read+1] = '\0';
        mvaddstr(i-1, 0, prev_line);
    }
    refresh();
}

void move_right(){
    char prev_char;
    for (int i=0; i < LINES; i++){
        for (int j=0; j < COLS-2; j++){
            int read = mvinnstr(i, j+1, &prev_char, 1);
            mvaddch(i, j, prev_char);
        }
    }
    refresh();
}

void move_left(){
    char prev_char;
    for (int i=0; i < LINES; i++){
        for (int j=COLS-1; j > 0; j--){
            int read = mvinnstr(i, j-1, &prev_char, 1);
            mvaddch(i, j, prev_char);
        }
    }
    refresh();
}

void layer_maps();

void initialise(){
    initscr();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    clear();
    int maxlines = LINES - 1;
    int maxcolumns = COLS - 1;

    for (int i = 0; i < maxlines; i++){
        level_map[i] = malloc(sizeof(char)*COLS);
    }
    for (int i = 0; i < maxlines; i++)[i] = calloc(COLS, sizeof(char));
    }
    srand(time(NULL));
    char c;
    for (int i = 0; i < LINES; i++){
        c = (char)(rand() % (127 + 1 - 32) + 32);
        memset(level_map[i], c, COLS);
    }
    level_map[LINES/2 - 1][COLS/2 - 1] = 'O';

    for (int i = 0; i < LINES; i++){
        mvhline(i, 0, c, COLS);
    }

    refresh();
}
