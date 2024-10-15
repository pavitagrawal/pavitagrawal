#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct TreeNode {
    char value;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(char value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

struct TreeNode* buildExpressionTree(char* postfix) {
    struct TreeNode** stack = (struct TreeNode**)malloc(100 * sizeof(struct TreeNode*));
    int top = -1;
    for (int i = 0; postfix[i] != '\0'; i++) {
        char current = postfix[i];
        if (isalnum(current)) {
            stack[++top] = createNode(current);
        } else if (isOperator(current)) {
            struct TreeNode* node = createNode(current);
            node->right = stack[top--];
            node->left = stack[top--];
            stack[++top] = node;
        }
    }
    struct TreeNode* root = stack[top];
    free(stack);
    return root;
}

int evaluateExpressionTree(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }
    if (!isOperator(root->value)) {
        return root->value - '0';  // Convert char to int
    }
    int leftEval = evaluateExpressionTree(root->left);
    int rightEval = evaluateExpressionTree(root->right);
    switch (root->value) {
        case '+': return leftEval + rightEval;
        case '-': return leftEval - rightEval;
        case '*': return leftEval * rightEval;
        case '/': return leftEval / rightEval;
    }
    return 0;
}

void freeTree(struct TreeNode* node) {
    if (node != NULL) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

int main() {
    char postfix[100];
    printf("Enter a postfix expression (use single digits and operators): ");
    scanf("%s", postfix);
    struct TreeNode* root = buildExpressionTree(postfix);
    int result = evaluateExpressionTree(root);
    printf("The result of the expression is: %d\n", result);
    freeTree(root);
    return 0;
}
