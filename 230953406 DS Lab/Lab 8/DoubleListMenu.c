#include <stdio.h>
#include <stdlib.h>

struct dnode {
    struct dnode *llink;
    int data;
    struct dnode *rlink;
};

struct dnode* insert_end(struct dnode *head) {
    struct dnode *temp = (struct dnode *)malloc(sizeof(struct dnode));
    scanf("%d", &temp->data);
    temp->llink = temp->rlink = NULL;
    if (head == NULL) {
        head = temp;
        return head;
    }
    struct dnode *cur = head;
    while (cur->rlink != NULL) {
        cur = cur->rlink;
    }
    cur->rlink = temp;
    temp->llink = cur;
    return head;
}

struct dnode* delete_end(struct dnode *head) {
    struct dnode *temp;
    if (head == NULL) {
        printf("DLL is empty\n");
        return head;
    }
    struct dnode *cur = head;
    while (cur->rlink != NULL) {
        cur = cur->rlink;
    }
    if (cur->llink != NULL) {
        cur->llink->rlink = NULL;
    } else {
        head = NULL;
    }
    free(cur);
    return head;
}

struct dnode* insert_at_position(struct dnode *head, int pos) {
    struct dnode *temp = (struct dnode *)malloc(sizeof(struct dnode));
    scanf("%d", &temp->data);
    temp->llink = temp->rlink = NULL;
    if (pos == 0) {
        temp->rlink = head;
        if (head != NULL) {
            head->llink = temp;
        }
        return temp;
    }
    struct dnode *cur = head;
    for (int i = 0; i < pos - 1 && cur != NULL; i++) {
        cur = cur->rlink;
    }
    if (cur == NULL) {
        printf("Position out of bounds\n");
        free(temp);
        return head;
    }
    temp->rlink = cur->rlink;
    if (cur->rlink != NULL) {
        cur->rlink->llink = temp;
    }
    cur->rlink = temp;
    temp->llink = cur;
    return head;
}

struct dnode* delete_at_position(struct dnode *head, int pos) {
    if (head == NULL) {
        printf("DLL is empty\n");
        return head;
    }
    struct dnode *cur = head;
    for (int i = 0; i < pos && cur != NULL; i++) {
        cur = cur->rlink;
    }
    if (cur == NULL) {
        printf("Position out of bounds\n");
        return head;
    }
    if (cur->llink != NULL) {
        cur->llink->rlink = cur->rlink;
    } else {
        head = cur->rlink;
    }
    if (cur->rlink != NULL) {
        cur->rlink->llink = cur->llink;
    }
    free(cur);
    return head;
}

struct dnode* insert_after(struct dnode *head, int after) {
    struct dnode *cur = head;
    while (cur != NULL && cur->data != after) {
        cur = cur->rlink;
    }
    if (cur == NULL) {
        printf("Element not found\n");
        return head;
    }
    struct dnode *temp = (struct dnode *)malloc(sizeof(struct dnode));
    scanf("%d", &temp->data);
    temp->llink = cur;
    temp->rlink = cur->rlink;
    if (cur->rlink != NULL) {
        cur->rlink->llink = temp;
    }
    cur->rlink = temp;
    return head;
}

struct dnode* insert_before(struct dnode *head, int before) {
    struct dnode *cur = head;
    while (cur != NULL && cur->data != before) {
        cur = cur->rlink;
    }
    if (cur == NULL) {
        printf("Element not found\n");
        return head;
    }
    struct dnode *temp = (struct dnode *)malloc(sizeof(struct dnode));
    scanf("%d", &temp->data);
    temp->rlink = cur;
    temp->llink = cur->llink;
    if (cur->llink != NULL) {
        cur->llink->rlink = temp;
    } else {
        head = temp;
    }
    cur->llink = temp;
    return head;
}

void print(struct dnode *head) {
    struct dnode *h = head;
    while (h != NULL) {
        printf("%d ", h->data);
        h = h->rlink;
    }
    printf("\n");
}

struct dnode* reverse(struct dnode *head) {
    struct dnode *temp = NULL;
    struct dnode *current = head;
    while (current != NULL) {
        temp = current->llink;
        current->llink = current->rlink;
        current->rlink = temp;
        current = current->llink;
    }
    if (temp != NULL) {
        head = temp->llink;
    }
    return head;
}

int main() {
    struct dnode *head = NULL;
    int c, pos, ele;
    for (;;) {
        printf("1. Insert at end\n2. Delete from end\n3. Insert at position\n4. Delete from position\n5. Insert after\n6. Insert before\n7. Print\n8. Reverse\n");
        scanf("%d", &c);
        switch (c) {
            case 1: head = insert_end(head); break;
            case 2: head = delete_end(head); break;
            case 3: printf("Enter position: "); scanf("%d", &pos); head = insert_at_position(head, pos); break;
            case 4: printf("Enter position: "); scanf("%d", &pos); head = delete_at_position(head, pos); break;
            case 5: printf("Enter element after which to insert: "); scanf("%d", &ele); head = insert_after(head, ele); break;
            case 6: printf("Enter element before which to insert: "); scanf("%d", &ele); head = insert_before(head, ele); break;
            case 7: print(head); break;
            case 8: head = reverse(head); break;
            default: exit(0);
        }
    }
    return 0;
}
