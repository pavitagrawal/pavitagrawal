#include<stdio.h>
int main(){
    int n, arr[50], i, j, pos, small;
    printf("Enter the no. of elements of list: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    for(i=0;i<n;i++){
        pos = i;
        small = arr[i];
        for(j=i+1;j<n;j++){
            if(small>arr[j]){
                pos = j;
                small = arr[j];
            }
        }
        arr[pos]=arr[i];
        arr[i]=small;
    }
    printf("The new list is: ");
    for(i=0; i<n; i++){
        printf("%d ", arr[i]);
    }
}
