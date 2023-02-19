#include "down-there.h"

int main(int argc, char **argv){
    initscr();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    clear();
    struct Element octopus;

    char **data;
    data = malloc(sizeof (char *) * LINES);
    for (int i = 0; i < LINES; i++){
        data[i] = calloc(COLS, sizeof(char));
    }

    octopus.start.x = COLS*0.5 - 1, octopus.start.y = LINES*0.5 - 1;
    octopus.data = data;
    octopus.size = read_element(octopus.data, "octopus.txt");

    struct Element elements[1];
    elements[0] = octopus;

    initialise(elements, 1);

    int input;
    while ((input = getch()) != 'q'){
        switch (input){
            case 'w':
                // if ! cant_move.up
                move_upwards();
                break;
            case 's':
                move_downwards();
                break;
            case 'a':
                move_left();
                break;
            case 'd':
                move_right();
                break;
        }
        print_map();
    }

    endwin();

    return 0;
}
