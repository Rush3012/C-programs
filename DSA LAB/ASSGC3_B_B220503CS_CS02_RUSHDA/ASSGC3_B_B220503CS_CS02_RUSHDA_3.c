#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int weight;
    int node;
    struct Node *next;
};

struct Node *createNode(int weight, int node) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->weight = weight;
    newNode->node = node;
    newNode->next = NULL;
    return newNode;
}

struct PriorityQueue {
    int capacity;
    int size;
    struct Node **heap;
};

void swap(struct Node **a, struct Node **b) {
    struct Node *temp = *a;
    *a = *b;
    *b = temp;
}

struct PriorityQueue *createPriorityQueue(int capacity) {
    struct PriorityQueue *pq = (struct PriorityQueue *)malloc(sizeof(struct PriorityQueue));
    pq->heap = (struct Node **)malloc(capacity * sizeof(struct Node *));
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

struct PriorityQueue *heapifyUp(struct PriorityQueue *pq, int index) {
    while (index > 0 && pq->heap[(index - 1) / 2]->weight > pq->heap[index]->weight) {
        swap(&pq->heap[(index - 1) / 2], &pq->heap[index]);
        index = (index - 1) / 2;
    }
    return pq;
}

struct PriorityQueue *heapifyDown(struct PriorityQueue *pq, int index) {
    int smallest = index;
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;

    if (leftChildIndex < pq->size && pq->heap[smallest]->weight > pq->heap[leftChildIndex]->weight)
        smallest = leftChildIndex;

    if (rightChildIndex < pq->size && pq->heap[smallest]->weight > pq->heap[rightChildIndex]->weight)
        smallest = rightChildIndex;

    if (smallest != index) {
        swap(&pq->heap[index], &pq->heap[smallest]);
        pq = heapifyDown(pq, smallest);
    }

    return pq;
}

void insert(struct PriorityQueue *pq, struct Node *element) {
    if (pq->size == pq->capacity)
        return;

    pq->heap[pq->size] = element;
    pq->size++;
    pq = heapifyUp(pq, pq->size - 1);
}

void pop(struct PriorityQueue *pq) {
    if (pq->size == 0)
        return;

    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
}

void labelList2(struct Node *arr[], char list[], int flag) {
    int listIndex = 0;
    int parent = 0;
    struct Node *p = NULL;

    while (list[listIndex] != '\0') {
        if (list[listIndex] == ' ') {
            listIndex++;
            continue;
        }

        int num = 0;
        while (list[listIndex] >= '0' && list[listIndex] <= '9') {
            num = (num * 10) + (list[listIndex] - '0');
            listIndex++;
        }

        if (flag == 0) {
            flag = 1;
            parent = num;
            p = arr[parent];
            continue;
        }

        p->weight = num;
        p = p->next;
    }
}

void labelList1(struct Node *arr[], char list[], int flag) {
    int listIndex = 0;
    int parent = 0;

    while (list[listIndex] != '\0') {
        if (list[listIndex] == ' ') {
            listIndex++;
            continue;
        }

        int num = 0;
        while (list[listIndex] >= '0' && list[listIndex] <= '9') {
            num = (num * 10) + (list[listIndex] - '0');
            listIndex++;
        }

        if (flag == 0) {
            flag = 1;
            parent = num;
            continue;
        }

        struct Node *element = createNode(-1, num);

        if (arr[parent] == NULL)
            arr[parent] = element;
        else {
            struct Node *p = arr[parent];
            while (p->next != NULL)
                p = p->next;
            p->next = element;
        }
    }
}

void dijkstra(struct Node *arr[], int src, int n) {
    int weight = 0;

    int dist[n + 1];
    for (int i = 1; i < n + 1; i++)
        dist[i] = INT_MAX;

    struct PriorityQueue *pq = createPriorityQueue(n * n);

    struct Node *element = createNode(0, src);
    insert(pq, element);
    dist[src] = 0;

    while (pq->size != 0) {
        struct Node *top = pq->heap[0];
        pop(pq);

        struct Node *p = arr[top->node];
        while (p != NULL) {
            weight = top->weight + p->weight;
            if (dist[p->node] > weight) {
                dist[p->node] = weight;
                struct Node *temp = createNode(weight, p->node);
                insert(pq, temp);
            }
            p = p->next;
        }
    }

    for (int i = 1; i < n + 1; i++)
        printf("%d ", dist[i]);
}

int main() {
    int n;
    scanf("%d\n", &n);

    struct Node *arr[n + 1];
    for (int i = 0; i < n + 1; i++)
        arr[i] = NULL;

    for (int i = 0; i < n; i++) {
        char list[1000];
        scanf(" %[^\n]", list);
        int flag = 0;
        labelList1(arr, list, flag);
    }

    for (int i = 0; i < n; i++) {
        char list[1000];
        scanf(" %[^\n]", list);
        int flag = 0;
        labelList2(arr, list, flag);
    }

    int src;
    scanf("%d\n", &src);

    dijkstra(arr, src, n);

    return 0;
}
