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
        temp = arr[i];
        j = i-1;
        while(j>=0 && arr[j]>temp){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
    printf("The new list is: ");
    for(i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
}
