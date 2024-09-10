#include <stdio.h>
struct sparse {
    int row;
    int col;
    int val;
};
void transpose(struct sparse a[], struct sparse b[]) {
    int n, i, j, currentb;
    n = a[0].val;
    b[0].row = a[0].row;
    b[0].col = a[0].col;
    b[0].val = n;
    if (n > 0) {
        currentb = 1;
        for (i = 0; i < a[0].col; i++) {
            for (j = 1; j <= n; j++) {
                if (a[j].col == i) {
                    b[currentb].row = a[j].col;
                    b[currentb].col = a[j].row;
                    b[currentb].val = a[j].val;
                    currentb++;
                }
            }
        }
    }
}
int main() {
    int row, col, val, A[100][100], i, j, k = 1;
    struct sparse a[1000];
    printf("Enter the number of rows: ");
    scanf("%d", &row);
    printf("Enter the number of columns: ");
    scanf("%d", &col);
    printf("Enter the elements:\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            scanf("%d", &A[i][j]);
            if (A[i][j] != 0) {
                a[k].row = i;
                a[k].col = j;
                a[k].val = A[i][j];
                k++;
            }
        }
    }
    a[0].row = row;
    a[0].col = col;
    a[0].val = k - 1;
    printf("The array of structure is:\n");
    for (i = 0; i < k; i++) {
        printf("row: %d, col: %d, value: %d\n", a[i].row, a[i].col, a[i].val);
    }

    struct sparse b[1000];
    transpose(a, b);
    printf("After transpose:\n");
    for (i = 0; i < k; i++) {
        printf("row: %d, col: %d, value: %d\n", b[i].row, b[i].col, b[i].val);
    }
    return 0;
}
