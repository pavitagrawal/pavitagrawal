#include <stdio.h>
#include <math.h>
#include <string.h>

// Function to check if a number is power of 2
int isPowerOfTwo(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Function to calculate number of parity bits needed
int calculateParityBits(int m) {
    int r = 0;
    while ((1 << r) < (m + r + 1)) {
        r++;
    }
    return r;
}

// Function to display hamming code with position details
void displayHammingCode(int hamming[], int totalBits) {
    printf("\nPosition:  ");
    for (int i = 1; i <= totalBits; i++) {
        printf("%2d ", i);
    }
    printf("\nBit Type:  ");
    for (int i = 1; i <= totalBits; i++) {
        if (isPowerOfTwo(i)) {
            printf(" P ");  // Parity bit
        } else {
            printf(" D ");  // Data bit
        }
    }
    printf("\nBit Value: ");
    for (int i = 1; i <= totalBits; i++) {
        printf("%2d ", hamming[i]);
    }
    printf("\n");
}

int main() {
    int data[50], hamming[100], received[100];
    int n, p, totalBits;
    int errorPos = 0;
    
    printf("============================================\n");
    printf("      HAMMING CODE - ERROR DETECTION\n");
    printf("           AND CORRECTION\n");
    printf("============================================\n\n");
    
    // Input number of data bits
    printf("Enter number of data bits: ");
    scanf("%d", &n);
    
    if (n <= 0 || n > 50) {
        printf("Invalid number of bits! (1-50 allowed)\n");
        return 1;
    }
    
    // Input data bits with validation
    printf("Enter %d data bits (0 or 1 only):\n", n);
    for (int i = 0; i < n; i++) {
        printf("Bit %d: ", i + 1);
        scanf("%d", &data[i]);
        
        if (data[i] != 0 && data[i] != 1) {
            printf("Invalid input! Only 0 or 1 allowed.\n");
            i--;  // Re-enter this bit
        }
    }
    
    // Calculate number of parity bits required
    p = calculateParityBits(n);
    totalBits = n + p;
    
    printf("\n--- HAMMING CODE GENERATION ---\n");
    printf("Data bits (m): %d\n", n);
    printf("Parity bits (r): %d\n", p);
    printf("Total bits (m+r): %d\n", totalBits);
    printf("\nParity bit positions: ");
    for (int i = 0; i < p; i++) {
        printf("%d ", (1 << i));
    }
    printf("\n");
    
    // Place data bits in hamming code (skip parity positions)
    int j = 0;
    for (int i = 1; i <= totalBits; i++) {
        if (isPowerOfTwo(i)) {
            hamming[i] = 0;  // Initialize parity bits to 0
        } else {
            hamming[i] = data[j++];
        }
    }
    
    printf("\nHamming code before parity calculation:\n");
    displayHammingCode(hamming, totalBits);
    
    // Calculate parity bit values
    for (int i = 0; i < p; i++) {
        int parityPos = (1 << i);  // Position of parity bit (1, 2, 4, 8, ...)
        int parity = 0;
        
        printf("\nCalculating P%d (position %d):\n", i + 1, parityPos);
        printf("Checking positions: ");
        
        for (j = 1; j <= totalBits; j++) {
            // Check if this position should be included in parity calculation
            if (j & parityPos) {
                printf("%d ", j);
                parity ^= hamming[j];
            }
        }
        printf("\nParity value: %d\n", parity);
        
        hamming[parityPos] = parity;
    }
    
    printf("\n============================================\n");
    printf("        TRANSMITTED HAMMING CODE\n");
    printf("============================================\n");
    displayHammingCode(hamming, totalBits);
    
    // Print hamming code in simple format
    printf("\nTransmitted Code: ");
    for (int i = 1; i <= totalBits; i++) {
        printf("%d", hamming[i]);
    }
    printf("\n");
    
    // Receiver side
    printf("\n============================================\n");
    printf("              RECEIVER SIDE\n");
    printf("============================================\n\n");
    
    printf("Enter received hamming code (%d bits):\n", totalBits);
    for (int i = 1; i <= totalBits; i++) {
        printf("Position %d: ", i);
        scanf("%d", &received[i]);
        
        if (received[i] != 0 && received[i] != 1) {
            printf("Invalid input! Only 0 or 1 allowed.\n");
            i--;
        }
    }
    
    printf("\nReceived Code: ");
    for (int i = 1; i <= totalBits; i++) {
        printf("%d", received[i]);
    }
    printf("\n");
    
    // Error detection and correction
    printf("\n--- ERROR DETECTION ---\n");
    
    errorPos = 0;
    for (int i = 0; i < p; i++) {
        int parityPos = (1 << i);
        int parity = 0;
        
        printf("\nChecking P%d (position %d):\n", i + 1, parityPos);
        printf("Positions checked: ");
        
        for (j = 1; j <= totalBits; j++) {
            if (j & parityPos) {
                printf("%d ", j);
                parity ^= received[j];
            }
        }
        
        printf("\nParity result: %d ", parity);
        
        if (parity != 0) {
            printf("(ERROR in this group)");
            errorPos += parityPos;
        } else {
            printf("(OK)");
        }
        printf("\n");
    }
    
    printf("\n============================================\n");
    printf("               RESULT\n");
    printf("============================================\n");
    
    if (errorPos == 0) {
        printf("\n✓ No Error Detected\n");
        printf("Data received correctly!\n");
        
        // Extract data bits
        printf("\nReceived Data Bits: ");
        for (int i = 1; i <= totalBits; i++) {
            if (!isPowerOfTwo(i)) {
                printf("%d", received[i]);
            }
        }
        printf("\n");
        
    } else {
        printf("\n✗ Error Detected at Position: %d\n", errorPos);
        printf("Bit value before correction: %d\n", received[errorPos]);
        
        // Correct the error
        received[errorPos] ^= 1;
        
        printf("Bit value after correction: %d\n", received[errorPos]);
        
        printf("\n--- CORRECTED HAMMING CODE ---\n");
        displayHammingCode(received, totalBits);
        
        printf("\nCorrected Code: ");
        for (int i = 1; i <= totalBits; i++) {
            printf("%d", received[i]);
        }
        printf("\n");
        
        // Extract corrected data bits
        printf("\nCorrected Data Bits: ");
        for (int i = 1; i <= totalBits; i++) {
            if (!isPowerOfTwo(i)) {
                printf("%d", received[i]);
            }
        }
        printf("\n");
    }
    
    printf("\n============================================\n");
    
    return 0;
}