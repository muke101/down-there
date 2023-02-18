#include "down-there.h"

int main(int argc, char **argv){

    initialise();

    int input;
    do {
        switch ((input = getch())){
            case 'w':
                move_upwards();
                break;
            case 's':
                move_downwards();
                break;
            case 'q':
                goto exit;
        }
    } while (true);
    exit:

    endwin();

    return 0;
}
