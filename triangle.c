#include "down-there.h"

struct Size read_element(char **element, char* file){
    char cur_char;
    FILE * fp;
    fp = fopen(file, "r");
    int x=0, y=0, max_x=0;
    fread(&cur_char, 1, 1, fp)
    while(cur_char != EOF){
        if(cur_char != '\n'){
            switch (cur_char) {
                case '_':
                    cur_char = ' ';
                    break;
                case ' ':
                    cur_char = 0;
                    break;
            }
            element[y][x] = cur_char;
            x ++;
        }
        else{
            max_x = max(max_x, x);
            if(x < COLS -1){
                element[y][x] = 0;
                x ++;
            }
            else{
                x=0;
                y++;
            }
        }
        fread(&cur_char, 1, 1, fp)
    }

    struct Size size;
    size.x = max_x + 1;
    size.y = y+1;
    return size;
}