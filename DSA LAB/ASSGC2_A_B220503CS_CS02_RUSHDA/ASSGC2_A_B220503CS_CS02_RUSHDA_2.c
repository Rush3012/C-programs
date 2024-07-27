#include <stdio.h>
#include <stdlib.h>


struct AVLNode {
    int key;
    int value;
    struct AVLNode *left;
    struct AVLNode *right;
    int size; // Added to track size of subtree
};

typedef struct AVLNode AVLTree;

struct AVLNode *newNode(int key, int value) {
    struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    node->key = key;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    node->size = 1; 
    return node;
}

struct AVLNode *insert(struct AVLNode *node, int key, int value) {
    if (node == NULL)
        return newNode(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else { 
        node->value = value;
        return node;
    }

    node->size++;

    return node;
}

void lowerbound(struct AVLNode *root, int key) {
    struct AVLNode *current = root;
    struct AVLNode *result = NULL;

    while (current != NULL) {
        if (current->key >= key) {
            result = current;
            current = current->left;
        } else
            current = current->right;
    }

    if (result != NULL)
        printf("%d %d\n", result->key, result->value);
    else
        printf("-1\n");
}

void find(struct AVLNode *root, int key) {
    struct AVLNode *current = root;

    while (current != NULL) {
        if (current->key == key) {
            printf("%d %d\n", current->key, current->value);
            return;
        } else if (current->key > key)
            current = current->left;
        else
            current = current->right;
    }

    printf("-1\n");
}

void printElements(struct AVLNode *root) {
    if (root != NULL) {
        printElements(root->left);
        printf("%d ", root->key);
        printElements(root->right);
    }
}

void size(struct AVLNode *root) {
    if (root == NULL)
        printf("0\n");
    else
        printf("%d\n", root->size);
}

void empty(struct AVLNode *root) {
    if (root == NULL)
        printf("1\n");
    else
        printf("0\n");
}

void freeAVLTree(struct AVLNode *root) {
    if (root == NULL)
        return;

    freeAVLTree(root->left);
    freeAVLTree(root->right);
    free(root);
}

int main() {
    struct AVLNode *root = NULL;
    char choice;
    int key, value;

    while (1) {
        scanf(" %c", &choice);

        switch (choice) {
            case 'i':
                scanf("%d %d", &key, &value);
                root = insert(root, key, value);
                break;
            case 'l':
                scanf("%d", &key);
                lowerbound(root, key);
                break;
            case 'f':
                scanf("%d", &key);
                find(root, key);
                break;
            case 's':
                size(root);
                break;
            case 'e':
                empty(root);
                break;
            case 'p':
                if (root == NULL)
                    printf("-1\n");
                else
                    printElements(root);
                printf("\n");
                break;
            case 't':
                freeAVLTree(root);
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
