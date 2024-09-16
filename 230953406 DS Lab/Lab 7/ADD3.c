#include <stdio.h>
#include <stdlib.h>
struct node {
    int info;
    struct node *link;
} *start1, *start2;
void create_list(struct node **start, int data) {
    struct node *q, *tmp;
    tmp = (struct node *)malloc(sizeof(struct node));
    tmp->info = data;
    tmp->link = NULL;
    if (*start == NULL)
        *start = tmp;
    else {
        q = *start;
        while (q->link != NULL)
            q = q->link;
        q->link = tmp;
    }
}
void merge_lists(struct node *list1, struct node *list2, struct node **list3) {
    struct node *p1 = list1, *p2 = list2;
    while (p1 != NULL && p2 != NULL) {
        create_list(list3, p1->info);
        create_list(list3, p2->info);
        p1 = p1->link;
        p2 = p2->link;
    }
    while (p1 != NULL) {
        create_list(list3, p1->info);
        p1 = p1->link;
    }
    while (p2 != NULL) {
        create_list(list3, p2->info);
        p2 = p2->link;
    }
}
void display(struct node *start) {
    struct node *q = start;
    if (q == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("List is :\n");
    while (q != NULL) {
        printf("%d ", q->info);
        q = q->link;
    }
    printf("\n");
}
int main() {
    int n1, n2, data;
    start1 = NULL;
    start2 = NULL;
    struct node *list3 = NULL;
    printf("Enter number of elements for list1: ");
    scanf("%d", &n1);
    for (int i = 0; i < n1; i++) {
        printf("Enter element for list1: ");
        scanf("%d", &data);
        create_list(&start1, data);
    }
    printf("Enter number of elements for list2: ");
    scanf("%d", &n2);
    for (int i = 0; i < n2; i++) {
        printf("Enter element for list2: ");
        scanf("%d", &data);
        create_list(&start2, data);
    }
    merge_lists(start1, start2, &list3);
    display(list3);
    return 0;
}
