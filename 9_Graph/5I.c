#include <stdio.h>
#define MAXN 300005
#define MAXQ 500005
#define LOG 20
struct TreeEdge {
    int to;
    int weight;
    int next;
};
int n;
int q;
int query_u[MAXQ];
int query_v[MAXQ];
int query_x[MAXQ];
int accepted[MAXQ];
int dsu_parent[MAXN];
int dsu_size[MAXN];
int tree_head[MAXN];
struct TreeEdge tree_edges[2 * MAXN];
int tree_edge_count;

int parent_vertex[MAXN];
int tin[MAXN];
int tout[MAXN];
int xor_to_root[MAXN];
int up[LOG][MAXN];
int dfs_stack_vertex[MAXN];
int dfs_stack_edge[MAXN];
int timer_value;

int bit[MAXN + 5];

int dsu_find(int value)
{
    if (dsu_parent[value] != value) {
        dsu_parent[value] = dsu_find(dsu_parent[value]);
    }
    return dsu_parent[value];
}

int dsu_union(int a, int b)
{
    int temp;
    a = dsu_find(a);
    b = dsu_find(b);
    if (a == b) {
        return 0;
    }
    if (dsu_size[a] < dsu_size[b]) {
        temp = a;
        a = b;
        b = temp;
    }
    dsu_parent[b] = a;
    dsu_size[a] += dsu_size[b];
    return 1;
}

void add_tree_edge(int u, int v, int weight)
{
    tree_edges[tree_edge_count].to = v;
    tree_edges[tree_edge_count].weight = weight;
    tree_edges[tree_edge_count].next = tree_head[u];
    tree_head[u] = tree_edge_count;
    tree_edge_count++;
}

/* Iterative DFS, so a long tree does not overflow the C call stack. */
int dfs1(int np,int lst)
{
    int stack_size = 0;
    int v;
    int e;
    int child;
    int j;

    parent_vertex[np] = lst;
    tin[np] = timer_value;
    timer_value++;
    xor_to_root[np] = 0;
    for (j = 0; j < LOG; j++) {
        up[j][np] = np;
    }

    dfs_stack_vertex[stack_size] = np;
    dfs_stack_edge[stack_size] = tree_head[np];
    stack_size++;

    while (stack_size > 0) {
        v = dfs_stack_vertex[stack_size - 1];
        e = dfs_stack_edge[stack_size - 1];
        if (e == -1) {
            tout[v] = timer_value;
            stack_size--;
            continue;
        }

        dfs_stack_edge[stack_size - 1] = tree_edges[e].next;
        child = tree_edges[e].to;
        if (child == parent_vertex[v]) {
            continue;
        }

        parent_vertex[child] = v;
        tin[child] = timer_value;
        timer_value++;
        xor_to_root[child] = xor_to_root[v] ^ tree_edges[e].weight;
        up[0][child] = v;
        for (j = 1; j < LOG; j++) {
            up[j][child] = up[j - 1][up[j - 1][child]];
        }
        dfs_stack_vertex[stack_size] = child;
        dfs_stack_edge[stack_size] = tree_head[child];
        stack_size++;
    }
    return 0;
}

int is_ancestor(int a, int b)
{
    return tin[a] <= tin[b] && tout[b] <= tout[a];
}

int get_lca(int a, int b)
{
    int j;
    if (is_ancestor(a, b)) {
        return a;
    }
    if (is_ancestor(b, a)) {
        return b;
    }
    for (j = LOG - 1; j >= 0; j--) {
        if (!is_ancestor(up[j][a], b)) {
            a = up[j][a];
        }
    }
    return up[0][a];
}

void bit_add(int position, int value)
{
    int p = position + 1;
    while (p <= n + 1) {
        bit[p] += value;
        p += p & -p;
    }
}

int bit_sum(int position)
{
    int p = position + 1;
    int result = 0;
    while (p > 0) {
        result += bit[p];
        p -= p & -p;
    }
    return result;
}

void mark_path_to_ancestor(int v, int ancestor)
{
    while (v != ancestor) {
        bit_add(tin[v], 1);
        bit_add(tout[v], -1);
        v = parent_vertex[v];
    }
}

int main(void)
{
    int i;
    int j;
    int common;
    int used_on_path;
    int path_xor;

    if (scanf("%d %d", &n, &q) != 2) {
        return 0;
    }

    for (i = 1; i <= n; i++) {
        dsu_parent[i] = i;
        dsu_size[i] = 1;
        tree_head[i] = -1;
    }

    for (i = 0; i < q; i++) {
        scanf("%d %d %d", &query_u[i], &query_v[i], &query_x[i]);
        accepted[i] = 0;
        if (dsu_union(query_u[i], query_v[i])) {
            accepted[i] = 1;
            add_tree_edge(query_u[i], query_v[i], query_x[i]);
            add_tree_edge(query_v[i], query_u[i], query_x[i]);
        }
    }

    timer_value = 0;
    for (j = 0; j < LOG; j++) {
        for (i = 1; i <= n; i++) {
            up[j][i] = i;
        }
    }
    for (i = 1; i <= n; i++) {
        tin[i] = -1;
        tout[i] = -1;
    }
    for (i = 1; i <= n; i++) {
        if (tin[i] == -1) {
            dfs1(i, i);
        }
    }

    for (i = 0; i < q; i++) {
        if (accepted[i]) {
            continue;
        }
        path_xor = xor_to_root[query_u[i]] ^ xor_to_root[query_v[i]];
        if ((path_xor ^ query_x[i]) != 1) {
            continue;
        }
        common = get_lca(query_u[i], query_v[i]);
        used_on_path = bit_sum(tin[query_u[i]])
                     + bit_sum(tin[query_v[i]])
                     - 2 * bit_sum(tin[common]);
        if (used_on_path != 0) {
            continue;
        }
        accepted[i] = 1;
        mark_path_to_ancestor(query_u[i], common);
        mark_path_to_ancestor(query_v[i], common);
    }

    for (i = 0; i < q; i++) {
        if (accepted[i]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}

