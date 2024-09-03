#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
int stack[MAX_STACK_SIZE];
int top = -1;
void PUSH(int item) {
    if (top == MAX_STACK_SIZE - 1) {
        printf("Stack full\n");
        return;
    }
    stack[++top] = item;
}
int POP() {
    if (top == -1) {
        printf("Stack underflows\n");
        return -1;
    }
    return stack[top--];
}
int evaluate_prefix(char* expr) {
    int i;
    for (i = strlen(expr) - 1; i >= 0; i--) {
        if (isalnum(expr[i])) {
            PUSH(expr[i] - '0'); // Convert char to int
        } else {
            int op1 = POP();
            int op2 = POP();
            switch (expr[i]) {
                case '+':
                    PUSH(op1 + op2);
                    break;
                case '-':
                    PUSH(op1 - op2);
                    break;
                case '*':
                    PUSH(op1 * op2);
                    break;
                case '/':
                    PUSH(op1 / op2);
                    break;
                case '^':
                    PUSH(pow(op1, op2));
                    break;
            }
        }
    }
    return POP();
}
int main() {
    char expr[MAX_STACK_SIZE];
    printf("Enter the prefix expression: ");
    scanf("%s", expr);
    int result = evaluate_prefix(expr);
    printf("Answer is: %d\n", result);
    return 0;
}
