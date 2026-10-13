#include <stdio.h>
#include <stdlib.h>
struct Road {
    int u;
    int v;
    int start;
    int length;
};
int *parent_array;
int *component_size;
int find_set(int value)
{
    if (parent_array[value] != value) {
        parent_array[value] = find_set(parent_array[value]);
    }
    return parent_array[value];
}
void join_sets(int a, int b)
{
    a = find_set(a);
    b = find_set(b);
    if (a == b) {
        return;
    }
    if (component_size[a] < component_size[b]) {
        int temp = a;
        a = b;
        b = temp;
    }
    parent_array[b] = a;
    component_size[a] += component_size[b];
}

int can_travel(int n, int m, struct Road roads[], int required[], int chosen[])
{
    int i;
    int j;
    int a;
    int b;
    int root;

    for(i=1;i<=n;++i) {
        parent_array[i] = i;
        component_size[i] = 1;
    }

    for (i = 0; i < m; i++) {
        int usable = 1;
        for (j = 0; j < roads[i].length; j++) {
            if (!chosen[required[roads[i].start + j]]) {
                usable = 0;
                break;
            }
        }
        if (usable) {
            join_sets(roads[i].u, roads[i].v);
        }
    }

    root = find_set(1);
    for (a = 2; a <= n; a++) {
        b = find_set(a);
        if (b != root) {
            return 0;
        }
    }
    return 1;
}

int main(void)
{
    int n;
    int m;
    int k;
    int i;
    int j;
    int total_required = 0;
    long long answer = 0;
    long long *cost;
    int *chosen;
    int *required;
    struct Road *roads;

    if (scanf("%d %d %d", &n, &m, &k) != 3) {
        return 0;
    }

    cost = (long long *)malloc((k + 1) * sizeof(long long));
    chosen = (int *)malloc((k + 1) * sizeof(int));
    roads = (struct Road *)malloc(m * sizeof(struct Road));

    for (i = 1; i <= k; i++) {
        scanf("%lld", &cost[i]);
        chosen[i] = 1;
    }

    /* Since k is at most about 60 when the costs are bounded by 10^18,
       this is a safe simple storage bound for all road requirements. */
    required = (int *)malloc((m * k + 1) * sizeof(int));

    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &roads[i].u, &roads[i].v, &roads[i].length);
        roads[i].start = total_required;
        for (j = 0; j < roads[i].length; j++) {
            scanf("%d", &required[total_required]);
            total_required++;
        }
    }

    parent_array = (int *)malloc((n + 1) * sizeof(int));
    component_size = (int *)malloc((n + 1) * sizeof(int));

    if (!can_travel(n, m, roads, required, chosen)) {
        printf("-1\n");
        free(cost);
        free(chosen);
        free(required);
        free(roads);
        free(parent_array);
        free(component_size);
        return 0;
    }

    /* A more expensive token is always more important than all cheaper
       tokens together, so remove tokens greedily from largest to smallest. */
    for (i = k; i >= 1; i--) {
        chosen[i] = 0;
        if (!can_travel(n, m, roads, required, chosen)) {
            chosen[i] = 1;
        }
    }

    for (i = 1; i <= k; i++) {
        if (chosen[i]) {
            answer += cost[i];
        }
    }
    printf("%lld\n", answer);

    free(cost);
    free(chosen);
    free(required);
    free(roads);
    free(parent_array);
    free(component_size);
    return 0;
}

