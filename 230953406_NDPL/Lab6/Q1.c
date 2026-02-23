#include <stdio.h>

int main() {
    int data[50], received[50];
    int n, i, choice, count = 0;

    printf("============================================\n");
    printf("     PARITY CHECK - ERROR DETECTION\n");
    printf("============================================\n\n");

    // Input number of bits
    printf("Enter number of data bits: ");
    scanf("%d", &n);

    // Validate number of bits
    if (n <= 0 || n > 49) {
        printf("Error: Number of bits should be between 1 and 49\n");
        return 1;
    }

    // Input data bits with validation
    printf("Enter %d data bits (0 or 1 only):\n", n);
    for (i = 0; i < n; i++) {
        printf("Bit %d: ", i + 1);
        scanf("%d", &data[i]);
        
        // Validate each bit
        if (data[i] != 0 && data[i] != 1) {
            printf("Error: Only 0 or 1 allowed!\n");
            i--;  // Re-enter this bit
        }
    }

    // Choose parity type
    printf("\nChoose Parity Type:\n");
    printf("1. Even Parity\n");
    printf("2. Odd Parity\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2) {
        printf("Invalid choice!\n");
        return 1;
    }

    printf("\n============================================\n");
    printf("              SENDER SIDE\n");
    printf("============================================\n");

    // Count number of 1s in data
    count = 0;
    for (i = 0; i < n; i++) {
        if (data[i] == 1)
            count++;
    }

    printf("Original Data: ");
    for (i = 0; i < n; i++)
        printf("%d", data[i]);
    printf("\n");

    printf("Number of 1s in data: %d\n", count);

    // Calculate parity bit
    int parity;
    if (choice == 1) {
        // Even parity: total 1s (including parity) should be even
        parity = (count % 2 == 0) ? 0 : 1;
        printf("Parity Type: EVEN\n");
    } else {
        // Odd parity: total 1s (including parity) should be odd
        parity = (count % 2 == 0) ? 1 : 0;
        printf("Parity Type: ODD\n");
    }

    printf("Calculated Parity Bit: %d\n", parity);

    // Display transmitted data
    printf("\n>>> Transmitted Data: ");
    for (i = 0; i < n; i++)
        printf("%d", data[i]);
    printf("%d\n", parity);
    printf("    (Data bits + Parity bit)\n");

    printf("\n============================================\n");
    printf("             RECEIVER SIDE\n");
    printf("============================================\n");

    // Receiver input
    printf("Enter received data (%d bits including parity):\n", n + 1);
    for (i = 0; i <= n; i++) {
        printf("Bit %d: ", i + 1);
        scanf("%d", &received[i]);
        
        if (received[i] != 0 && received[i] != 1) {
            printf("Error: Only 0 or 1 allowed!\n");
            i--;
        }
    }

    // Display received data
    printf("\nReceived Data: ");
    for (i = 0; i <= n; i++)
        printf("%d", received[i]);
    printf("\n");

    // Count 1s in received data
    count = 0;
    for (i = 0; i <= n; i++) {
        if (received[i] == 1)
            count++;
    }

    printf("Number of 1s in received data: %d\n", count);

    printf("\n============================================\n");
    printf("           ERROR DETECTION RESULT\n");
    printf("============================================\n");

    // Check for errors
    if (choice == 1) {
        // Even parity: count should be even
        printf("Expected: Even number of 1s\n");
        printf("Actual: %s number of 1s\n", (count % 2 == 0) ? "Even" : "Odd");
        
        if (count % 2 == 0) {
            printf("\n✓ RESULT: No Error Detected\n");
        } else {
            printf("\n✗ RESULT: Error Detected!\n");
        }
    } else {
        // Odd parity: count should be odd
        printf("Expected: Odd number of 1s\n");
        printf("Actual: %s number of 1s\n", (count % 2 == 0) ? "Even" : "Odd");
        
        if (count % 2 != 0) {
            printf("\n✓ RESULT: No Error Detected\n");
        } else {
            printf("\n✗ RESULT: Error Detected!\n");
        }
    }

    printf("============================================\n");

    return 0;
}