/* ######################################
# University of Information Technology #
# IT007 Operating System               #
# <Nguyen Vo Tien Loc>, <22520792>     #
# File: rr.c			       #
######################################*/

#include <stdio.h>

#define MAX_PROCESS 10

// Process structure
typedef struct {
    int id;
    int burst_time;
    int remaining_time;
    int start_time;
    int end_time;
} Process;

// Function to perform Round Robin scheduling
void roundRobin(Process processes[], int n, int quantum) {
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("---------------------------------------------------------------------\n");
    printf("| Process | Burst Time | Start Time | End Time | Waiting Time | Turnaround Time |\n");
    printf("---------------------------------------------------------------------\n");

    // Iterate until all processes are executed
    while (1) {
        int all_processes_completed = 1;

        // Iterate through all processes
        for (int i = 0; i < n; i++) {
            // If process has remaining burst time
            if (processes[i].remaining_time > 0) {
                all_processes_completed = 0;

                // Set start time if it's the first time the process is executed
                if (processes[i].start_time == -1)
                    processes[i].start_time = current_time;

                // Execute the process for the quantum or its remaining time, whichever is smaller
                int execute_time = (processes[i].remaining_time < quantum) ? processes[i].remaining_time : quantum;
                processes[i].remaining_time -= execute_time;
                
                // Update current time
                current_time += execute_time;

                // If process has finished execution
                if (processes[i].remaining_time == 0) {
                    // Set end time
                    processes[i].end_time = current_time;

                    // Calculate turnaround time
                    int turnaround_time = processes[i].end_time;

                    // Calculate waiting time
                    int waiting_time = turnaround_time - processes[i].burst_time;
                    total_waiting_time += waiting_time;

                    // Print process details in table form
                    printf("|   %2d    |     %2d     |     %2d     |    %2d   |      %2d       |        %2d        |\n",
                           processes[i].id, processes[i].burst_time, processes[i].start_time, processes[i].end_time, waiting_time, turnaround_time);

                    total_turnaround_time += turnaround_time;
                }
            }
        }

        // If all processes are completed, break the loop
        if (all_processes_completed)
            break;
    }

    printf("---------------------------------------------------------------------\n");

    // Calculate average waiting time and average turnaround time
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    // Print average waiting time and average turnaround time
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n, quantum;
    Process processes[MAX_PROCESS];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter burst time for each process: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].id = i + 1;
        processes[i].start_time = -1; // Initialize start time as -1 (indicating not started)
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Perform Round Robin scheduling
    roundRobin(processes, n, quantum);

    return 0;
}
