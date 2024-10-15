#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int value;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct TreeNode* insert(struct TreeNode* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

void levelOrderTraversal(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    struct TreeNode** queue = (struct TreeNode**)malloc(100 * sizeof(struct TreeNode*));
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* current = queue[front++];
        printf("%d ", current->value);

        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }

    free(queue);
}

void freeTree(struct TreeNode* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

int main() {
    struct TreeNode* root = NULL;
    int choice, value;

    while (1) {
        printf("\nBinary Search Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Level Order Traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Level Order Traversal of the tree: ");
                levelOrderTraversal(root);
                printf("\n");
                break;
            case 3:
                freeTree(root);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
