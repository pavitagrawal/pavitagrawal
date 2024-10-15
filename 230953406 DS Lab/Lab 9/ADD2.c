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

CircularDoublyLinkedList* addPolynomials(CircularDoublyLinkedList* poly1, CircularDoublyLinkedList* poly2) {
    CircularDoublyLinkedList* result = (CircularDoublyLinkedList*)malloc(sizeof(CircularDoublyLinkedList));
    initList(result);

    Node* p1 = poly1->head->next;
    Node* p2 = poly2->head->next;

    while (p1 != poly1->head && p2 != poly2->head) {
        if (p1->exp == p2->exp) {
            appendTerm(result, p1->coeff + p2->coeff, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        } else if (p1->exp > p2->exp) {
            appendTerm(result, p1->coeff, p1->exp);
            p1 = p1->next;
        } else {
            appendTerm(result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    while (p1 != poly1->head) {
        appendTerm(result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while (p2 != poly2->head) {
        appendTerm(result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Main function for addition
int main() {
    CircularDoublyLinkedList poly1, poly2;

    initList(&poly1);
    initList(&poly2);

    appendTerm(&poly1, 5, 3);
    appendTerm(&poly1, 2, 1);
    appendTerm(&poly2, 3, 2);
    appendTerm(&poly2, 2, 1);

    printf("Polynomial 1: ");
    displayPoly(&poly1);

    printf("Polynomial 2: ");
    displayPoly(&poly2);

    CircularDoublyLinkedList* result = addPolynomials(&poly1, &poly2);
    printf("Sum: ");
    displayPoly(result);

    return 0;
}
