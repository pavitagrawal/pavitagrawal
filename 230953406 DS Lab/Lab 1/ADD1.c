#include <stdio.h>
#define MAX 50
int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int rows, cols, i, j;
    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &rows, &cols);
    printf("Enter elements of matrix A:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    printf("Enter elements of matrix B:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &B[i][j]);
        }
    }
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            C[i][j] = (A[i][j] > B[i][j]) ? A[i][j] : B[i][j];
        }
    }
    printf("Matrix C (max of A and B):\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}
