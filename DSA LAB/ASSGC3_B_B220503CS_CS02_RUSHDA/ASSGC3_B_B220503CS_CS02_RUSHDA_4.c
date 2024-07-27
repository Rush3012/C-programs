#include <stdio.h>
#include <limits.h>

#define MAX_NODES 100 
#define INF INT_MAX

void printSolution(int dist[MAX_NODES][MAX_NODES], int V);

void floydWarshall(int graph[MAX_NODES][MAX_NODES], int V) {
    int dist[MAX_NODES][MAX_NODES], i, j, k;

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    printSolution(dist, V);
}

void printSolution(int dist[MAX_NODES][MAX_NODES], int V) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%d ", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int V;
    scanf("%d", &V);

    int graph[MAX_NODES][MAX_NODES];

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == -1) graph[i][j] = INF; 
        }
    }

    floydWarshall(graph, V);

    return 0;
}
