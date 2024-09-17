#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *prev, *next;
} *start1 = NULL, *end1 = NULL, *start2 = NULL, *end2 = NULL;

void displayList1() {
    struct node *q = start1;
    while(q != NULL) {
        printf("%d ", q->data);
        q = q->next;
    }
    printf("\n");
}

void insertAtRear1(int d) {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = d;
    temp->next = NULL;
    temp->prev = NULL;

    if(start1 == NULL) {
        start1 = end1 = temp;
        return;
    }

    temp->prev = end1;
    end1->next = temp;
    end1 = temp;
}

void displayList2() {
    struct node *q = start2;
    while(q != NULL) {
        printf("%d ", q->data);
        q = q->next;
    }
    printf("\n");
}

void insertAtRear2(int d) {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->data = d;
    temp->next = NULL;
    temp->prev = NULL;

    if(start2 == NULL) {
        start2 = end2 = temp;
        return;
    }

    temp->prev = end2;
    end2->next = temp;
    end2 = temp;
}

void addLongIntegers() {
    struct node *p1 = end1, *p2 = end2;
    int carry = 0;
    struct node *result = NULL, *last = NULL;

    while (p1 != NULL || p2 != NULL || carry) {
        int sum = carry;
        if (p1 != NULL) {
            sum += p1->data;
            p1 = p1->prev;
        }
        if (p2 != NULL) {
            sum += p2->data;
            p2 = p2->prev;
        }
        carry = sum / 10;
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        temp->data = sum % 10;
        temp->next = NULL;
        temp->prev = last;

        if (last != NULL) {
            last->next = temp;
        } else {
            result = temp;
        }
        last = temp;
    }

    start1 = result;
    end1 = last;
}

int main() {
    int choice, data;
    while(1) {
        printf("1. Add to List 1\n2. Add to List 2\n3. Display List 1\n4. Display List 2\n5. Add Long Integers\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter data for List 1: ");
                scanf("%d", &data);
                insertAtRear1(data);
                break;
            case 2:
                printf("Enter data for List 2: ");
                scanf("%d", &data);
                insertAtRear2(data);
                break;
            case 3:
                displayList1();
                break;
            case 4:
                displayList2();
                break;
            case 5:
                addLongIntegers();
                printf("Result of addition stored in List 1.\n");
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
