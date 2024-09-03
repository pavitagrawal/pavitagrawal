#include<stdio.h>
#define MAX 100
int stack[MAX];
 struct Stack s;
int PUSH(int *top, int item){
    if(*top==MAX-1){
        printf("Stack full\n");
    }
    stack[++*top]=item;
}
int POP(int *top){
    if(*top==-1){
        printf("Stack underflows\n");
        return-1;
    }
    return stack[(*top)--];
}
int main(){
    int num, top=-1, i, rem, base, t;
    printf("Enter the number: ");
    scanf("%d", &num);
    printf("Enter the base: ");
    scanf("%d", &base);
    t = num;
    while(t!=0){
        rem = t%base;
        stack[100]=PUSH(&top, rem);
        t=t/base;
    }
    int digit = pop(&s);
        if (digit >= 10) {
            printf("%c", 'A' + (digit - 10));
        } else {
            printf("%d", digit);
        }
    printf("Answer: ");
    while(top!=-1){
        t = POP(&top);
        printf("%d", t);
    }
}
