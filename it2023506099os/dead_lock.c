#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void calculateNeed(int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int isSafeState(int processes, int resources) {
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0}; 
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    while (count < processes) {
        int found = 0;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                int canAllocate = 1;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = 0;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            return 0;  // No safe sequence found
        }
    }

    printf("\nSystem is in a SAFE state.\nSafe Sequence: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    int processes, resources;
    
    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter number of resources: ");
    scanf("%d", &resources);

    printf("\nEnter the available resources: ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("\nEnter the maximum resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter the allocated resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    calculateNeed(processes, resources);

    if (isSafeState(processes, resources)) {
        printf("Deadlock is prevented.\n");
    } else {
        printf("System is in an UNSAFE state! Deadlock may occur.\n");
    }

    return 0;
}

