#include <stdio.h>
int binarySearch(int arr[], int low, int high, int key) {
    if (low > high) {
        return -1;
    }
    int mid = (low + high) / 2;
    if (arr[mid] == key) {
        return mid;
    } else if (arr[mid] < key) {
        return binarySearch(arr, mid + 1, high, key);
    } else {
        return binarySearch(arr, low, mid - 1, key);
    }
}
void selectionSort(int arr[], int n) {
    if (n <= 1) return;
    int i, j, pos, small;
    for (i = 0; i < n - 1; i++) {
        pos = i;
        small = arr[i];
        for (j = i + 1; j < n; j++) {
            if (small > arr[j]) {
                pos = j;
                small = arr[j];
            }
        }
        arr[pos] = arr[i];
        arr[i] = small;
    }
}
int multiply(int a, int b) {
    if (b == 0) return 0;
    return a + multiply(a, b - 1);
}
int main() {
    int key, n, arr[50], i;
    printf("Enter the no. of elements of list: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the element to search for: ");
    scanf("%d", &key);
    int result = binarySearch(arr, 0, n - 1, key);
    if (result != -1) {
        printf("Key found at %d place\n", result + 1);
    } else {
        printf("Key not found.\n");
    }
    printf("Enter the no. of elements of list for sorting: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    selectionSort(arr, n);
    printf("The new list is: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    int a, b;
    printf("Enter two numbers to multiply: ");
    scanf("%d %d", &a, &b);
    printf("The product is: %d\n", multiply(a, b));
    return 0;
}
