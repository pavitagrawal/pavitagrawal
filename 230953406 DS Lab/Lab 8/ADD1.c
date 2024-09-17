#include <stdio.h>
#include <stdlib.h>

struct dnode {
    int info;
    struct dnode *prev;
    struct dnode *next;
};

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
}Node;

Node* createNode(int data);
void insert(Node* header, int data);
void display(Node* header);
void unionLists(Node* list1, Node* list2, Node* result);
void intersectionLists(Node* list1, Node* list2, Node* result);

int main(){
    Node* header1 = createNode(-1);
    Node* header2 = createNode(-1);
    Node* unionHeader = createNode(-1);
    Node* intersectionHeader = createNode(-1);
    int choice, data;
    printf("Enter elements for the first doubly linked list (enter -1 to stop):\n");
    while (1) {
        scanf("%d", &data);
        if (data == -1) break;
        insert(header1, data);
    }
    printf("Enter elements for the second doubly linked list (enter -1 to stop):\n");
    while (1) {
        scanf("%d", &data);
        if (data == -1) break;
        insert(header2, data);
    }
    unionLists(header1, header2, unionHeader);
    intersectionLists(header1, header2, intersectionHeader);
    printf("Union of the two lists:\n");
    display(unionHeader);
    printf("Intersection of the two lists:\n");
    display(intersectionHeader);
    return 0;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insert(Node* header, int data) {
    Node* newNode = createNode(data);
    Node* current = header;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
}

void display(Node* header) {
    if (header->next == NULL) {
        printf("Doubly linked list is empty.\n");
        return;
    }
    Node* current = header->next;
    printf("Doubly linked list elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void unionLists(Node* list1, Node* list2, Node* result) {
    Node* current = list1->next;
    while (current != NULL) {
        insert(result, current->data);
        current = current->next;
    }
    current = list2->next;
    while (current != NULL) {
        Node* temp = result->next;
        int found = 0;
        while (temp != NULL) {
            if (temp->data == current->data) {
                found = 1;
                break;
            }
            temp = temp->next;
        }
        if (!found) {
            insert(result, current->data);
        }
        current = current->next;
    }
}

void intersectionLists(Node* list1, Node* list2, Node* result) {
    Node* current = list1->next;
    while (current != NULL) {
        Node* temp = list2->next;
        while (temp != NULL) {
            if (temp->data == current->data) {
                insert(result, current->data);
                break;
            }
            temp = temp->next;
        }
        current = current->next;
    }
}
