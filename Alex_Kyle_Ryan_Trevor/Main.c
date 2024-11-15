#include <std.h>
#include "Schedulers.h"

void sort_by_arrival_time(struct process processes[], int n){
    //Sort the processes by arrival time using insertion sort
    for(int i = 1; i < n; i++){
        struct process key = processes[i];
        int j = i - 1;
        
        //Move the elements that are greater then the key to one position ahead
        while(j >=0 && processes[j].arrival_time > key.arrival_time){
            processes[j + 1] = processes[j];
            j--;
        }

        processes[j+1] = key;
    }
}
void FIFO_Scheduling(struct process processes[], int n){
    //Sort the processes by arrival time using insertion sort
    sort_by_arrival_time(processes, n);

    //Start FIFO processes
    int current_time = 0;

    for(int i =0; i < n; i++){
        // Wait if the current time is less than the process's arrival time
        //Takes care of CPU idle time
        if(current_time < processes[i].arrival_time){
            printf("CPU idle from %d to %d\n", current_time, processes[i].arrival_time);
            current_time = processes[i].arrival_time;
        }

        //Calculate the current time after the current process completes
        printf("Process %d starts at time %d\n", processes[i].pid, current_time);
        current_time += processes[i].burst_time;
        printf("Process %d ends at time %d\n", processes[i].pid, current_time);

        //Calculate the processes completion, turnaround, and waiting time
        processes[i].completion_time = current_time;
        processes[i].turnaround_time = current_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }

    //Display results after if we want to use a function instead of printing in the method like above
    //printf("After scheduling:\n");
    //....
}

void RR_Scheduling(struct process processes[], int n, int time_quantom){
    //Sort the processes by arrival time using insertion sort
    sort_by_arrival_time(processes, n);

    //Start Round Robin process
    int current_time = 0;
    int done;

    do{
        //Start by assuming all processes are done
        done = 1;

        //Iterate through processes to check next round
        for(int i = 0; i < n; i++){
            if(processes[i].remaining_time > 0){
                //Not all processes are done
                done = 0;

                //Handle CPU idle time
                if(processes[i].arrival_time > current_time){
                    //Find the earliest arrival time of remaining process
                    int earliest_arrival = processes[i].arrival_time;
                    for(int j = 0; j < n; j++){
                        if (processes[j].remaining_time > 0 && processes[j].arrival_time < earliest_arrival) {
                            earliest_arrival = processes[j].arrival_time;
                        }
                    }

                    // Move current time to the earliest available process
                    current_time = earliest_arrival;
                }

                //Exacute process for the time quantom or remaing time
                if(processes[i].arrival_time <= current_time){
                    int time_to_exacute = processes[i].remaining_time < time_quantom? processes[i].remaining_time:time_quantom;
                    //Print process exacuting and current time 
                    printf("Process %d executes for %d units from time %d\n", processes[i].pid, time_to_exacute, current_time);

                    //Update remainging and current time
                    current_time += time_to_exacute;
                    processes[i].remaining_time -= time_to_exacute;
                    
                    if(processes[i].remaining_time == 0){
                        processes[i].completion_time = current_time;
                        printf("Process %d completes at time %d\n", processes[i].pid, current_time);
                    }
                }
            }
        }

    }while(!done);

    //Calculate turnaround and waiting time for each process
    for(int i = 0; i < n; i++){
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
    }


    //Display results after if we want to use a function instead of printing in the method like above
   // printf("After Scheduling:\n"); ...
}
int main(void){

}
