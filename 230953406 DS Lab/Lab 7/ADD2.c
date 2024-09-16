#include <stdio.h>
#include <stdlib.h>
struct node {
    int info;
    struct node *link;
} *startX, *startY, *startZ;
void create_list(struct node **start, int data) {
    struct node *q, *tmp;
    tmp = (struct node *)malloc(sizeof(struct node));
    tmp->info = data;
    tmp->link = NULL;
    if (*start == NULL) {
        *start = tmp;
    } else {
        q = *start;
        while (q->link != NULL) {
            q = q->link;
        }
        q->link = tmp;
    }
}
void merge_lists() {
    struct node *ptrX = startX, *ptrY = startY, *ptrZ = NULL, *lastZ = NULL;
    while (ptrX != NULL && ptrY != NULL) {
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        if (ptrX->info <= ptrY->info) {
            newNode->info = ptrX->info;
            ptrX = ptrX->link;
        } else {
            newNode->info = ptrY->info;
            ptrY = ptrY->link;
        }
        newNode->link = NULL;
        if (startZ == NULL) {
            startZ = newNode;
            lastZ = newNode;
        } else {
            lastZ->link = newNode;
            lastZ = newNode;
        }
    }
    while (ptrX != NULL) {
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        newNode->info = ptrX->info;
        newNode->link = NULL;
        lastZ->link = newNode;
        lastZ = newNode;
        ptrX = ptrX->link;
    }
    while (ptrY != NULL) {
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        newNode->info = ptrY->info;
        newNode->link = NULL;
        lastZ->link = newNode;
        lastZ = newNode;
        ptrY = ptrY->link;
    }
    startX = NULL;
    startY = NULL;
}
void display(struct node *start) {
    struct node *q = start;
    while (q != NULL) {
        printf("%d ", q->info);
        q = q->link;
    }
    printf("\n");
}
int main() {
    int n, m;
    startX = NULL;
    startY = NULL;
    startZ = NULL;
    printf("Enter number of elements for list X: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter element for list X: ");
        scanf("%d", &m);
        create_list(&startX, m);
    }
    printf("Enter number of elements for list Y: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter element for list Y: ");
        scanf("%d", &m);
        create_list(&startY, m);
    }
    merge_lists();
    printf("Merged list Z: ");
    display(startZ);
    return 0;
}
