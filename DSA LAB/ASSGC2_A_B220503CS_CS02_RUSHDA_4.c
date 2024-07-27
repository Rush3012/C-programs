#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int data;
    Color color;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(int data, Color color) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = color;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* constructTree(char *str, int *index) {
    if (str[*index] == '(') (*index)++;
    if (str[*index] == ')') {
        (*index)++;
        return NULL;
    }

    int data = 0;
    Color color = BLACK;
    while (str[*index] != ' ' && str[*index] != '(' && str[*index] != ')') {
        if (str[*index] == 'R') color = RED;
        else if (str[*index] >= '0' && str[*index] <= '9') {
            data = data * 10 + (str[*index] - '0');
        }
        (*index)++;
    }
    Node* root = createNode(data, color);
    root->left = constructTree(str, index);
    root->right = constructTree(str, index);
    if (str[*index] == ')') (*index)++;
    return root;
}

bool isRedBlackTreeUtil(Node* root, int *blackHeight) {
    if (root == NULL) {
        *blackHeight = 1;
        return true;
    }

    int leftBlackHeight, rightBlackHeight;
    bool leftValid = isRedBlackTreeUtil(root->left, &leftBlackHeight);
    bool rightValid = isRedBlackTreeUtil(root->right, &rightBlackHeight);

    if (!leftValid || !rightValid) return false;

    if (leftBlackHeight != rightBlackHeight) return false;

    *blackHeight = leftBlackHeight;
    if (root->color == RED && ((root->left && root->left->color == RED) || (root->right && root->right->color == RED))) {
        return false;
    }

    if (root->color == BLACK) (*blackHeight)++;
    return true;
}

bool checkRedBlackTree(Node* root) {
    int blackHeight;
    return isRedBlackTreeUtil(root, &blackHeight);
}

int main() {
    char str[1000];
    fgets(str, sizeof(str), stdin);

    int index = 0;
    Node* root = constructTree(str, &index);

    if (checkRedBlackTree(root)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}
