#include <stdio.h>
#define MAX 10
int graph[MAX][MAX], visited[MAX], n;
void BFS(int start) {
    int q[MAX], front = 0, rear = 0;
    int i, v;
    for (i = 0; i < n; i++)
    visited[i] = 0;
    q[rear++] = start;
    visited[start] = 1;
    printf("BFS: ");
    while (front < rear) {
        v = q[front++];
        printf("%d ", v);
        for (i = 0; i < n; i++) {
            if (graph[v][i] && !visited[i]) {
                visited[i] = 1;
                q[rear++] = i;
            }
        }
    }
    printf("\n");
}
void DFS(int v) {
    int i;
    visited[v] = 1;
    printf("%d ", v);
    for (i = 0; i < n; i++)
    if (graph[v][i] && !visited[i])
    DFS(i);
}
int main() {
    int i, j;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    scanf("%d", &graph[i][j]);
    BFS(0);
    for (i = 0; i < n; i++)
    visited[i] = 0;
    printf("DFS: ");
    DFS(0);
    return 0;
}
