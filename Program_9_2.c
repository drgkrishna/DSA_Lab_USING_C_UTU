#include <stdio.h>
struct Edge {
    int u, v, w;
};
int parent[20];
int find(int x) {
    while (parent[x] != x)
    x = parent[x];
    return x;
}
void unite(int a, int b) {
    parent[find(a)] = find(b);
}
int main() {
    struct Edge e[50], t;
    int n, m, i, j, count = 0, total = 0;
    printf("Enter vertices and edges: ");
    scanf("%d%d", &n, &m);
    for (i = 0; i < m; i++) {
        printf("Enter u v weight: ");
        scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    }
    for (i = 0; i < n; i++)
    parent[i] = i;
    for (i = 0; i < m - 1; i++)
    for (j = 0; j < m - i - 1; j++)
    if (e[j].w > e[j + 1].w) {
        t = e[j];
        e[j] = e[j + 1];
        e[j + 1] = t;
    }
    printf("Edges in MST:\n");
    for (i = 0; i < m && count < n - 1; i++) {
        if (find(e[i].u) != find(e[i].v)) {
            printf("%d - %d : %d\n",
            e[i].u, e[i].v, e[i].w);
            total += e[i].w;
            unite(e[i].u, e[i].v);
            count++;
        }
    }
    printf("Minimum Cost = %d\n", total);
    return 0;
}
