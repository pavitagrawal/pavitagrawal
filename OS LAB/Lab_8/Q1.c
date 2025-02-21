#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to find the need of each process
void calculateNeed(int need[P][R], int maxm[P][R], int allot[P][R]) {
    // Calculating Need of each process
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            // Need of instance = maxm instance - allocated instance
            need[i][j] = maxm[i][j] - allot[i][j];
}

// Function to find if the system is in a safe state or not
bool isSafe(int processes[], int avail[], int maxm[][R], int allot[][R]) {
    int need[P][R];

    // Function to calculate need matrix
    calculateNeed(need, maxm, allot);

    // Mark all processes as unfinished
    bool finish[P] = {0};

    // To store safe sequence
    int safeSeq[P];

    // Make a copy of available resources
    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    // While all processes are not finished or system is not in safe state
    int count = 0;
    while (count < P) {
        // Find a process which is not finished and whose needs can be satisfied with current work[] resources
        bool found = false;
        for (int p = 0; p < P; p++) {
            // First check if a process is finished
            if (finish[p] == 0) {
                // Check if for all resources of current process need is less than work
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                // If all needs of process p were satisfied
                if (j == R) {
                    // Add the allocated resources of current process to the available/work resources
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    // Add this process to safe sequence
                    safeSeq[count++] = p;

                    // Mark this process as finished
                    finish[p] = 1;

                    found = true;
                }
            }
        }

        // If we could not find a next process in safe sequence
        if (found == false) {
            printf("System is not in safe state\n");
            return false;
        }
    }

    // If system is in safe state then safe sequence will be as below
    printf("System is in safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");

    return true;
}

// Driver code
int main() {
    int n, r;
    printf("Enter no. of processes: ");
    scanf("%d", &n);
    printf("Enter no. of resources: ");
    scanf("%d", &r);
    int processes[n];
    printf("Enter process IDs: ");
    for(int i=0;i<n;i++){
    	scanf("%d", &processes[i]);
    }
    printf("Enter available instance of resources: ");
    int avail[r];
    for(int i=0;i<r;i++){
    	scanf("%d", &avail[i]);
    }
    printf("Enter maximum resources that can be allocated to processes:\n");
    int maxm[n][r];
    for(int i=0;i<n;i++){
    	for(int j=0;j<r;j++){
    	    scanf("%d", &maxm[i][j]);
    	}
    }
    printf("Enter resources allocated to processes:\n");
    int allot[n][r];
    for(int i=0;i<n;i++){
    	for(int j=0;j<r;j++){
    	    scanf("%d", &allot[i][j]);
    	}
    }
    // Check if the system is in a safe state or not
    isSafe(processes, avail, maxm, allot);

    return 0;
}
