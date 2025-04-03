#include <stdio.h>
#include <stdlib.h>

void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", (frames[i] != -1) ? frames[i] : -1);
    printf("\n");
}

// FIFO Page Replacement Algorithm
void fifo(int pages[], int np, int nf) {
    int *frames = (int *)malloc(nf * sizeof(int));
    int faults = 0, front = 0;

    for (int i = 0; i < nf; i++)
        frames[i] = -1;

    printf("\nFIFO Page Replacement:\n");
    
    for (int i = 0; i < np; i++) {
        int found = 0;
        for (int j = 0; j < nf; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault
            frames[front] = pages[i];
            front = (front + 1) % nf;
            faults++;
        }

        printFrames(frames, nf);
    }

    printf("Total page faults: %d\n", faults);
    free(frames);
}

// Optimal Page Replacement Algorithm
void optimal(int pages[], int np, int nf) {
    int *frames = (int *)malloc(nf * sizeof(int));
    int faults = 0;

    for (int i = 0; i < nf; i++)
        frames[i] = -1;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < np; i++) {
        int found = 0, farthest = -1, replaceIndex = -1;

        for (int j = 0; j < nf; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault
            if (i < nf) {
                frames[i] = pages[i];
            } else {
                for (int j = 0; j < nf; j++) {
                    int nextUse = np;
                    for (int k = i + 1; k < np; k++) {
                        if (frames[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }
                frames[replaceIndex] = pages[i];
            }
            faults++;
        }

        printFrames(frames, nf);
    }

    printf("Total page faults: %d\n", faults);
    free(frames);
}

int main() {
    int np, nf;

    printf("Enter the number of pages and frames: ");
    scanf("%d %d", &np, &nf);

    int *pages = (int *)malloc(np * sizeof(int));
    printf("Enter the page sequence: ");
    for (int i = 0; i < np; i++)
        scanf("%d", &pages[i]);

    fifo(pages, np, nf);
    optimal(pages, np, nf);

    free(pages);
    return 0;
}
