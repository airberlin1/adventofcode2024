#include <stdio.h>
#include <stdlib.h>

#define INPUT_LENGTH 1000  // this is obviously really bad because why no generalized inputs but whatever


long long * read_input(){
    long long * locations = (long long *) malloc(sizeof(long long) * 2 * INPUT_LENGTH);
    for (unsigned i = 0; i < INPUT_LENGTH; i++) {
        scanf("%d %d", locations+(2*i), locations+(2 * i)+1);
        if (locations[2*i] < 10000) {
            printf("%d\n", i);
        }
    }
    return locations;
}


void sort_input(long long * locations){
    long long helper;
    for (unsigned j = 0; j < 2; j++){
        for (unsigned i = 0; i < INPUT_LENGTH - 1; i++) {
            for (unsigned k = 0; k < INPUT_LENGTH - 1; k++) {
                if (locations[2 * k + j] > locations[2 * k + j + 2]) {
                    helper = locations[2 * k + j];
                    locations[2 * k + j] = locations[2 * k + j + 2];
                    locations[2 * k + j + 2] = helper;
                }
            }
        }
    }
}


unsigned calculate_distance(long long * locations){
    unsigned distance = 0;
    for (unsigned i = 0; i < INPUT_LENGTH; i++) {
        distance += llabs(locations[2 * i] - locations[2 * i + 1]);
    }
    return distance;
}


void first_star(long long * locations){
    sort_input(locations);
    printf("%u\n", calculate_distance(locations));
}


void second_star(long long * locations){
    unsigned ind_count;
    unsigned similarity_score = 0;
    for (unsigned i = 0; i < INPUT_LENGTH; i++){
        ind_count = 0;
        for (unsigned j = 1; j < INPUT_LENGTH * 2; j+=2) {
            if (locations[2 * i] == locations[j]) {
                ind_count++;
            }
        }
        similarity_score += ind_count * locations[2 * i];
    }
    printf("%u\n", similarity_score);
}


int main(void){
    long long * locations = read_input();
    // first_star(locations);
    second_star(locations);
}
