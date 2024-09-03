#include<stdio.h>
int main(){
    int n, arr[50], i, j, temp;
    printf("Enter the no. of elements of list: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    for(i=0;i<n;i++){
        for(j=0;j<n-1-i;j++){
            if(arr[j]>arr[j+1]){
                temp = arr[j+1];
                arr[j+1]=arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("The new list is: ");
    for(i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
}
