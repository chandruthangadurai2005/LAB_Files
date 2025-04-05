#include<stdio.h>

typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void print(Process processes[], int n) {
    printf("P#\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            processes[i].id,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].completion_time,
            processes[i].turnaround_time,
            processes[i].waiting_time);
    }
}

void sjf(Process processes[], int n) {
    int current_time = 0, completed = 0;
    while (completed < n) {
        int min_remaining_time = 9999;
        int short_ind = -1;

        // Find the process with the shortest remaining burst time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                short_ind = i;
            }
        }

        // If a process is found, reduce its remaining time
        if (short_ind != -1) {
            processes[short_ind].remaining_time--;
            current_time++;

            // If the process is finished, calculate its completion time and other metrics
            if (processes[short_ind].remaining_time == 0) {
                processes[short_ind].completion_time = current_time;
                processes[short_ind].turnaround_time = processes[short_ind].completion_time - processes[short_ind].arrival_time;
                processes[short_ind].waiting_time = processes[short_ind].turnaround_time - processes[short_ind].burst_time;
                completed++;
            }
        } else {
            // If no process is ready to execute, increase time
            current_time++;
        }
    }
    print(processes, n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = -1;
    }

    sjf(processes, n);
    return 0;
}

