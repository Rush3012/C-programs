#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

void dfs(int adj[][MAX_NODES], int node, int numNodes, int visited[]);
void dfsAndCount(int adj[][MAX_NODES], int node, int numNodes, int visited[], int *count);
int countComponents(int adj[][MAX_NODES], int numNodes);
void printComponentSizes(int adj[][MAX_NODES], int numNodes);
int countBridges(int adj[][MAX_NODES], int numNodes);
int countArticulationPoints(int adj[][MAX_NODES], int numNodes);
int convertToInt(const char *str, int start, int end);

int main() {
    int numNodes;
    int adj[MAX_NODES][MAX_NODES];

    scanf("%d", &numNodes);
    getchar();

    // Initialize adjacency matrix
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            adj[i][j] = 0;
        }
    }

    // Populate adjacency matrix
    for (int i = 0; i < numNodes; i++) {
        char line[100];
        scanf(" %[^\n]", line);
        getchar();

        int index;
        int j = 0;
        while (line[j] != ' ' && line[j] != '\0') {
            j++;
        }
        index = convertToInt(line, 0, j);
        if (line[j] == ' ') {
            j++;
        }

        while (line[j] != '\0') {
            int k = j;
            while (line[j] != ' ' && line[j] != '\0') {
                j++;
            }

            int v = convertToInt(line, k, j);
            adj[index - 1][v - 1] = 1;
            adj[v - 1][index - 1] = 1;

            if (line[j] == ' ') {
                j++;
            }
        }
    }

    char ch;
    do {
        scanf(" %c", &ch);

        switch (ch) {
            case 'n':
                printf("%d\n", countComponents(adj, numNodes));
                break;
            case 's':
                printComponentSizes(adj, numNodes);
                printf("\n");
                break;
            case 'b':
                printf("%d\n", countBridges(adj, numNodes));
                break;
            case 'a':
                printf("%d\n", countArticulationPoints(adj, numNodes));
                break;
            case 't':
                exit(0);
                break;
        }
    } while (1);

    return 0;
}

void dfs(int adj[][MAX_NODES], int node, int numNodes, int visited[]) {
    visited[node] = 1;
    for (int i = 0; i < numNodes; i++) {
        if (adj[node][i] && !visited[i]) {
            dfs(adj, i, numNodes, visited);
        }
    }
}

void dfsAndCount(int adj[][MAX_NODES], int node, int numNodes, int visited[], int *count) {
    (*count)++;
    visited[node] = 1;
    for (int i = 0; i < numNodes; i++) {
        if (adj[node][i] && !visited[i]) {
            dfsAndCount(adj, i, numNodes, visited, count);
        }
    }
}

int countComponents(int adj[][MAX_NODES], int numNodes) {
    int visited[numNodes];
    int count = 0;

    for (int i = 0; i < numNodes; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < numNodes; i++) {
        if (!visited[i]) {
            dfs(adj, i, numNodes, visited);
            count++;
        }
    }

    return count;
}

void printComponentSizes(int adj[][MAX_NODES], int numNodes) {
    int visited[numNodes];

    for (int i = 0; i < numNodes; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < numNodes; i++) {
        if (!visited[i]) {
            int count = 0;
            dfsAndCount(adj, i, numNodes, visited, &count);
            printf("%d ", count);
        }
    }
}

int countBridges(int adj[][MAX_NODES], int numNodes) {
    int bridges = 0;
    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            if (adj[i][j] != 0) {
                adj[i][j] = 0;
                adj[j][i] = 0;
                int a2 = countComponents(adj, numNodes);
                adj[i][j] = 1;
                adj[j][i] = 1;
                int a1 = countComponents(adj, numNodes);
                if (a1 != a2) {
                    bridges++;
                }
            }
        }
    }
    return bridges / 2;
}

int countArticulationPoints(int adj[][MAX_NODES], int numNodes) {
    int points = 0;
    for (int z = 0; z < numNodes; z++) {
        int temp[MAX_NODES][MAX_NODES];
        int k = 0;
        int l = 0;
        for (int i = 0; i < numNodes; i++) {
            if (i == z) {
                continue;
            }
            for (int j = 0; j < numNodes; j++) {
                if (j == z) {
                    continue;
                }
                temp[k][l] = adj[i][j];
                l++;
            }
            k++;
            l = 0;
        }

        int a1 = countComponents(temp, numNodes - 1);
        int a2 = countComponents(adj, numNodes);

        if (a1 != a2) {
            points++;
        }
    }
    return points;
}

int convertToInt(const char *str, int start, int end) {
    int result = 0;
    for (int i = start; i < end && str[i] != '\0'; i++) {
        result = result * 10 + (str[i] - '0');
    }
    return result;
}
