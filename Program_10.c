#include <stdio.h>
#define MAX 10
#define INF 9999
int main() {
    int cost[MAX][MAX], dist[MAX], visited[MAX] = {0};
    int n, source, i, j, u, min;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter cost matrix:\n");
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    scanf("%d", &cost[i][j]);
    printf("Enter source vertex: ");
    scanf("%d", &source);
    for (i = 0; i < n; i++)
    dist[i] = cost[source][i];
    dist[source] = 0;
    visited[source] = 1;
    for (i = 1; i < n; i++) {
        min = INF;
        u = -1;
        for (j = 0; j < n; j++)
        if (!visited[j] && dist[j] < min) {
            min = dist[j];
            u = j;
        }
        if (u == -1)
        break;
        visited[u] = 1;
        for (j = 0; j < n; j++)
        if (!visited[j] &&
        dist[u] + cost[u][j] < dist[j])
        dist[j] = dist[u] + cost[u][j];
    }
    printf("Shortest distances:\n");
    for (i = 0; i < n; i++)
    printf("%d -> %d = %d\n", source, i, dist[i]);
    return 0;
}
