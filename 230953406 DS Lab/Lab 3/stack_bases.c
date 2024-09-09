#include <stdio.h>
#define MAX 100

int stack[MAX];

int PUSH(int *top, int item) {
    if (*top == MAX - 1) {
        printf("Stack full\n");
        return -1;
    }
    stack[++(*top)] = item;
    return 0;
}

int POP(int *top) {
    if (*top == -1) {
        printf("Stack underflows\n");
        return -1;
    }
    return stack[(*top)--];
}

int main() {
    int num, top = -1, rem, base, t;
    printf("Enter the number: ");
    scanf("%d", &num);
    printf("Enter the base: ");
    scanf("%d", &base);
    t = num;

    while (t != 0) {
        rem = t % base;
        PUSH(&top, rem);
        t = t / base;
    }

    printf("Answer: ");
    while (top != -1) {
        int digit = POP(&top);
        if (digit >= 10) {
            printf("%c", 'A' + (digit - 10));
        } else {
            printf("%d", digit);
        }
    }
    printf("\n");
    return 0;
}
