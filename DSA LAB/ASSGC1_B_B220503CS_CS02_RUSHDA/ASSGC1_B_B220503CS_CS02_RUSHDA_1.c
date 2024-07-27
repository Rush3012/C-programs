#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};


struct TreeNode* newNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}


int searchIndex(int arr[], int start, int end, int target) {
    int index;
    for (index = start; index <= end; index++) {
        if (arr[index] == target)
            return index;
    }
    return -1;
}

struct TreeNode* buildTreeHelper(int inorder[], int preorder[], int inStart, int inEnd, int* preIndex) {
    if (inStart > inEnd)
        return NULL;

    struct TreeNode* node = newNode(preorder[*preIndex]);
    (*preIndex)++;

    if (inStart == inEnd)
        return node;

    int inIndex = searchIndex(inorder, inStart, inEnd, node->data);

    node->left = buildTreeHelper(inorder, preorder, inStart, inIndex - 1, preIndex);
    node->right = buildTreeHelper(inorder, preorder, inIndex + 1, inEnd, preIndex);

    return node;
}

struct TreeNode* buildTree(int inorder[], int preorder[], int n) {
    int preIndex = 0;
    return buildTreeHelper(inorder, preorder, 0, n - 1, &preIndex);
}

void postOrderTraversal(struct TreeNode* node) {
    if (node == NULL)
        return;
    postOrderTraversal(node->left);
    postOrderTraversal(node->right);
    printf("%d ", node->data);
}

int calculateHeight(struct TreeNode* node) {
    if (node == NULL)
        return 0;
    else {
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
    }
}

void printLevel(struct TreeNode* root, int level, int leftToRight) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1) {
        if (leftToRight) {
            printLevel(root->left, level - 1, leftToRight);
            printLevel(root->right, level - 1, leftToRight);
        } else {
            printLevel(root->right, level - 1, leftToRight);
            printLevel(root->left, level - 1, leftToRight);
        }
    }
}

void printZigZag(struct TreeNode* root) {
    int height = calculateHeight(root);
    int i;

    int leftToRight = 1;
    for (i = 1; i <= height; i++) {
        printLevel(root, i, leftToRight);
        leftToRight = !leftToRight;
    }
}

void printMaxAtEachLevel(struct TreeNode* root) {
    int height = calculateHeight(root), level;
    for (level = 1; level <= height; level++) {
        int max = INT_MIN;
        findMaxAtLevel(root, level, &max);
        printf("%d ", max);
    }
}

void findMaxAtLevel(struct TreeNode* node, int level, int* max) {
    if (node == NULL) return;
    if (level == 1) {
        if (node->data > *max) *max = node->data;
    } else if (level > 1) {
        findMaxAtLevel(node->left, level - 1, max);
        findMaxAtLevel(node->right, level - 1, max);
    }
}

int calculateDiameter(struct TreeNode* tree, int* height) {
    int leftHeight = 0, rightHeight = 0;
    int leftDiameter = 0, rightDiameter = 0;

    if (tree == NULL) {
        *height = 0;
        return 0;
    }

    leftDiameter = calculateDiameter(tree->left, &leftHeight);
    rightDiameter = calculateDiameter(tree->right, &rightHeight);

    *height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

    return (leftHeight + rightHeight + 1) > (leftDiameter > rightDiameter ? leftDiameter : rightDiameter)
               ? (leftHeight + rightHeight + 1)
               : (leftDiameter > rightDiameter ? leftDiameter : rightDiameter);
}

int getDiameter(struct TreeNode* tree) {
    int height = 0;
    return calculateDiameter(tree, &height);
}

int sumOfLeftLeaves(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    int result = 0;
    if (root->left != NULL) {
        if (root->left->left == NULL && root->left->right == NULL)
            result += root->left->data;
    }

    result += sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    int inorder[n];
    int preorder[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
    }

   struct TreeNode* root = NULL;

    int preIndex = 0;
    root = buildTree(inorder, preorder, n);

    char option;
    do {
        scanf(" %c", &option);
        switch (option) {
            case 'p':
                postOrderTraversal(root);
                printf("\n");
                break;
            case 'z':
                printZigZag(root);
                printf("\n");
                break;
            case 'm':
                printMaxAtEachLevel(root);
                printf("\n");
                break;
            case 'd':
                printf("%d\n", getDiameter(root));
                break;
            case 's':
                printf("%d\n", sumOfLeftLeaves(root));
                break;
        }
    } while (option != 'e');

    return 0;
}
