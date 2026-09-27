#include <stdio.h>
#define INF 9999
#define MAX 10
int main() {
    int cost[MAX][MAX], selected[MAX] = {0};
    int n, edges = 0, total = 0;
    int i, j, x, y, min;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter cost matrix:\n");
    for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    scanf("%d", &cost[i][j]);
    selected[0] = 1;
    printf("Edges in MST:\n");
    while (edges < n - 1) {
        min = INF;
        for (i = 0; i < n; i++)
        if (selected[i])
        for (j = 0; j < n; j++)
        if (!selected[j] && cost[i][j] < min) {
            min = cost[i][j];
            x = i;
            y = j;
        }
        printf("%d - %d : %d\n", x, y, min);
        total += min;
        selected[y] = 1;
        edges++;
    }
    printf("Minimum Cost = %d\n", total);
    return 0;
}
