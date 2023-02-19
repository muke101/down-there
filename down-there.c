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

    octopus.start.x = COLS - 1, octopus.start.y = LINES - 1;
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
        char next_char;
        switch (input) {
            case 'w':
                next_player_loc.y = LINES / 2 - 2;
                next_player_loc.x = COLS / 2 - 1;

                mvinnstr(next_player_loc.y, next_player_loc.x, &next_char, 1);
                switch (next_char) {
                    case ' ':
                    case '~':
                        move_upwards();
                        break;
                }
                break;
            case 's':
                next_player_loc.y = LINES / 2;
                next_player_loc.x = COLS / 2 - 1;

                mvinnstr(next_player_loc.y, next_player_loc.x, &next_char, 1);
                switch (next_char) {
                    case ' ':
                    case '~':
                        move_downwards();
                        break;
                }
                break;
            case 'a':
                next_player_loc.y = LINES / 2 - 1;
                next_player_loc.x = COLS / 2 - 2;

                mvinnstr(next_player_loc.y, next_player_loc.x, &next_char, 1);
                switch (next_char) {
                    case ' ':
                    case '~':
                        move_left();
                        break;
                }
                break;
            case 'd':
                next_player_loc.y = LINES / 2 - 1;
                next_player_loc.x = COLS / 2 ;

                mvinnstr(next_player_loc.y, next_player_loc.x, &next_char, 1);
                switch (next_char) {
                    case ' ':
                    case '~':
                        move_right();
                        break;
                }
                break;
        }
        print_map();
    }

    endwin();

    return 0;
}
