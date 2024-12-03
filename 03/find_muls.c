#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define true 1
#define false 0

#define INPUT_LENGTH 3500 * 6

typedef int bool;


char * read_data(char * fileName) {
    FILE * fp;
    char * corrupted_mem = (char *) malloc(sizeof(char) * INPUT_LENGTH);
    char * line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int num_to_be_read = 0;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        free(corrupted_mem);
        exit(-1);
    }
    char c;
    unsigned mem_ind = 0;
    while ((c = fgetc(fp)) != EOF) {
        corrupted_mem[mem_ind] = c;
        mem_ind++;
    }
    corrupted_mem[mem_ind] = '\0';
    fclose(fp);
    return corrupted_mem;
}


bool is_num(char c){
    return (c <= '9' && c >= '0');
}


int next_mul(char * corrupted_mem, unsigned * mem_ind, bool * doo, bool second_star){
    if (*mem_ind > 0) (*mem_ind)--;
    while (corrupted_mem[*mem_ind] != '\0') {
        (*mem_ind)++;
        bool success = true;
        unsigned add_ind = 4;
        unsigned first_num = 0;
        unsigned second_num = 0;
        if (corrupted_mem[*mem_ind] == 'm') {
            if (corrupted_mem[(*mem_ind)+1] != 'u') continue;
            if (corrupted_mem[(*mem_ind)+2] != 'l') continue;
            if (corrupted_mem[(*mem_ind)+3] != '(') continue;
        } else if (corrupted_mem[*mem_ind] == 'd') {

            if (corrupted_mem[(*mem_ind)+1] != 'o') continue;
            if (corrupted_mem[(*mem_ind)+2] != 'n') {

                if (corrupted_mem[(*mem_ind)+2] != '(') continue;
                if (corrupted_mem[(*mem_ind)+3] != ')') continue;
                *doo = true;
            } else {
                if (corrupted_mem[(*mem_ind)+3] != '\'') continue;
                if (corrupted_mem[(*mem_ind)+4] != 't') continue;

                if (corrupted_mem[(*mem_ind)+5] != '(') continue;
                if (corrupted_mem[(*mem_ind)+6] != ')') continue;
                *doo = false;
            }
        } else {
            continue;
        }
        do {
            if (is_num(corrupted_mem[(*mem_ind)+add_ind])) {
                first_num *= 10;
                first_num += corrupted_mem[(*mem_ind)+add_ind] - '0';
                add_ind++;
            } else if (corrupted_mem[(*mem_ind)+add_ind] == ',') {

            } else {
                success = false;
                break;
            }
        } while (corrupted_mem[*mem_ind+add_ind] != ',');
        add_ind++;
        do {
            if (is_num(corrupted_mem[(*mem_ind)+add_ind])) {
                second_num *= 10;
                second_num += corrupted_mem[(*mem_ind)+add_ind] - '0';
                add_ind++;
            } else if (corrupted_mem[(*mem_ind)+add_ind] == ')') {

            } else {
                success = false;
                break;
            }

        } while (corrupted_mem[*mem_ind+add_ind] != ')');
        //printf("%d", success);
        if (success && (!second_star || (*doo))) {
            *mem_ind += 3;
            //printf("%d, %d", first_num, second_num);
            return first_num * second_num;
        }
    }
    return 0;
}


int first_star(char * text) {
    unsigned mem_ind = 0;
    int result = 0;
    bool * hi = (bool *) malloc(sizeof(bool));
    *hi = true;
    while (text[mem_ind] != '\0') {
        result += next_mul(text, &mem_ind, hi, false);
    }
    free(hi);
    return result;
}


int second_star(char * text) {
    unsigned mem_ind = 0;
    int result = 0;
    bool * doo = (bool *) malloc(sizeof(bool));
    *doo = true;
    while (text[mem_ind] != '\0') {
        result += next_mul(text, &mem_ind, doo, true);
    }

    free(doo);
    return result;
}


int main(int argc, char * argv[]){
    char * text = read_data(argv[1]);
    printf("%d\n", first_star(text));
    printf("%d\n", second_star(text));
    free(text);
    return 0;
}
