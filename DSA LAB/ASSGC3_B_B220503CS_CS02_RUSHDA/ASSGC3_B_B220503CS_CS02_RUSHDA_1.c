#include<stdio.h>
#include<stdlib.h>

struct Edge {
    int weight;
    int node;
    int parent;
    struct Edge* next;
};

struct PriorityQueue {
    struct Edge** heap;
    int capacity;
    int size;
};

struct PriorityQueue* init_priority_queue(int capacity) {
    struct PriorityQueue* pq = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    pq->heap = (struct Edge**)malloc(capacity * sizeof(struct Edge*));
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

void swap(struct Edge** a, struct Edge** b) {
    struct Edge* temp = *a;
    *a = *b;
    *b = temp;
}

void heap_up(struct PriorityQueue* pq, int index) {
    while (index > 0 && pq->heap[(index - 1) / 2]->weight >= pq->heap[index]->weight) 
    {
        if(pq->heap[(index - 1) / 2]->weight == pq->heap[index]->weight)
        {
            if(pq->heap[(index - 1) / 2]->node > pq->heap[index]->node)
            swap(&pq->heap[(index - 1) / 2], &pq->heap[index]);
            index = (index - 1) / 2;
        }
        else
        {
            swap(&pq->heap[(index - 1) / 2], &pq->heap[index]);
            index = (index - 1) / 2;
        }
    }
}

void heap_down(struct PriorityQueue* pq, int index) {
    int smallest = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;

    if (left_child < pq->size && pq->heap[left_child]->weight <= pq->heap[smallest]->weight)
    {
        if(pq->heap[left_child]->weight == pq->heap[smallest]->weight)
        {
            if(pq->heap[left_child]->node < pq->heap[smallest]->weight)
                smallest = left_child;
        }
        else
            smallest = left_child;
    }

    if (right_child < pq->size && pq->heap[right_child]->weight <= pq->heap[smallest]->weight)
    {
        if(pq->heap[right_child]->weight == pq->heap[smallest]->weight)
        {
            if(pq->heap[right_child]->node < pq->heap[smallest]->weight)
                smallest = right_child;
        }
        else
            smallest = right_child;
    }

    if (smallest != index) {
        swap(&pq->heap[index], &pq->heap[smallest]);
        heap_down(pq, smallest);
    }
}

void insert(struct PriorityQueue* pq, struct Edge* ele) {
    if (pq->size == pq->capacity) {
        return;
    }

    pq->heap[pq->size] = ele;
    pq->size++;
    heap_up(pq, pq->size - 1);
}

void pop(struct PriorityQueue* pq) {
    if (pq->size == 0) {
        return;
    }
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    heap_down(pq, 0);
}

void spanning_sequence(int start, struct PriorityQueue* pq, struct Edge* edgelist[], int num_nodes,int flag) {
    int mst_edges[1000];
    int m_ix = 0;
    
    int sum=0;

    int visited[num_nodes];
    for (int i = 0; i < num_nodes; i++)
        visited[i] = 0;

    struct Edge* ele = (struct Edge*)malloc(sizeof(struct Edge));
    ele->weight = 0;
    ele->node = start;
    ele->parent = -1;

    insert(pq, ele);

    while (pq->size != 0) {
        struct Edge* top = pq->heap[0];
        pop(pq);

        if (visited[top->node] == 0 ) {
            visited[top->node] = 1;
            sum += top->weight;

            if (top->parent != -1) {
                mst_edges[m_ix++] = top->parent;
                mst_edges[m_ix++] = top->node;
            }
            

            struct Edge* p = edgelist[top->node];
            while (p != NULL) {
                if (visited[p->node] == 0 && p->weight != 0)
                    insert(pq, p);
                p = p->next;
            }
        }
    }
    
    if(flag==0)
        printf("%d\n",sum);
    
    if(flag==1)
    {
        for (int i = 0; i < m_ix; i++)
            printf("%d ", mst_edges[i]);
        printf("\n");
    }
}

void construct_edges(char arr[], int parent, struct Edge* edgelist[]) {
    int node = 0;
    int index = 0;

    while (arr[index] != '\0') {

        if (arr[index] == '0') {
            node++;
            index++;
        } 
        else if (arr[index] > '0' && arr[index] <= '9') 
        {
            int weight=0;
            while(arr[index] >= '0' && arr[index] <= '9')
            {
                weight =(weight*10) + (arr[index] - '0');
                index++;
            }

            struct Edge* ele = (struct Edge*)malloc(sizeof(struct Edge));

            ele->weight = weight;
            ele->node = node;
            ele->parent = parent;
            ele->next = NULL;

            if (edgelist[parent] == NULL) {
                edgelist[parent] = ele;
            } else {
                struct Edge* p = edgelist[parent];
                while (p->next != NULL)
                    p = p->next;
                p->next = ele;
            }

            node++;
        } 
        
        else if (arr[index] == ' ')
            index++;
    }
}

int main() {
    int num_nodes;
    scanf("%d\n", &num_nodes);

    struct Edge* edgelist[num_nodes];
    for (int i = 0; i < num_nodes; i++)
        edgelist[i] = NULL;

    for (int parent = 0; parent < num_nodes; parent++) {
        char arr[1000];
        scanf(" %[^\n]", arr);
        construct_edges(arr, parent, edgelist);
    }

    struct PriorityQueue* pq = init_priority_queue(num_nodes * num_nodes);
    
    int flag=0;

    char ch;
    while (1) {
        scanf(" %c", &ch);
        switch (ch) {
            case 't':
                flag=0;
                spanning_sequence(0, pq, edgelist, num_nodes, flag);
                break;
                
            case 's':
                int s;
                scanf("(%d)",&s);
                flag=1;
                spanning_sequence(s, pq, edgelist, num_nodes, flag);
                break;
                

            case 'x':
                return 0;
        }
    }
    
    return 0;
}
