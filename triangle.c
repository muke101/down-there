#include "down-there.h"

struct Tuple read_element(char **element, char* file){
    char cur_char;
    FILE * fp;
    fp = fopen(file, "r");
    int x=0, y=0, max_x=0;
    fread(&cur_char, 1, 1, fp);
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

            if (x == COLS-1 ){
                cur_char = '*';
                element[y][x] = cur_char;
                break;
            }
            element[y][x] = cur_char;
            x ++;

        }
        else{
            if(x > max_x)
                max_x = x;
            x=0;
            y++;

        }
        fread(&cur_char, 1, 1, fp);
    }

    struct Tuple size;
    size.x = max_x + 1;
    size.y = y+1;
    return size;
}
