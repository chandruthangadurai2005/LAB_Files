#include<stdio.h>
#define max 20 // maximum size for array

int main() {
    int i, burstTime[max], remainTime[max], remainProcess, arrivalTime[max], totalExecutionTime = 0, timeQuantum, flag = 0, n;
    float totalWaitingTime = 0, totalTurnAroundTime = 0;
    printf("Enter the Number of Process (max 20): ");
    scanf("%d", &n); // n is the number of Process
    remainProcess = n;

    // Declare additional arrays for completion time and turnaround time
    int completionTime[max], turnaroundTime[max], waitingTime[max];

    printf("Enter Arrival Time\n");
    for (i = 0; i < n; i++) {
        printf("For P[%d]: ", i + 1);
        scanf("%d", &arrivalTime[i]);
    }

    printf("\nEnter Burst Time\n");
    for (i = 0; i < n; i++) {
        printf("For P[%d]: ", i + 1);
        scanf("%d", &burstTime[i]);
        remainTime[i] = burstTime[i]; // initially assume remaining time for any process is equal to its burst time!
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &timeQuantum);

    // Round Robin Scheduling
    for (i = 0; remainProcess != 0;) {
        if (remainTime[i] <= timeQuantum && remainTime[i] > 0) {
            totalExecutionTime += remainTime[i];
            remainTime[i] = 0;
            flag = 1;
        }
        else if (remainTime[i] > 0) {
            remainTime[i] -= timeQuantum;
            totalExecutionTime += timeQuantum;
        }

        // Process completed
        if (flag == 1 && remainTime[i] == 0) {
            completionTime[i] = totalExecutionTime;
            turnaroundTime[i] = completionTime[i] - arrivalTime[i]; // Turnaround Time = Completion Time - Arrival Time
            waitingTime[i] = turnaroundTime[i] - burstTime[i]; // Waiting Time = Turnaround Time - Burst Time

            totalWaitingTime += waitingTime[i];
            totalTurnAroundTime += turnaroundTime[i];

            flag = 0;
            remainProcess--;
        }

        if (i == n - 1)
            i = 0;
        else if (arrivalTime[i + 1] <= totalExecutionTime) {
            i++;
        }
        else
            i = 0;
    }

    // Calculate and display average waiting time and turnaround time
    totalWaitingTime = totalWaitingTime / n;
    totalTurnAroundTime = totalTurnAroundTime / n;

    // Print the results in a tabular format
    printf("\nP#\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                i + 1, arrivalTime[i], burstTime[i], completionTime[i], turnaroundTime[i], waitingTime[i]);
    }

    // Display averages
    printf("\nThe Average Waiting Time: %.2f\n", totalWaitingTime);
    printf("The Average Turnaround Time: %.2f\n", totalTurnAroundTime);

    return 0;
}

