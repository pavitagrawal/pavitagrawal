#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

char stack[MAX_STACK_SIZE];
int top = -1;

int PUSH(char item) {
    if (top == MAX_STACK_SIZE - 1) {
        printf("Stack full\n");
        return -1;
    }
    stack[++top] = item;
}

char POP() {
    if (top == -1) {
        printf("Stack underflows\n");
        return -1;
    }
    return stack[top--];
}

int stack_pre(char c) {
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

void prefix_to_postfix(char* prefix) {
    char postfix[MAX_STACK_SIZE];
    int j = 0;
    int length = strlen(prefix);
    
    for (int i = length - 1; i >= 0; i--) {
        if (isalnum(prefix[i])) {
            postfix[j++] = prefix[i];
        } else {
            while (top != -1 && stack_pre(stack[top]) > stack_pre(prefix[i])) {
                postfix[j++] = POP();
            }
            PUSH(prefix[i]);
        }
    }
    
    while (top != -1) {
        postfix[j++] = POP();
    }
    
    postfix[j] = '\0';
    strrev(postfix);
    printf("Postfix expression: %s\n", postfix);
}

int main() {
    char prefix[MAX_STACK_SIZE];
    printf("Enter a prefix expression: ");
    scanf("%s", prefix);
    prefix_to_postfix(prefix);
    return 0;
}
