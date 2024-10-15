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
struct TreeNode* deleteNode(struct TreeNode* root, int value) {
    if (root == NULL) {
        return root;
    }
    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        struct TreeNode* temp = root->right;
        while (temp && temp->left != NULL) {
            temp = temp->left;
        }
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}
int search(struct TreeNode* root, int value) {
    if (root == NULL) {
        return 0;
    }
    if (root->value == value) {
        return 1;
    }
    if (value < root->value) {
        return search(root->left, value);
    }
    return search(root->right, value);
}
void printTreeInOrder(struct TreeNode* node) {
    if (node != NULL) {
        printTreeInOrder(node->left);
        printf("%d ", node->value);
        printTreeInOrder(node->right);
    }
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
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. In-order Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value)) {
                    printf("Value %d found in the tree.\n", value);
                } else {
                    printf("Value %d not found in the tree.\n", value);
                }
                break;
            case 4:
                printf("In-order traversal of the tree: ");
                printTreeInOrder(root);
                printf("\n");
                break;
            case 5:
                freeTree(root);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
