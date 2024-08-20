#include<stdio.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
int top=-1;
char t;
int PUSH(int item){
    if(top==MAX_STACK_SIZE-1){
        printf("Stack full\n");
    }
    stack[++top]=item;
}
int POP(){
    if(top==-1){
        printf("Stack underflows\n");
        return-1;
    }
    return stack[top--];
}
int eval(void){
    char t;
    char symbol;
    int op1, op2;
    int n=0;
    t=expr[n++];
    while(t!='\0'){
        if(t!='+'&&t!='-'&&t!='*'&&t!='/'&&t!='%'){
            PUSH(t-'0');
        }
        else{
            op2 = POP();
            op1 = POP();
            switch(t){
                case '+':
                    PUSH(op1+op2);
                    break;
                case '-':
                    PUSH(op1-op2);
                    break;
                case '*':
                    PUSH(op1*op2);
                    break;
                case '/':
                    PUSH(op1/op2);
                    break;
                case '%':
                    PUSH(op1%op2);
                    break;
            }
        }
        t = expr[n++];
    }
    return POP();
}
int main(){
    int ans;
    printf("Enter the postfix expression: ");
    gets(expr);
    ans = eval();
    printf("Answer is: %d", ans);
    return 0;
}
