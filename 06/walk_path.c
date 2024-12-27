#include <stdio.h>
#include <stdlib.h>

int main(void){
    char fileName[10] = "map.in";
    char text[130][130];
    int directions[8][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    FILE * fp;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        exit(-1);
    }
    char c = fgetc(fp);
    int i = 0;
    int j = 0;
    int starti;
    int startj;
    fflush(stdout);
    for (i = 0; i < 130; i++) {
        for (j = 0; j < 130; j++) {
            text[i][j] = c;
            if (c == '^') {
                starti = i;
                startj = j;
            }
            c = fgetc(fp);
        }
        c = fgetc(fp);
    }
    fclose(fp);


    int count = 0;
    for (i = 0; i < 130; i++) {
        for (j = 0; j < 130; j++) {

        }
    }


    return 0;

}
