#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100

int graph[MAX_NODES][MAX_NODES + 1]; // Adjacency list representation
int visited[MAX_NODES] = {0};
int path[MAX_NODES];
int N;

void printPath(int path[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

void findAllPathsUtil(int src, int dest, int path[], int path_len) {
    visited[src] = 1;
    path[path_len] = src;
    path_len++;

    if (src == dest) {
        printPath(path, path_len);
    } else {
        for (int i = 1; i <= graph[src][0]; i++) {
            int adj = graph[src][i];
            if (!visited[adj]) {
                findAllPathsUtil(adj, dest, path, path_len);
            }
        }
    }

    path_len--;
    visited[src] = 0;
}

void findAllPaths(int src, int dest) {
    memset(visited, 0, sizeof(visited));
    findAllPathsUtil(src, dest, path, 0);
}

int isCyclicUtil(int v, int parent) {
    visited[v] = 1;
    for (int i = 1; i <= graph[v][0]; i++) {
        int adj = graph[v][i];

        if (!visited[adj]) {
            if (isCyclicUtil(adj, v))
                return 1;
        } else if (adj != parent) {
            return 1;
        }
    }
    return 0;
}

int isConnected() {
    memset(visited, 0, sizeof(visited));
    isCyclicUtil(0, -1); // Start DFS from node 0, assuming 0 is always a part of the graph for simplicity.
    for (int i = 0; i < N; i++) {
        if (!visited[i])
            return 0; // Node i is not connected
    }
    return 1; // All nodes are connected
}

void isTree() {
    memset(visited, 0, sizeof(visited));
    if (isCyclicUtil(0, -1) == 0 && isConnected())
        printf("1\n"); // Graph is a tree
    else
        printf("-1\n"); // Graph is not a tree
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        int u, count = 0, v;
        scanf("%d", &u);
        while (scanf("%d", &v) == 1) {
            graph[u][++count] = v;
            char c = getchar();
            if (c == '\n' || c == EOF) break;
        }
        graph[u][0] = count; // Store the count of neighbors at index 0
    }

    char cmd;
    while (scanf(" %c", &cmd) && cmd != 'x') {
        if (cmd == 'a') {
            int src, dest;
            scanf("%d %d", &src, &dest);
            findAllPaths(src, dest);
        } else if (cmd == 't') {
            isTree();
        }
    }

    return 0;
}