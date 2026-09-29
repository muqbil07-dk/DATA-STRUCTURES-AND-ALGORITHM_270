#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    int n, q, i, u, v, edgeCount;
    int timer, top, current, edge;
    int *head, *to, *nextEdge;
    int *parent, *tin, *tout, *iter, *stack;
    int *nodeAt, *prefix;
    char *letters;

    if (scanf("%d %d", &n, &q) != 2) {
        return 0;
    }

    letters = (char *)malloc(
        (size_t)(n + 1) * sizeof(char));

    scanf("%s", letters + 1);

    head = (int *)malloc(
        (size_t)(n + 1) * sizeof(int));

    to = (int *)malloc(
        (size_t)(2 * n) * sizeof(int));

    nextEdge = (int *)malloc(
        (size_t)(2 * n) * sizeof(int));

    parent = (int *)calloc(
        (size_t)(n + 1), sizeof(int));

    tin = (int *)malloc(
        (size_t)(n + 1) * sizeof(int));

    tout = (int *)malloc(
        (size_t)(n + 1) * sizeof(int));

    iter = (int *)malloc(
        (size_t)(n + 1) * sizeof(int));

    stack = (int *)malloc(
        (size_t)(n + 1) * sizeof(int));

    nodeAt = (int *)malloc(
        (size_t)(n + 1) * sizeof(int));

    for (i = 1; i <= n; i++) {
        head[i] = -1;
    }

    edgeCount = 0;

    for (i = 0; i < n - 1; i++) {
        scanf("%d %d", &u, &v);

        to[edgeCount] = v;
        nextEdge[edgeCount] = head[u];
        head[u] = edgeCount++;

        to[edgeCount] = u;
        nextEdge[edgeCount] = head[v];
        head[v] = edgeCount++;
    }

    timer = 0;
    top = 0;

    stack[top++] = 1;
    parent[1] = -1;

    tin[1] = ++timer;
    nodeAt[timer] = 1;
    iter[1] = head[1];

    while (top > 0) {
        current = stack[top - 1];
        edge = iter[current];

        if (edge == -1) {
            tout[current] = timer;
            top--;
            continue;
        }

        iter[current] = nextEdge[edge];
        v = to[edge];

        if (v == parent[current]) {
            continue;
        }

        parent[v] = current;
        tin[v] = ++timer;
        nodeAt[timer] = v;
        iter[v] = head[v];

        stack[top++] = v;
    }

    prefix = (int *)calloc(
        (size_t)26 * (n + 1),
        sizeof(int));

    for (i = 1; i <= n; i++) {
        int c;

        c = letters[nodeAt[i]] - 'a';

        for (u = 0; u < 26; u++) {
            prefix[u * (n + 1) + i] =
                prefix[u * (n + 1) + i - 1];
        }

        prefix[c * (n + 1) + i]++;
    }

    while(q--) {
        scanf("%d %c", &u, &letters[0]);

        v = letters[0] - 'a';

        printf("%d\n",
               prefix[v * (n + 1) + tout[u]] -
               prefix[v * (n + 1) + tin[u
