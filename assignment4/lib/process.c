/**
 * GNU C libraries used
 * vasprintf
 */

#include <stdio.h>
#include "process.h"

char *process__to_string(struct process_struct *process) {
    char *str = NULL;
    int error = vasprintf(&str, "[id %d : arrival_time %d,  burst_time %d]", process->id, process->arrive_time, process->burst_time);
    if (error == -1) {
        fprintf(stderr, "String allocation failed.");
        str = "";
    }
    return str;
}

struct process_func process_func = {
    process__to_string
};
