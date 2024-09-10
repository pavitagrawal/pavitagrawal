#include <stdio.h>
void multiply(int a[10][10], int b[10][10], int r1, int c1, int r2, int c2) {
    int i, j, k, res[10][10] = {0};
    for (i = 0; i < r1; i++)
        for (j = 0; j < c2; j++)
            for (k = 0; k < c1; k++)
                res[i][j] += a[i][k] * b[k][j];
    printf("Product:\n");
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++)
            printf("%d ", res[i][j]);
        printf("\n");
    }
}
void add(int a[10][10], int b[10][10], int r, int c) {
    int i, j, res[10][10];
    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            res[i][j] = a[i][j] + b[i][j];
    printf("Sum:\n");
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++)
            printf("%d ", res[i][j]);
        printf("\n");
    }
}
int isMagicSquare(int mat[10][10], int n) {
    int sum = 0, diag1 = 0, diag2 = 0;
    for (int i = 0; i < n; i++) sum += mat[0][i];
    for (int i = 0; i < n; i++) {
        diag1 += mat[i][i];
        diag2 += mat[i][n - i - 1];
        int rowSum = 0, colSum = 0;
        for (int j = 0; j < n; j++) {
            rowSum += mat[i][j];
            colSum += mat[j][i];
        }
        if (rowSum != sum || colSum != sum) return 0;
    }
    return (diag1 == sum && diag2 == sum);
}
int main() {
    int a[10][10], b[10][10], r1, c1, r2, c2, n;
    printf("Enter rows and columns for matrix A: ");
    scanf("%d %d", &r1, &c1);
    printf("Enter matrix A:\n");
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c1; j++)
            scanf("%d", &a[i][j]);
    printf("Enter rows and columns for matrix B: ");
    scanf("%d %d", &r2, &c2);
    printf("Enter matrix B:\n");
    for (int i = 0; i < r2; i++)
        for (int j = 0; j < c2; j++)
            scanf("%d", &b[i][j]);
    if (c1 == r2) multiply(a, b, r1, c1, r2, c2);
    else printf("Matrix multiplication not possible.\n");
    if (r1 == r2 && c1 == c2) add(a, b, r1, c1);
    else printf("Matrix addition not possible.\n");
    printf("Enter size of square matrix: ");
    scanf("%d", &n);
    int mat[10][10];
    printf("Enter square matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &mat[i][j]);
    if (isMagicSquare(mat, n)) printf("It is a magic square.\n");
    else printf("It is not a magic square.\n");
    return 0;
}