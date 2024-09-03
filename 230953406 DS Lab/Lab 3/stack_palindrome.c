#include<stdio.h>
#include<string.h>
#define MAX 100
char stack[MAX];
int POP(int *top){
    if(*top==-1){
        printf("Stack underflows\n");
        return-1;
    }
    return stack[(*top)--];
}
int main(){
    int top, i, check, t, length;
    printf("Enter the string: ");
    gets(stack);
    length=strlen(stack);
    top = length-1;
    for(i=0;i<length;i++){
        t = POP(&top);
        if(t==stack[i]){
            check = 1;
        }
        else{
            check=0;
            break;
        }
    }
    if(check==1){
        printf("It is a palindrome");
    }
    else{
        printf("It is not a palindrome");
    }
}
