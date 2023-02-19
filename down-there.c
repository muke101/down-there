#include "down-there.h"

int main(int argc, char **argv){
    struct Element octopus;

    char **data;
    data = malloc(sizeof (char *) * LINES);
    for (int i = 0; i < LINES; i++){
        data[i] = calloc(COLS, sizeof(char));
    }

    octopus.data = data;
    octopus.size = read_element(octopus.data, 'octopus.txt');
    octopus.start.x = 0, octopus.start.y = 0;

    struct Element elements[1];
    elements[0] = octopus;

    initialise(elements, 1);

    int input;
    while ((input = getch()) != 'q'){
        switch (input){
            case 'w':
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
