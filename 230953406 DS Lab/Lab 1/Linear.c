#include<stdio.h>
int main(){
    int key, n, arr[50], i;
    printf("Enter the no. of elements of list: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for(i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Enter the element to search for: ");
    scanf("%d", &key);
    for(i=0; i<n; i++){
        if(arr[i]==key){
            printf("The element is at %d place", i+1);
        }
    }
}
