#include <stdio.h>
#define MAX 100     // Maximum number of vertices (nodes)
#define INF 9999    // Representing "infinity" (no direct edge)

// Dijkstra's Algorithm function
void dijkstra(int n, int g[MAX][MAX], int s) {
    int dist[MAX];        // Array to store shortest distance from source to each vertex
    int vis[MAX] = {0};   // Array to track visited vertices (0 = not visited, 1 = visited)

    // Step 1: Initialize distances
    for (int i = 0; i < n; i++)
        dist[i] = g[s][i];   // Distance from source to each vertex as per input matrix

    dist[s] = 0;             // Distance to itself is always 0
    vis[s] = 1;              // Mark source as visited

    // Step 2: Repeat (n-1) times to visit all vertices
    for (int c = 1; c < n; c++) {
        int min = INF, u = -1;

        // Step 2.1: Find the unvisited vertex with the smallest distance
        for (int i = 0; i < n; i++)
            if (!vis[i] && dist[i] < min) {
                min = dist[i];
                u = i;        // u is the vertex with the smallest known distance
            }

        if (u == -1) break;   // If no vertex found, stop (remaining vertices unreachable)

        vis[u] = 1;           // Step 2.2: Mark this vertex as visited

        // Step 2.3: Update the distances of neighboring vertices
        for (int v = 0; v < n; v++) {
            // If not visited, edge exists, and we found a shorter path → update
            if (!vis[v] && g[u][v] != INF && dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v];
            }
        }
    }

    // Step 3: Print final shortest distances from source
    printf("\nShortest distances from source %d:\n", s);
    for (int i = 0; i < n; i++)
        printf("To %d : %d\n", i, dist[i]);
}

// Main function
int main() {
    int n, g[MAX][MAX], s;

    // Input: number of vertices
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // Input: adjacency matrix
    printf("Enter adjacency matrix (use %d for no edge):\n", INF);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &g[i][j]);

    // Input: source vertex
    printf("Enter source vertex (0-%d): ", n-1);
    scanf("%d", &s);

    // Call Dijkstra’s algorithm
    dijkstra(n, g, s);

    return 0;
}
