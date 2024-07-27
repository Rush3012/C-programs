#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    char color;
    struct Node *left, *right, *parent;
};

struct Node *createNode(int key) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->color = 'R'; 
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

void printRBTree(struct Node *root) {
    if (root == NULL)
        return;

    printf("(%d%c(", root->key, root->color);
    printRBTree(root->left);
    printf(")(");
    printRBTree(root->right);
    printf("))");
}

void leftRotate(struct Node **root, struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void rightRotate(struct Node **root, struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    x->right = y;
    y->parent = x;
}

void fixInsert(struct Node **root, struct Node *z) {
    while (z->parent != NULL && z->parent->color == 'R') {
        if (z->parent == z->parent->parent->left) {
            struct Node *y = z->parent->parent->right;
            if (y != NULL && y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                rightRotate(root, z->parent->parent);
            }
        } else {
            struct Node *y = z->parent->parent->left;
            if (y != NULL && y->color == 'R') {
                z->parent->color = 'B';
                y->color = 'B';
                z->parent->parent->color = 'R';
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = 'B';
                z->parent->parent->color = 'R';
                leftRotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = 'B';
}

void insertInRedBlack(struct Node **root, int key) {
    struct Node *z = createNode(key);
    struct Node *y = NULL;
    struct Node *x = *root;

    while (x != NULL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        *root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    fixInsert(root, z);
}

int main() {
    struct Node *root = NULL;
    int key;
    char ch;

    do {
        scanf("%c", &ch);
        if (ch == 'e')
            break;
        else if (ch >= '0' && ch <= '9') {
            ungetc(ch, stdin);
            scanf("%d", &key);
            insertInRedBlack(&root, key);
            printRBTree(root);
            printf("\n");
        }
    } while (1);

    return 0;
}
