#include<stdio.h>
int main(){
    int i = 0, len = 0;
    char str[50];
    printf("Enter the string to check length for: ");
    scanf("%s", str);
    while(str[i]!='\0'){
        len++;
        i++;
    }
    printf("The length of string is: %d", len);
}
