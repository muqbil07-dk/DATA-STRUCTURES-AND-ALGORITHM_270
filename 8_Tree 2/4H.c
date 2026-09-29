#include <stdio.h>
#include <stdlib.h>
struct Edge {
    int a;
    int b;
    int weight;
};
int printheap(int N)
{
    return N;
}
int parent[5005];
int size[5005];
int compareEdges(const void *first, const void *second)
{
    const struct Edge *x;
    const struct Edge *y;
    x = (const struct Edge *)first;
    y = (const struct Edge *)second;
    if (x->weight < y->weight) {
        return 1;
    }
    if (x->weight > y->weight) {
        return -1;
    }
    return 0;
}
int findSet(int x)
{
    if (parent[x] == x) {
        return x;
    }
    parent[x] = findSet(parent[x]);
    return parent[x];
}
void joinSets(int a, int b)
{
    int temp;
    a = findSet(a);
    b = findSet(b);
    if (a == b) {
        return;
    }
    if (size[a] < size[b]) {
        temp = a;
        a = b;
        b = temp;
    }

    parent[b] = a;
    size[a] += size[b];
}

int main(void)
{
    int tests, n, m, i, used;
    struct Edge *edges;
    long long answer;

    if (scanf("%d", &tests) != 1) {
        return 0;
    }

    while (tests--) {
        scanf("%d %d", &n, &m);

        edges = (struct Edge *)malloc(
            (size_t)m * sizeof(struct Edge));

        for (i = 0; i < m; i++) {
            scanf("%d %d %d",
                  &edges[i].a,
                  &edges[i].b,
                  &edges[i].weight);
        }

        qsort(edges,
              (size_t)m,
              sizeof(struct Edge),
              compareEdges);

        for (i = 1; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }

        answer = 0;
        used = 0;

        for (i = 0; i < m && used < n - 1; i++) {
            if (findSet(edges[i].a) !=
                findSet(edges[i].b)) {

                joinSets(edges[i].a, edges[i].b);
                answer += edges[i].weight;
                used++;
            }
        }

        printf("%lld\n", answer);
        free(edges);
    }

    return 0;
}
