#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;
typedef struct LinkedList {
    Node* head;
    int size;
} LinkedList;
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}
void initList(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}
void appendTerm(LinkedList* poly, int coeff, int exp) {
    Node* newNode = createNode(coeff, exp);
    if (poly->head == NULL || poly->head->exp < exp) {
        newNode->next = poly->head;
        poly->head = newNode;
    } else {
        Node* temp = poly->head;
        while (temp->next != NULL && temp->next->exp >= exp) {
            temp = temp->next;
        }
        if (temp->exp == exp) {
            temp->coeff += coeff;
            free(newNode);
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }
    poly->size++;
}

void displayPoly(LinkedList* poly) {
    Node* temp = poly->head;
    while (temp != NULL) {
        if (temp->coeff != 0) {
            printf("%dx^%d", temp->coeff, temp->exp);
            if (temp->next != NULL && temp->next->coeff > 0) {
                printf(" + ");
            }
        }
        temp = temp->next;
    }
    printf("\n");
}

LinkedList* addPolynomials(LinkedList* poly1, LinkedList* poly2) {
    LinkedList* result = (LinkedList*)malloc(sizeof(LinkedList));
    initList(result);

    Node* p1 = poly1->head;
    Node* p2 = poly2->head;



    while (p1 != NULL) {
        appendTerm(result, p1->coeff, p1->exp);
        p1 = p1->next;
    }
    while (p2 != NULL) {
        appendTerm(result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}
int main() {
    LinkedList poly1;
    LinkedList poly2;
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
    LinkedList* result = addPolynomials(&poly1, &poly2);
    printf("Sum: ");
    displayPoly(result);
    return 0;
}
