#ifndef SCHEDULERS_H  
#define SCHEDULERS_H

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int remaining_time;
    int is_completed;
};

void sort_by_arrival_time(struct process processes[], int n);
void FIFO_Scheduling(struct process processes[], int n);
void RR_Scheduling(struct process processes[], int n, int time_quantom);

#endif
