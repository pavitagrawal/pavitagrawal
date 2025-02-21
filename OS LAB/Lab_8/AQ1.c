#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 5

// Function to find the need of each process
void calculateNeed(int need[MAX_PROCESSES][MAX_RESOURCES], int maxm[MAX_PROCESSES][MAX_RESOURCES], int allot[MAX_PROCESSES][MAX_RESOURCES], int processCount) {
    for (int i = 0; i < processCount; i++)
        for (int j = 0; j < MAX_RESOURCES; j++)
            need[i][j] = maxm[i][j] - allot[i][j];
}

// Function to check if the system is in a safe state
bool isSafe(int processes[], int avail[], int maxm[][MAX_RESOURCES], int allot[][MAX_RESOURCES], int processCount) {
    int need[MAX_PROCESSES][MAX_RESOURCES];
    calculateNeed(need, maxm, allot, processCount);

    bool finish[MAX_PROCESSES] = {0};
    int work[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; i++)
        work[i] = avail[i];

    int count = 0;
    while (count < processCount) {
        bool found = false;
        for (int p = 0; p < processCount; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == MAX_RESOURCES) {
                    for (int k = 0; k < MAX_RESOURCES; k++)
                        work[k] += allot[p][k];
                    finish[p] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            printf("Deadlock detected!\n");
            return false;
        }
    }
    printf("No deadlock detected.\n");
    return true;
}

// Driver code
int main() {
    int processes[MAX_PROCESSES];
    int processCount, resourceCount;

    printf("Enter the number of processes (max %d): ", MAX_PROCESSES);
    scanf("%d", &processCount);

    printf("Enter the number of resources (max %d): ", MAX_RESOURCES);
    scanf("%d", &resourceCount);

    int avail[MAX_RESOURCES];
    printf("Enter the available instances of resources:\n");
    for (int i = 0; i < resourceCount; i++) {
        printf("Resource %d: ", i + 1);
        scanf("%d", &avail[i]);
    }

    int maxm[MAX_PROCESSES][MAX_RESOURCES];
    printf("Enter the maximum resources that can be allocated to each process:\n");
    for (int i = 0; i < processCount; i++) {
        processes[i] = i; // Assign process IDs
        printf("Process P%d:\n", i);
        for (int j = 0; j < resourceCount; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &maxm[i][j]);
        }
    }

    int allot[MAX_PROCESSES][MAX_RESOURCES];
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < processCount; i++) {
        printf("Process P%d:\n", i);
        for (int j = 0; j < resourceCount; j++) {
            printf("Resource %d: ", j + 1);
            scanf("%d", &allot[i][j]);
        }
    }

    // Check for deadlock
    isSafe(processes, avail, maxm, allot, processCount);

    return 0;
}
