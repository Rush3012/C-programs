#include <stdio.h>
#include <stdlib.h>

// Define the structure for the Binary Tree Node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new Binary Tree Node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to perform Level Order Traversal of the Binary Tree
void levelOrderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;

    // Queue for level order traversal
    struct TreeNode* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* current = queue[front++];
        printf("%d ", current->data);

        if (current->left != NULL)
            queue[rear++] = current->left;
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

// Function to calculate the maximum sum of a BST
int maxSumBSTUtil(struct TreeNode* root, int* maxSum, int* isBST, int* sum) {
    if (root == NULL) {
        *isBST = 1;
        return 0;
    }

    int leftSum = 0, rightSum = 0;
    int leftIsBST = 0, rightIsBST = 0;

    *sum = root->data;

    int leftMax = maxSumBSTUtil(root->left, &leftSum, &leftIsBST, sum);
    int rightMax = maxSumBSTUtil(root->right, &rightSum, &rightIsBST, sum);

    if (leftIsBST && rightIsBST && (root->left == NULL || root->data > leftMax) && (root->right == NULL || root->data < rightMax)) {
        *isBST = 1;
        *sum = leftSum + rightSum + root->data;
        *maxSum = (*maxSum > *sum) ? *maxSum : *sum;
        return root->data;
    } else {
        *isBST = 0;
        return 0;
    }
}

// Function to compute the maximum sum of all keys of any BST in the binary tree
int maximumSumBST(struct TreeNode* root) {
    int maxSum = 0;
    int isBST = 0;
    int sum;

    maxSumBSTUtil(root, &maxSum, &isBST, &sum);

    return maxSum;
}

// Function to print the right view of the Binary Tree
void rightView(struct TreeNode* root) {
    if (root == NULL)
        return;

    // Queue for level order traversal
    struct TreeNode* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* current = queue[front++];

            // Print the last node of each level
            if (i == levelSize - 1)
                printf("%d ", current->data);

            if (current->left != NULL)
                queue[rear++] = current->left;
            if (current->right != NULL)
                queue[rear++] = current->right;
        }
    }
}

// Function to parse the Parenthesis Representation and build the Binary Tree
struct TreeNode* buildTree(char* str, int* index) {
    if (str[*index] == '\0' || str[*index] == ')') {
        (*index)++;
        return NULL;
    }

    // Extract the data
    int num = 0;
    while (str[*index] >= '0' && str[*index] <= '9') {
        num = num * 10 + (str[*index] - '0');
        (*index)++;
    }

    struct TreeNode* root = createNode(num);

    if (str[*index] == '(') {
        (*index)++;
        root->left = buildTree(str, index);
    }

    if (str[*index] == '(') {
        (*index)++;
        root->right = buildTree(str, index);
    }

    (*index)++;
    return root;
}

int main() {
    char treeInput[500];
    fgets(treeInput, sizeof(treeInput), stdin);

    int index = 0;
    struct TreeNode* root = buildTree(treeInput, &index);

    char command;
    while (scanf(" %c", &command) == 1) {
        switch (command) {
            case 'l':
                levelOrderTraversal(root);
                printf("\n");
                break;
            case 'm':
                printf("%d\n", maximumSumBST(root));
                break;
            case 'r':
                rightView(root);
                printf("\n");
                break;
            default:
                printf("Invalid command\n");
                break;
        }
    }

    return 0;
}
