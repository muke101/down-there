#include "down-there.h"

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
    char prev_line[COLS+1];
    for (int i=0; i <= LINES-1; i++){
        int read = mvinnstr(i, 0, prev_line, COLS);
        prev_line[read+1] = '\0';
        mvaddstr(i-1, 0, prev_line);
    }
    refresh();
}

void initialise(){
    initscr();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    clear();
    int maxlines = LINES - 1;
    int maxcolumns = COLS - 1;

    srand(time(NULL));
    char c;
    for (int i=0; i < LINES; i++){
        c = (char)(rand() % (127 + 1 - 32) + 32);
        mvhline(i, 0, c, COLS);
    }

    mvaddch(LINES/2 - 1, COLS/2 - 1, 'O');

    refresh();
    placeholder();

}
