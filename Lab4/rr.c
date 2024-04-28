/* ######################################
# University of Information Technology #
# IT007 Operating System               #
# <Nguyen Vo Tien Loc>, <22520792>     #
# File: rr.c			       #
######################################*/

/*#include <stdio.h>

int main()
{
   int i, total = 0, x, limit, counter = 0, t_quantum;
   int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10];
   int process_start[10] = {0};
   int process_end[10] = {0};
   float average_wait_time, average_turnaround_time;

   printf("\nEnter Total Number of Processes: ");
   scanf("%d", &limit);
   x = limit;

   for (i = 0; i < limit; i++)
   {
      printf("\nProvide the details for Process[%d]\n", i + 1);
      printf("Arrival Time:\t");
      scanf("%d", &arrival_time[i]);
      printf("Burst Time:\t");
      scanf("%d", &burst_time[i]);
      temp[i] = burst_time[i];
   }

   printf("\nEnter Time Quantum:\t");
   scanf("%d", &t_quantum);

   printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\t Start Time\t End Time\n");
   for (total = 0, i = 0; x != 0;)
   {
      if (temp[i] <= t_quantum && temp[i] > 0)
      {
         total = total + temp[i];
         temp[i] = 0;
         counter = 1;
         process_end[i] = total;
      }
      else if (temp[i] > 0)
      {
         total = total + t_quantum;
         temp[i] = temp[i] - t_quantum;
      }

      if (temp[i] == 0 && counter == 1)
      {
         x--;
         printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d\t\t %d\t\t %d", i + 1, burst_time[i], total - arrival_time[i], total - arrival_time[i] - burst_time[i], process_start[i], process_end[i]);

         wait_time = wait_time + total - arrival_time[i] - burst_time[i];

         turnaround_time = turnaround_time + total - arrival_time[i];
         counter = 0;
      }

      if (temp[i] > 0 && process_start[i] == 0)
      {
         process_start[i] = total;
      }

      if (i == limit - 1)
      {
         i = 0;
      }
      else if (arrival_time[i + 1] <= total)
      {
         i++;
      }
      else
      {
         i = 0;
      }
   }

   average_wait_time = wait_time * 1.0 / limit;
   average_turnaround_time = turnaround_time * 1.0 / limit;

   printf("\n\nAverage Waiting Time:\t%f", average_wait_time);
   printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);

   return 0;
}*/
/* #include <stdio.h>

#define MAX_PROCESS 10

// Process structure
typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int end_time;
} Process;

// Function to perform Round Robin scheduling
void roundRobin(Process processes[], int n, int quantum) {
    int remaining_processes = n;
    int current_time = 0;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Iterate until all processes are executed
    while (remaining_processes > 0) {
        // Iterate through all processes
        for (int i = 0; i < n; i++) {
            // If process has arrived and has remaining burst time
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
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
                    remaining_processes--;

                    // Set end time
                    processes[i].end_time = current_time;

                    // Calculate turnaround time
                    int turnaround_time = processes[i].end_time - processes[i].arrival_time;

                    // Calculate waiting time
                    int waiting_time = turnaround_time - processes[i].burst_time;
                    total_waiting_time += waiting_time;

                    // Print process details
                    printf("Process %d: Burst Time = %d, Turnaround Time = %d, Waiting Time = %d, Start Time = %d, End Time = %d\n",
                           processes[i].id, processes[i].burst_time, turnaround_time, waiting_time, processes[i].start_time, processes[i].end_time);

                    total_turnaround_time += turnaround_time;
                }
            }
        }
    }

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

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].id = i + 1;
        processes[i].start_time = -1; // Initialize start time as -1 (indicating not started)
    }

    // Perform Round Robin scheduling
    roundRobin(processes, n, quantum);

    return 0;
}
*/
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
