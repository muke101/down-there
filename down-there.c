#include "down-there.h"

int main(int argc, char **argv){

    initialise();

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
