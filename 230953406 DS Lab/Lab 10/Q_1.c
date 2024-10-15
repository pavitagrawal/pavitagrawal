#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void inorderTraversal(TreeNode* root) {
    TreeNode* stack[100];
    int top = -1;
    TreeNode* current = root;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->value);
        current = current->right;
    }
}

void postorderTraversal(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* stack[100];
    int top = -1;
    TreeNode* lastVisited = NULL;
    stack[++top] = root;

    while (top != -1) {
        TreeNode* current = stack[top];

        if (current->left == NULL && current->right == NULL ||
            (lastVisited && (lastVisited == current->left || lastVisited == current->right))) {
            printf("%d ", current->value);
            lastVisited = stack[top--];
        } else {
            if (current->right != NULL) stack[++top] = current->right;
            if (current->left != NULL) stack[++top] = current->left;
        }
    }
}

void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* stack[100];
    int top = -1;
    stack[++top] = root;

    while (top != -1) {
        TreeNode* current = stack[top--];
        printf("%d ", current->value);

        if (current->right != NULL) stack[++top] = current->right;
        if (current->left != NULL) stack[++top] = current->left;
    }
}

TreeNode* findParent(TreeNode* root, int target) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return NULL;

    if ((root->left && root->left->value == target) || (root->right && root->right->value == target)) {
        return root;
    }

    TreeNode* leftParent = findParent(root->left, target);
    if (leftParent != NULL) return leftParent;
    return findParent(root->right, target);
}

int depth(TreeNode* root) {
    if (root == NULL) return 0;
    int leftDepth = depth(root->left);
    int rightDepth = depth(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

int printAncestors(TreeNode* root, int target) {
    if (root == NULL) return 0;

    if (root->value == target) return 1;

    if (printAncestors(root->left, target) || printAncestors(root->right, target)) {
        printf("%d ", root->value);
        return 1;
    }
    return 0;
}

int countLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int main() {
    TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("In-order Traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Post-order Traversal: ");
    postorderTraversal(root);
    printf("\n");

    printf("Pre-order Traversal: ");
    preorderTraversal(root);
    printf("\n");

    TreeNode* parent = findParent(root, 5);
    printf("Parent of 5: %s\n", parent ? "Found" : "Not Found");

    printf("Depth of Tree: %d\n", depth(root));

    printf("Ancestors of 4: ");
    printAncestors(root, 4);
    printf("\n");

    printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));

    return 0;
}
