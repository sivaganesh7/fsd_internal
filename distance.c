#include <stdio.h>
#define MAX 10
#define INF 9999

int main() {
    int nodes, i, j, k;
    int distance[MAX][MAX], via[MAX][MAX];

    printf("Enter number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter cost matrix:\n");
    for (i = 0; i < nodes; i++)
        for (j = 0; j < nodes; j++) {
            scanf("%d", &distance[i][j]);
            if (distance[i][j] == 0 && i != j)
                distance[i][j] = INF;
            via[i][j] = j;
        }

    // Distance vector algorithm
    for (k = 0; k < nodes; k++)
        for (i = 0; i < nodes; i++)
            for (j = 0; j < nodes; j++)
                if (distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                    via[i][j] = via[i][k];
                }

    printf("\nRouting tables:\n");
    for (i = 0; i < nodes; i++) {
        printf("Router %d:\n", i + 1);
        for (j = 0; j < nodes; j++)
            printf("To %d via %d distance %d\n", j + 1, via[i][j] + 1, distance[i][j]);
        printf("\n");
    }
}
