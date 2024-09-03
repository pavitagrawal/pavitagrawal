#include<stdio.h>
int main(){
    int key, n, arr[50], i, low, high, mid;
    printf("Enter the no. of elements of list: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Enter the element to search for: ");
    scanf("%d", &key);
    low = 0;
    high = n-1;
    mid = (low + high)/2;
    while(low!=high){
        if(key>arr[mid]){
            low = mid;
            mid = (low + high)/2;
        }
        else if(key<arr[mid]){
            high = mid;
            mid = (low + high)/2;
        }
        else if(key == arr[mid]){
            printf("Key found at %d place", mid+1);
            break;
        }
    }
}
