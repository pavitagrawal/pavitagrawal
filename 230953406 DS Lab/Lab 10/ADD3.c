#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
Node* copyTree(Node* original) {
    if (original == NULL) {
        return NULL;
    }
    Node* newNode = createNode(original->data);
    newNode->left = copyTree(original->left);
    newNode->right = copyTree(original->right);
    return newNode;
}
void printInorder(Node* root) {
    if (root != NULL) {
        printInorder(root->left);
        printf("%d ", root->data);
        printInorder(root->right);
    }
}
int main() {
    Node *originalRoot = createNode(1);
    originalRoot->right = createNode(2);
    originalRoot->left = createNode(3);
    originalRoot->left->left= createNode(0);
    originalRoot->right->left = createNode(4);
    originalRoot->right->right = createNode(5);
    printf("Original Tree (Inorder Traversal): ");
    printInorder(originalRoot);
    Node* copiedRoot = copyTree(originalRoot);
    printf("\nCopied Tree (Inorder Traversal): ");
    printInorder(copiedRoot);
    printf("\n");
    return 0;
}
