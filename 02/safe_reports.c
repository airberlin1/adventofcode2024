#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define true 1
#define false 0

#define INPUT_LENGTH 1000
#define MAX_REPORT_LENGTH 8

typedef int bool;

bool is_safe(int * report);


int * read_data(char * fileName) {
    FILE * fp;
    int * reports = (int *) malloc(sizeof(int) * INPUT_LENGTH * MAX_REPORT_LENGTH);
    char * line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int num_to_be_read = 0;

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        free(reports);
        exit(-1);
    }

    for (unsigned i = 0; i < INPUT_LENGTH; i++) {
        if ((read = getline(&line, &len, fp) == -1)) exit(-1);        for (unsigned j = 0; j < MAX_REPORT_LENGTH; j++) {
            reports[MAX_REPORT_LENGTH * i + j] = -1;
        }
        unsigned report_ind = 0;
        num_to_be_read = 0;
        for (unsigned j = 0; j < len; j++) {
            char c = line[j];
            if (c == '\0') break;
            if (isspace(c)) {
                reports[MAX_REPORT_LENGTH * i + report_ind] = num_to_be_read;
                report_ind++;
                num_to_be_read = 0;
            } else {
                //convert chars to nums
                num_to_be_read *= 10;
                num_to_be_read += c - '0';
            }
        }
    }

    fclose(fp);
    return reports;
}


void remove_level(int * report, int * edited_report, unsigned level){
    unsigned edited_ind = 0;
    for (unsigned i = 0; i < MAX_REPORT_LENGTH; i++) {
        if (i != level) {
            edited_report[edited_ind] = report[i];
            edited_ind++;
        }
    }
    edited_report[MAX_REPORT_LENGTH - 1] = -1;
}


bool is_barely_safe(int * report, int * edited_report) {
    if (is_safe(report)) {
        return true;
    }
    for (unsigned i = 0; i < MAX_REPORT_LENGTH; i++) {
        remove_level(report, edited_report, i);
        if (is_safe(edited_report)) return true;
    }
    return false;
}


bool is_safe(int * report) {
    bool decreasing = report[0] > report[1];
    for (unsigned i = 0; i < MAX_REPORT_LENGTH - 1; i++) {
        if (report[i + 1] == -1) break;
        if (report[i] == report[i+1]) return false;
        if (abs(report[i] - report[i+1]) > 3) return false;
        if (decreasing && report[i] < report[i+1]) return false;
        if (!decreasing && report[i] > report[i+1]) return false;
    }
    return true;
}


int count_safe_reports(int * reports) {
    int safe_reports = 0;
    for (unsigned i = 0; i < INPUT_LENGTH * MAX_REPORT_LENGTH; i += MAX_REPORT_LENGTH){
        safe_reports += is_safe(reports + i);
    }
    return safe_reports;
}


int count_safe_second_star(int * reports, int * edited_report) {
    int safe_reports = 0;
    for (unsigned i = 0; i < INPUT_LENGTH * MAX_REPORT_LENGTH; i+= MAX_REPORT_LENGTH) {
        safe_reports += is_barely_safe(reports + i, edited_report);
    }
    return safe_reports;
}


void first_star(char * fileName){
    int * reports = read_data(fileName);
    printf("%d\n", count_safe_reports(reports));
    free(reports);
}


void second_star(char * fileName){
   int * reports = read_data(fileName);
   int * edited_report = (int *) malloc(sizeof(int) * MAX_REPORT_LENGTH);
   printf("%d\n", count_safe_second_star(reports, edited_report));
   free(reports);
   free(edited_report);
}


int main(int argc, char * argv[]){
    if (argc != 2) {
        printf("Please specify an input file.");
        return 0;
    }
    //first_star(argv[1]);
    second_star(argv[1]);
    return 0;
}
