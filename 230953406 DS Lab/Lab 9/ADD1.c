#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct CircularDoublyLinkedList {
    Node* head;
} CircularDoublyLinkedList;

Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

void initList(CircularDoublyLinkedList* list) {
    list->head = createNode(0, 0); // Header node
    list->head->next = list->head; // Point to itself
    list->head->prev = list->head;
}

void appendTerm(CircularDoublyLinkedList* poly, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    Node* last = poly->head->prev;

    newNode->next = poly->head;
    newNode->prev = last;
    last->next = newNode;
    poly->head->prev = newNode;
}

void displayPoly(CircularDoublyLinkedList* poly) {
    Node* temp = poly->head->next;
    while (temp != poly->head) {
        if (temp->coeff != 0) {
            printf("%dx^%d ", temp->coeff, temp->exp);
            if (temp->next != poly->head) printf("+ ");
        }
        temp = temp->next;
    }
    printf("\n");
}

CircularDoublyLinkedList* multiplyPolynomials(CircularDoublyLinkedList* poly1, CircularDoublyLinkedList* poly2) {
    CircularDoublyLinkedList* result = (CircularDoublyLinkedList*)malloc(sizeof(CircularDoublyLinkedList));
    initList(result);

    Node* p1 = poly1->head->next;
    while (p1 != poly1->head) {
        Node* p2 = poly2->head->next;
        while (p2 != poly2->head) {
            int newCoeff = p1->coeff * p2->coeff;
            int newExp = p1->exp + p2->exp;
            appendTerm(result, newCoeff, newExp);
            p2 = p2->next;
        }
        p1 = p1->next;
    }

    return result;
}

int main() {
    CircularDoublyLinkedList poly1, poly2;

    initList(&poly1);
    initList(&poly2);

    appendTerm(&poly1, 5, 4);
    appendTerm(&poly1, 2, 3);
    appendTerm(&poly2, 3, 2);
    appendTerm(&poly2, 4, 0);

    printf("Polynomial 1: ");
    displayPoly(&poly1);

    printf("Polynomial 2: ");
    displayPoly(&poly2);

    CircularDoublyLinkedList* result = multiplyPolynomials(&poly1, &poly2);
    printf("Product: ");
    displayPoly(result);

    return 0;
}
