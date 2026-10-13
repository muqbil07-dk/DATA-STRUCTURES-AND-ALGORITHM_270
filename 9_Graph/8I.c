#include <stdio.h>
#include <stdlib.h>
struct Edge {
    int to;
    int next;
};
int *head_array;
struct Edge *edges;
int edge_count;
int *parent_array;
int *order_array;
int *stack_array;
int order_count;
int *dp_free;
int *dp_blocked;
void link(int i,int j)
{
    edges[edge_count].to = j;
    edges[edge_count].next = head_array[i];
    head_array[i] = edge_count;
    edge_count++;
}
void dfs(int p,int i)
{
    int stack_size = 0;
    int v;
    int e;
    int child;

    parent_array[i] = p;
    stack_array[stack_size++] = i;
    order_count = 0;

    while (stack_size > 0) {
        v = stack_array[--stack_size];
        order_array[order_count++] = v;
        e = head_array[v];
        while (e != -1) {
            child = edges[e].to;
            if (child != parent_array[v]) {
                parent_array[child] = v;
                stack_array[stack_size++] = child;
            }
            e = edges[e].next;
        }
    }
}

int main(void)
{
    int n;
    int i;
    int a;
    int b;
    int e;
    int v;
    int child;
    int base;
    int gain;
    int best_gain;
    int answer;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    head_array = (int *)malloc((n + 1) * sizeof(int));
    edges = (struct Edge *)malloc((2 * n + 2) * sizeof(struct Edge));
    parent_array = (int *)malloc((n + 1) * sizeof(int));
    order_array = (int *)malloc((n + 1) * sizeof(int));
    stack_array = (int *)malloc((n + 1) * sizeof(int));
    dp_free = (int *)malloc((n + 1) * sizeof(int));
    dp_blocked = (int *)malloc((n + 1) * sizeof(int));

    for (i = 1; i <= n; i++) {
        head_array[i] = -1;
        parent_array[i] = 0;
    }
    edge_count = 0;
    for (i = 0; i < n - 1; i++) {
        scanf("%d %d", &a, &b);
        link(a, b);
        link(b, a);
    }

    dfs(0, 1);

    for (i = order_count - 1; i >= 0; i--) {
        v = order_array[i];
        base = 0;
        for (e = head_array[v]; e != -1; e = edges[e].next) {
            child = edges[e].to;
            if (child == parent_array[v]) {
                continue;
            }
            base += dp_free[child];
        }
        dp_blocked[v] = base;
        best_gain = 0;
        for (e = head_array[v]; e != -1; e = edges[e].next) {
            child = edges[e].to;
            if (child == parent_array[v]) {
                continue;
            }
            gain = 1 + dp_blocked[child] - dp_free[child];
            if (gain > best_gain) {
                best_gain = gain;
            }
        }
        dp_free[v] = base + best_gain;
    }

    answer = dp_free[1];
    printf("%d\n", answer);

    free(head_array);
    free(edges);
    free(parent_array);
    free(order_array);
    free(stack_array);
    free(dp_free);
    free(dp_blocked);
    return 0;
}

