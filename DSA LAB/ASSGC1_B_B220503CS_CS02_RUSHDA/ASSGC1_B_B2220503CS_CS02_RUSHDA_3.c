#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left, *right;
};

struct TreeNode* createNode(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct TreeNode* buildBST(char **str) {
    if (**str == '\0' || **str == ')') return NULL;

    int num = 0;
    while (**str >= '0' && **str <= '9') {
        num = num * 10 + (**str - '0');
        (*str)++;
    }

    struct TreeNode *root = createNode(num);

    if (**str == '(') {
        (*str)++;
        root->left = buildBST(str);
        if (**str == ')') (*str)++;
        (*str)++;
        root->right = buildBST(str);
        if (**str == ')') (*str)++;
    }

    return root;
}

void printInRange(struct TreeNode *root, int k1, int k2) {
    if (!root) return;

    if (root->data >= k1) printInRange(root->left, k1, k2);
    if (root->data >= k1 && root->data <= k2) printf("%d ", root->data);
    if (root->data <= k2) printInRange(root->right, k1, k2);
}

int printPathToValue(struct TreeNode *root, int target) {
    if (!root) return 0;

    if (root->data == target) {
        printf("%d ", root->data);
        return 1;
    }

    if (printPathToValue(root->left, target) || printPathToValue(root->right, target)) {
        printf("%d ", root->data);
        return 1;
    }

    return 0;
}

int main() {
    char str[10000];
    scanf("%s", str);
    char *p = str;
    struct TreeNode *root = buildBST(&p);

    char ch;
    int k1, k2;
    do {
        scanf(" %c", &ch);
        switch (ch) {
            case 'p':
                scanf("%d %d", &k1, &k2);
                printInRange(root, k1, k2);
                printf("\n");
                break;
            case 'a':
                scanf("%d", &k1);
                if (printPathToValue(root, k1)) {
                    printf("\n");
                } else {
                    printf(" \n");
                }
                break;
        }
    } while (ch != 'e');

    return 0;
}
