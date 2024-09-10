#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
    int *data;
    int top;
    int capacity;
} Stack;

void initStack(Stack *s, int capacity)
{
    s->data = (int *)malloc(capacity * sizeof(int));
    s->top = -1;
    s->capacity = capacity;
}

void push(Stack *s, int value)
{
    if (s->top < s->capacity - 1)
    {
        s->data[++(s->top)] = value;
    }
    else
    {
        printf("Stack overflow\n");
    }
}

int pop(Stack *s)
{
    if (s->top >= 0)
    {
        return s->data[(s->top)--];
    }
    printf("Stack underflow\n");
    return -1;
}

int main()
{
    Stack stacks[2];
    initStack(&stacks[0], MAX);
    initStack(&stacks[1], MAX);

    int value;
    printf("Enter values to push onto stack 0 (enter -1 to stop):\n");
    while (1) {
        scanf("%d", &value);
        if (value == -1) break;
        push(&stacks[0], value);
    }

    printf("Enter values to push onto stack 1 (enter -1 to stop):\n");
    while (1) {
        scanf("%d", &value);
        if (value == -1) break;
        push(&stacks[1], value);
    }

    printf("Pop from stack 0: %d\n", pop(&stacks[0]));
    printf("Pop from stack 1: %d\n", pop(&stacks[1]));

    free(stacks[0].data);
    free(stacks[1].data);

    return 0;
}
