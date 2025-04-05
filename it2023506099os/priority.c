#include <stdio.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
    int priority;
} Process;

// Function to calculate waiting time
void calculateWaitingTime(Process processes[], int n) {
    int total_time = 0; // Total elapsed time
    for (int i = 0; i < n; i++) {
        // Calculate waiting time as total time minus burst time and arrival time
        processes[i].waiting_time = total_time - processes[i].arrival_time;
        if (processes[i].waiting_time < 0) {
            processes[i].waiting_time = 0;  // Ensure waiting time is non-negative
        }
        total_time += processes[i].burst_time;  // Add burst time to total elapsed time
    }
}

// Function to calculate turnaround time
void calculateTurnAroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

// Function to sort processes based on priority and arrival time
void sortProcessesByPriority(Process processes[], int n) {
    Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // Sort primarily by priority, if priorities are the same, by arrival time
            if (processes[i].priority > processes[j].priority || 
               (processes[i].priority == processes[j].priority && processes[i].arrival_time > processes[j].arrival_time)) {
                // Swap the processes
                temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to display the results
void displayResults(Process processes[], int n) {
    printf("PN\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].process_id, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].priority, 
               processes[i].waiting_time, 
               processes[i].turnaround_time);
    }
}

void priorityScheduling(Process processes[], int n) {
    // Sort processes by priority and arrival time
    sortProcessesByPriority(processes, n);

    // Calculate waiting time and turnaround time
    calculateWaitingTime(processes, n);
    calculateTurnAroundTime(processes, n);

    // Display the results
    displayResults(processes, n);
}

int main() {
    int n;
    
    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Declare an array to store processes
    Process processes[n];

    // Input process details (arrival time, burst time, and priority)
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;  // Process IDs are 1, 2, 3, ...
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    }

    // Call the priority scheduling function
    priorityScheduling(processes, n);

    return 0;
}

