#include <stdio.h>
#include <string.h>
#define MAX_STACK_SIZE 100
char stack[MAX_STACK_SIZE][MAX_STACK_SIZE];
int top = -1;
void PUSH(char* item){
    if (top == MAX_STACK_SIZE - 1){
        printf("Stack full\n");
        return -1;
    }
    strcpy(stack[++top], item);
}
char* POP(){
    if (top == -1) {
        printf("Stack underflows\n");
        return -1;
    }
    return stack[top--];
}
int is_operator(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
void postfix_to_infix(char* expr){
    char temp[MAX_STACK_SIZE];
    for (int i = 0; expr[i]; i++) {
        if (isalnum(expr[i])) {
            char operand[2] = {expr[i], '\0'};
            PUSH(operand);
        } else if (is_operator(expr[i])) {
            char* op1 = POP();
            char* op2 = POP();
            printf(temp, "(%s %c %s)", op2, expr[i], op1);
            PUSH(temp);
        }
    }
    printf("Infix expression: %s\n", POP());
}
int main(){
    char expr[MAX_STACK_SIZE];
    printf("Enter postfix expression: ");
    scanf("%s", expr);
    postfix_to_infix(expr);
    return 0;
}
