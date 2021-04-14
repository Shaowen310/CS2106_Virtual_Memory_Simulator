/**
 * CS5250 Assignment 4, Scheduling policies simulator
 * Input file:
 *     input.txt
 * Output files:
 *     FCFS.txt
 *     RR.txt
 *     SRTF.txt
 *     SJF.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include "process.h"

int main (int argc, char** argv) {
    struct process_struct p0 = {0, 5, 10};
    char * str = process_func.to_string(&p0);
    printf("%s\n", str);
    free(str);
    return 0;
}
