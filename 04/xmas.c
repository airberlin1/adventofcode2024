#include <stdio.h>
#include <stdlib.h>

int inStr(char c, char * str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == c) return 1;
    }
    return 0;

}


int main(void){
    char fileName[10] = "xmas.in";
    char text[140][140];
    int directions[8][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {1, 0}, {-1, 0}, {0, 1}, {-1, 0}};
    FILE * fp;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        exit(-1);
    }
    char c = fgetc(fp);
    int i = 0;
    int j = 0;

    fflush(stdout);
    for (i = 0; i < 140; i++) {
        for (j = 0; j < 140; j++) {
            text[i][j] = c;
            c = fgetc(fp);
        }
        c = fgetc(fp);
    }
    fclose(fp);
    unsigned count = 0;
    for (i = 0; i < 140; i++) {
        for (j = 0; j < 140; j++) {
            if (text[i][j] == 'X'){
                for (unsigned k = 0; k < 8; k++) {
                    if (i + directions[k][0] < 140 && j + directions[k][1] >= 0) {
                        if (text[i + directions[k][0]][j + directions[k][1]] == 'M') {
                            if (text[i + 2 * directions[k][0]][j + 2 * directions[k][1]] == 'A') {
                                if (text[i + 3 * directions[k][0]][j + 3 * directions[k][1]] == 'S') {
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    unsigned count2 = 0;
    unsigned maybeCount = 0;
    int directions2[4][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (i = 1; i < 139; i++) {
        for (j = 1; j < 139; j++) {
            if (text[i][j] == 'A') {
                maybeCount = 0;
                for (unsigned k = 0; k < 4; k++) {
                    if (text[i + directions2[k][0]][j+directions2[k][1]] == 'M') {
                        if (text[i - directions2[k][0]][j-directions2[k][1]] == 'S') {
                            if (maybeCount) count2++;
                            maybeCount = 1;
                        }
                    }
                }
            }
        }
    }
    printf("%d\n", count);
    printf("%d\n", count2);
    return 0;
}
