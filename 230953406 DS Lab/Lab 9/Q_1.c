#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct DoublyLinkedCircularList {
    Node* head;
} DoublyLinkedCircularList;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void insert(DoublyLinkedCircularList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        list->head->next = list->head;
        list->head->prev = list->head;
    } else {
        Node* tail = list->head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = list->head;
        list->head->prev = newNode;
    }
}

void deleteElement(DoublyLinkedCircularList* list, int data) {
    if (list->head == NULL) {
        printf("List is empty!\n");
        return;
    }

    Node* current = list->head;
    do {
        if (current->data == data) {
            if (current->next == list->head) {
                free(current);
                list->head = NULL;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                if (current == list->head) {
                    list->head = current->next;
                }
                free(current);
            }
            printf("Deleted %d from the list.\n", data);
            return;
        }
        current = current->next;
    } while (current != list->head);

    printf("Element %d not found in the list.\n", data);
}

void display(DoublyLinkedCircularList* list) {
    if (list->head == NULL) {
        printf("List is empty!\n");
        return;
    }

    Node* current = list->head;
    do {
        printf("%d <=> ", current->data);
        current = current->next;
    } while (current != list->head);
    printf("(back to head)\n");
}

int main() {
    DoublyLinkedCircularList list;
    list.head = NULL;
    int choice, data;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert Element\n");
        printf("2. Delete Element\n");
        printf("3. Display List\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &data);
                insert(&list, data);
                printf("Inserted %d into the list.\n", data);
                break;
            case 2:
                printf("Enter element to delete: ");
                scanf("%d", &data);
                deleteElement(&list, data);
                break;
            case 3:
                display(&list);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
