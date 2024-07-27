#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 200

typedef struct {
    int key;
    bool occupied;
} HashEntry;

void unionAB(int A[], int B[], int m, int n) {
    HashEntry hashTable[MAX_SIZE * 2] = {0};

    for (int i = 0; i < m; i++) {
        if (!hashTable[A[i]].occupied) {
            printf("%d ", A[i]);
            hashTable[A[i]].occupied = true;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!hashTable[B[i]].occupied) {
            printf("%d ", B[i]);
            hashTable[B[i]].occupied = true;
        }
    }
    printf("\n");
}

void intersectionAB(int A[], int B[], int m, int n) {
    HashEntry hashTable[MAX_SIZE * 2] = {0};

    for (int i = 0; i < m; i++) {
        hashTable[A[i]].occupied = true;
    }

    for (int i = 0; i < n; i++) {
        if (hashTable[B[i]].occupied) {
            printf("%d ", B[i]);
            hashTable[B[i]].occupied = false; 
        }
    }
    printf("\n");
}

void setDifferenceAB(int A[], int B[], int m, int n) {
    HashEntry hashTable[MAX_SIZE * 2] = {0};
    bool isDifference = false;

    for (int i = 0; i < n; i++) {
        hashTable[B[i]].occupied = true;
    }

    for (int i = 0; i < m; i++) {
        if (!hashTable[A[i]].occupied) {
            printf("%d ", A[i]);
            isDifference = true;
        }
    }

    if (!isDifference) {
        printf("-1");
    }

    printf("\n");
}


int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int A[m], B[n];
    for (int i = 0; i < m; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &B[i]);
    }

    char op, firstArray, secondArray;
    while (true) {
        scanf(" %c %c %c", &op, &firstArray, &secondArray);
        if (op == 'e') {
            break;
        }
        if (op == 'u') {
            if (firstArray == 'A' && secondArray == 'B') {
                unionAB(A, B, m, n);
            } else {
                unionAB(B, A, n, m);
            }
        } else if (op == 'i') {
            if (firstArray == 'A' && secondArray == 'B') {
               intersectionAB(B, A, n, m);
            } else {
                 intersectionAB(A, B, m, n);
                
            }
        } else if (op == 's') {
            if (firstArray == 'A' && secondArray == 'B') {
                setDifferenceAB(A, B, m, n);
            } else {
                setDifferenceAB(B, A, n, m);
            }
        }
    }

    return 0;
}
