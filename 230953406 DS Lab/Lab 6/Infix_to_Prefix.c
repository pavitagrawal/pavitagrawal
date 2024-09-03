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
    return 0;
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
void Reverse(char str[], int size){
    int start = 0;
    int end = size-1;
    while(start<end){
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
void infix_to_prefix(char* expr){
    char prefix[MAX_STACK_SIZE];
    int j = 0, i;
    for (i = 0; expr[i]; i++){
        if (isalnum(expr[i])) {
            prefix[j++] = expr[i];
        }
        else if (expr[i] == '(') {
            PUSH(expr[i]);
        }
        else if (expr[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                prefix[j++] = POP();
            }
            POP();
        }
        else {
            while (top != -1 && stack_pre(stack[top]) >= stack_pre(expr[i])){
                prefix[j++] = POP();
            }
            PUSH(expr[i]);
        }
    }
    while (top != -1){
        prefix[j++] = POP();
    }
    prefix[j] = '\0';
    Reverse(prefix, j);
    char final_prefix[MAX_STACK_SIZE];
    int k = 0;
    for (i = 0; i < j; i++) {
        if (prefix[i] != '(' && prefix[i] != ')') {
            final_prefix[k++] = prefix[i];
        }
    }
    final_prefix[k] = '\0';
    printf("Prefix expression: %s\n", final_prefix);
}
int main(){
    char expr[MAX_STACK_SIZE];
    printf("Enter infix expression: ");
    scanf("%s", expr);
    int len = 0, i = 0;
    while(expr[i]!='\0'){
        len++;
        i++;
    }
    Reverse(expr, len);
    for(i=0; i<len; i++){
        if(expr[i]=='('){
            expr[i]=')';
        }
        else if(expr[i]==')'){
            expr[i]='(';
        }
    }
    infix_to_prefix(expr);
    return 0;
}
