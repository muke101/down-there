#include "down-there.h"

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
    for (int i=0; i < LINES; i++){
        c = (char)(rand() % (127 + 1 - 32) + 32);
        mvhline(i, 0, c, COLS);
    }

    mvaddch(LINES/2 - 1, COLS/2 - 1, 'O');

    refresh();
    placeholder();

    getch();
    endwin();

    return 0;
}
