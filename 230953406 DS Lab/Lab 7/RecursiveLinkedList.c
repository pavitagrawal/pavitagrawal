#include <stdio.h>
#include <stdlib.h>
struct node {
    int info;
    struct node *link;
} *start;
void create_list(int data);
void traverse_list(struct node *node);
int main(){
    int n, m;
    start = NULL;
    printf("How many nodes do you want to create: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        printf("Enter the element: ");
        scanf("%d", &m);
        create_list(m);
    }
    printf("Traversing the linked list:\n");
    traverse_list(start);
    return 0;
}
void create_list(int data){
    struct node *tmp = (struct node *)malloc(sizeof(struct node));
    tmp->info = data;
    tmp->link = NULL;
    if (start == NULL){
        start = tmp;
    } else {
        struct node *q = start;
        while (q->link != NULL){
            q = q->link;
        }
        q->link = tmp;
    }
}
void traverse_list(struct node *node){
    if (node == NULL){
        return;
    }
    printf("%d ", node->info);
    traverse_list(node->link);
}
