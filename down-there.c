#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

int main(int argc, char **argv){
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    clear();
    int maxlines = LINES - 1;
    int maxcolumns = COLS - 1;

    srand(time(NULL));
    char c;
    for (int i; i < LINES; i++){
        c = (char)(rand() % (127 + 1 - 32) + 32);
        mvhline(i, 0, c, COLS);
    }

    mvaddch(LINES/2, COLS/2, 'O');

    refresh();
    getch();
    endwin();

    return 0;
}
