#include<stdio.h>
int main(){
    int n, arr[50], i, j, temp;
    printf("Enter the no. of elements of list: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(arr[i]>arr[j]){
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
    printf("The new list is: ");
    for(i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
}
