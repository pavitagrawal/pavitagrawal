#include <stdio.h>
#include <string.h>
#define MAX_STACK_SIZE 100
char stack[MAX_STACK_SIZE];
int top = -1;
int PUSH(char item){
    if(top == MAX_STACK_SIZE - 1){
        printf("Stack full\n");
        return -1;
    }
    stack[++top] = item;
}
char POP(){
    if (top == -1){
        printf("Stack underflows\n");
        return -1;
    }
    return stack[top--];
}
int stack_pre(char c){
    switch (c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        case '(':
            return 0;
        default:
            return -1;
    }
}
void infix_to_postfix(char* expr){
    char postfix[MAX_STACK_SIZE];
    int j = 0;
    for (int i = 0; expr[i]; i++){
        if (isalnum(expr[i])) {
            postfix[j++] = expr[i];
        }
        else if (expr[i] == '(') {
            PUSH(expr[i]);
        }
        else if (expr[i] == ')') {
            while (top != -1 && stack[top] != '('){
                postfix[j++] = POP();
            }
            POP();
        }
        else {
            while (top != -1 && stack_pre(stack[top]) >= stack_pre(expr[i])){
                postfix[j++] = POP();
            }
            PUSH(expr[i]);
        }
    }
    while(top != -1){
        if (stack[top] != '('){
            postfix[j++] = POP();
        }
        else{
            POP();
        }
    }
    postfix[j] = '\0';
    printf("Postfix expression: %s\n", postfix);
}
int main(){
    char expr[MAX_STACK_SIZE];
    printf("Enter infix expression: ");
    scanf("%s", expr);
    infix_to_postfix(expr);
    return 0;
}
