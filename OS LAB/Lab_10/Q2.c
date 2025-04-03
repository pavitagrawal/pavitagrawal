#include <stdio.h>
#include <stdlib.h>

// Function to find the least recently used page
int findLRU(int *timestamps, int n) {
    int min = 0;
    for (int i = 1; i < n; i++) {
        if (timestamps[i] < timestamps[min])
            min = i;
    }
    return min;
}

// Function to implement LRU page replacement
void lruPageReplacement(int *pages, int numPages, int numFrames) {
    int *frames = (int *)malloc(numFrames * sizeof(int));
    int *timestamps = (int *)malloc(numFrames * sizeof(int));
    int pageFaults = 0, time = 0;

    // Initialize frames to -1 (empty)
    for (int i = 0; i < numFrames; i++)
        frames[i] = -1;

    printf("\nLRU Page Replacement Simulation:\n");

    for (int i = 0; i < numPages; i++) {
        int page = pages[i], found = -1;

        // Check if page is already in frame
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == page) {
                found = j;
                break;
            }
        }

        if (found == -1) { // Page fault
            int replaceIdx;
            if (i < numFrames) {
                replaceIdx = i;  // Fill empty frames first
            } else {
                replaceIdx = findLRU(timestamps, numFrames); // Find LRU page index
            }

            frames[replaceIdx] = page;
            pageFaults++;
        } else {
            replaceIdx = found;
        }

        timestamps[replaceIdx] = time++; // Update timestamp

        // Print current frame status
        printf("Step %d: ", i + 1);
        for (int j = 0; j < numFrames; j++)
            printf("%d ", (frames[j] != -1) ? frames[j] : -1);
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    // Free allocated memory
    free(frames);
    free(timestamps);
}

int main() {
    int numPages, numFrames;

    // User input for number of pages and frames
    printf("Enter the number of pages and frames: ");
    scanf("%d %d", &numPages, &numFrames);

    int *pages = (int *)malloc(numPages * sizeof(int));

    // User input for page sequence
    printf("Enter the page sequence: ");
    for (int i = 0; i < numPages; i++)
        scanf("%d", &pages[i]);

    // Run LRU page replacement algorithm
    lruPageReplacement(pages, numPages, numFrames);

    // Free allocated memory
    free(pages);

    return 0;
}
