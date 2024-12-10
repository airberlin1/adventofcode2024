#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

typedef int bool;


int SIZE = 50;

char * readFile(char * fileName) {
    char * text = (char *) malloc(sizeof(char) * SIZE * SIZE);
    FILE * fp;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        free(text);
        exit(-1);
    }
    char c = fgetc(fp);
    int i = 0;
    int j = 0;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            text[i * SIZE + j] = c;
            c = fgetc(fp);
        }
        c = fgetc(fp);
    }
    fclose(fp);
    return text;
}


int * findOccurences(const char * text, int * amount, char c) {

    *amount = 0;
    for (unsigned i = 0; i < SIZE; i++) {
        for (unsigned j = 0; j < SIZE; j++) {
            if (text[i * SIZE + j] == c) (*amount)++;
        }
    }

    int * occurences = (int *) malloc(sizeof(int) * 2 * (*amount));
    unsigned occ_ind = 0;
    for (unsigned i = 0; i < SIZE; i++) {
        for (unsigned j = 0; j < SIZE; j++) {
            if (text[i * SIZE + j] == c) {
                occurences[2 * occ_ind] = i;
                occurences[2 * occ_ind + 1] = j;
                occ_ind++;
            }
        }
    }
    return occurences;
}


bool * initHits() {
    bool * hits = (bool *) malloc(sizeof(bool) * SIZE * SIZE);
    for (unsigned i = 0; i < SIZE; i++) {
        for (unsigned j = 0; j < SIZE; j++) {
            hits[i * SIZE + j] = false;
        }
    }
    return hits;
}


bool inBounds(int x, int y) {
    if (x < 0) return false;
    if (y < 0) return false;
    if (x >= SIZE) return false;
    if (y >= SIZE) return false;
    return true;
}


void checkChar(char * text, bool * hits, char c) {
    int amount = 0;
    int * occurences = findOccurences(text, &amount, c);

    int xDiff;
    int yDiff;
    int x;
    int y;

    for (unsigned i = 0; i < amount; i++) {
        for (unsigned j = i + 1; j < amount; j++) {
            xDiff = occurences[2 * i] - occurences[2 * j];
            yDiff = occurences[2 * i + 1] - occurences[2 * j + 1];

            x = occurences[2 * i];
            y = occurences[2 * i + 1];

            while (inBounds(x, y)) {
                hits[x * SIZE + y] = true;
                x += xDiff;
                y += yDiff;
            }

            x = occurences[2 * j];
            y = occurences[2 * j + 1];

            while (inBounds(x, y)) {
                hits[x * SIZE + y] = true;
                x -= xDiff;
                y -= yDiff;
            }
        }
    }

    free(occurences);
}


int search_way(char * text, int x, int y, char num){
    int count = 0;
    if (!inBounds(x, y)) return 0;
    if (text[x * SIZE + y] != num) return 0;
    if (num == '9') {
        return 1;
    }

    count += search_way(text, x + 1, y, num + 1);
    count += search_way(text, x - 1, y, num + 1);
    count += search_way(text, x, y + 1, num + 1);
    count += search_way(text, x, y - 1, num + 1);
    return count;
}

int countHits(bool * hits) {
    int cnt = 0;
    for (unsigned i = 0; i < SIZE; i++) {
        for (unsigned j = 0; j < SIZE; j++) {
            if (hits[i * SIZE + j]) cnt++;
        }
    }
    return cnt;
}


int checkAllWays(char * text) {
    int count = 0;
    int amount = 0;
    int * occurences = findOccurences(text, &amount, '0');
    for (unsigned i = 0; i < amount; i++) {
        count += search_way(text,occurences[i * 2], occurences[i * 2 + 1], '0');
    }
    free(occurences);
    return count;
}





int main(int argc, char * argv[]){
    SIZE = atoi(argv[2]);

    char * text = readFile(argv[1]);

    int ways = checkAllWays(text);
    printf("%d\n", ways);

    free(text);

    return 0;
}
