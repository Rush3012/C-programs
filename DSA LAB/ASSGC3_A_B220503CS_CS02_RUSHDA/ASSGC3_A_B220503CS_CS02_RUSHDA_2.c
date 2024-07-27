#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef int Graph[MAX_NODES][MAX_NODES];

typedef struct {
    int visited[MAX_NODES];
    int finishingT[MAX_NODES];
    int Degree[MAX_NODES];
    int count;
} SCCData;

void DFS(int node, int vertices, Graph g, SCCData *sccData) {
    sccData->visited[node] = 1;
    for (int i = 0; i < vertices; ++i) {
        if (g[node][i] && !sccData->visited[i]) {
            DFS(i, vertices, g, sccData);
        }
    }
    sccData->finishingT[sccData->count++] = node;
}

void DFS_Transposed(int node, int vertices, Graph tg, SCCData *sccData) {
    sccData->visited[node] = 1;
    for (int i = 0; i < vertices; ++i) {
        if (tg[node][i] && !sccData->visited[i]) {
            DFS_Transposed(i, vertices, tg, sccData);
        }
    }
}

int Number_of_strongly_components(int vertices, Graph g, Graph tg, SCCData *sccData) {
    for (int i = 0; i < vertices; ++i) {
        sccData->visited[i] = 0;
    }
    for (int i = 0; i < vertices; ++i) {
        if (!sccData->visited[i]) {
            DFS(i, vertices, g, sccData);
        }
    }
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            tg[j][i] = g[i][j];
        }
    }
    for (int i = 0; i < vertices; ++i) {
        sccData->visited[i] = 0;
    }
    int SCC_count = 0;
    for (int i = vertices - 1; i >= 0; --i) {
        if (!sccData->visited[sccData->finishingT[i]]) {
            DFS_Transposed(sccData->finishingT[i], vertices, tg, sccData);
            SCC_count++;
        }
    }
    return SCC_count;
}

int Is_Topological_sort_possible(int vertices, Graph g, int *Degree) {
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            if (g[i][j] == 1) {
                Degree[j]++;
            }
        }
    }
    int queue[MAX_NODES];
    int front = -1, rear = -1;
    for (int i = 0; i < vertices; ++i) {
        if (Degree[i] == 0) {
            queue[++rear] = i;
        }
    }
    int count = 0; 
    while (front != rear) {
        int current = queue[++front]; 
        count++; 
        for (int i = 0; i < vertices; ++i) {
            if (g[current][i] == 1) {
                Degree[i]--;
                if (Degree[i] == 0) {
                    queue[++rear] = i;
                }
            }
        }
    }
    if (count == vertices) {
        return 1;
    } else {
        return -1; 
    }
}

int main() {
    int vertices;
    scanf("%d", &vertices);
    Graph adjacencyMatrix, transposedAdjacencyMatrix;
    SCCData sccData;
    sccData.count = 0;
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }
    char option;
    do {
        scanf(" %c", &option);
        switch (option) {
            case 't':
                if (Is_Topological_sort_possible(vertices, adjacencyMatrix, sccData.Degree) == 1) {
                    printf("1\n");
                } else {
                    printf("-1\n");
                }
                break;
            case 'c':
                printf("%d\n", Number_of_strongly_components(vertices, adjacencyMatrix, transposedAdjacencyMatrix, &sccData));
                break;
        }
    } while (option != 'x');
    return 1;
}

