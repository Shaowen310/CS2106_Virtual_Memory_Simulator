#ifndef PROCESS_H_
#define PROCESS_H_

struct process_struct {
    int id;
    int arrive_time;
    int burst_time;
};

struct process_func {
    char * (* to_string) (struct process_struct *process); 
};

extern struct process_func process_func;

#endif