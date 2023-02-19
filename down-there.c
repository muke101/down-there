#include "down-there.h"

int main(int argc, char **argv){
    initscr();
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    clear();

    char **data;

    struct Element octopus;
    data = malloc(sizeof (char *) * LINES);
    for (int i = 0; i < LINES; i++){
        data[i] = calloc(COLS, sizeof(char));
    }

    octopus.start.x = COLS*0.5 - 1, octopus.start.y = LINES*0.5 - 1;
    octopus.data = data;
    octopus.size = read_element(octopus.data, "octopus.txt");

    struct Element miku;
    data = malloc(sizeof (char *) * LINES);
    for (int i = 0; i < LINES; i++){
        data[i] = calloc(COLS, sizeof(char));
    }

    miku.start.x = 1, miku.start.y = 1;
    miku.data = data;
    miku.size = read_element(miku.data, "miku.txt");


    struct Element elements[2];
    elements[0] = octopus;
    elements[1] = miku;

    initialise(elements, 2);

    int input;
    struct Tuple next_player_loc;

    while ((input = getch()) != 'q'){
        switch (input) {
            case 'w':
                next_player_loc.y = LINES / 2;
                next_player_loc.x = COLS / 2 - 1;

                char above_char;
                mvinnstr(next_player_loc.y, next_player_loc.x, &above_char, 1);
                switch (above_char) {
                    case ' ':
                    case '~':
                        move_upwards();
                        break;
                }
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
