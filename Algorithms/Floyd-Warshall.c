#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100

// Function to find the shortest paths using Floyd-Warshall algorithm
void floydWarshall(int graph[MAX_VERTICES][MAX_VERTICES], int numVertices) {
    int dist[MAX_VERTICES][MAX_VERTICES];
    int i, j, k;

    // Initialize the distance matrix
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Find the shortest path between all pairs of vertices
    for (k = 0; k < numVertices; k++) {
        for (i = 0; i < numVertices; i++) {
            for (j = 0; j < numVertices; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Print the shortest distances
    printf("Shortest distances between all pairs of vertices:\n");
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            if (dist[i][j] == INT_MAX) {
                printf("INF\t");
            } else {
                printf("%d\t", dist[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int numVertices, i, j;
    int graph[MAX_VERTICES][MAX_VERTICES];

    // Get the number of vertices in the graph
    printf("Enter the number of vertices in the graph (up to %d): ", MAX_VERTICES);
    scanf("%d", &numVertices);

    // Get the adjacency matrix
    printf("Enter the adjacency matrix (enter INF for infinity):\n");
    for (i = 0; i < numVertices; i++) {
        for (j = 0; j < numVertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Call the Floyd-Warshall function
    floydWarshall(graph, numVertices);

    return 0;
}

