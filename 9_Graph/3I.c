#include <stdio.h>
#include <stdlib.h>
struct FlowEdge {
    int to;
    int next;
    int capacity;
};

struct FlowEdge *flow_edges;
int *flow_head;
int *parent_edge;
int edge_count;
int *edge_from;
int *edge_to;
int *original_edge;
int *out_head;
int *out_next;
int *edge_used;
int *route_nodes;
int *route_edges;
int *route_visited;
int route_length;

void add_flow_edge(int u, int v)
{
    flow_edges[edge_count].to = v;
    flow_edges[edge_count].capacity = 1;
    flow_edges[edge_count].next = flow_head[u];
    flow_head[u] = edge_count;
    edge_count++;

    flow_edges[edge_count].to = u;
    flow_edges[edge_count].capacity = 0;
    flow_edges[edge_count].next = flow_head[v];
    flow_head[v] = edge_count;
    edge_count++;
}

int bfs(int n,int s,int t)
{
    int *queue;
    int front = 0;
    int back = 0;
    int i;
    int current;
    int e;

    queue = (int *)malloc((n + 1) * sizeof(int));
    for (i = 1; i <= n; i++) {
        parent_edge[i] = -1;
    }
    queue[back++] = s;
    parent_edge[s] = -2;

    while (front < back) {
        current = queue[front++];
        e = flow_head[current];
        while (e != -1) {
            if (flow_edges[e].capacity > 0 && parent_edge[flow_edges[e].to] == -1) {
                parent_edge[flow_edges[e].to] = e;
                queue[back++] = flow_edges[e].to;
                if (flow_edges[e].to == t) {
                    free(queue);
                    return 1;
                }
            }
            e = flow_edges[e].next;
        }
    }
    free(queue);
    return 0;
}

int find_route(int current, int target, int depth)
{
    int i;
    if (current == target) {
        route_nodes[depth] = current;
        route_length = depth + 1;
        return 1;
    }
    route_visited[current] = 1;
    route_nodes[depth] = current;

    i = out_head[current];
    while (i != -1) {
        if (edge_used[i] && !route_visited[edge_to[i]]) {
            route_edges[depth] = i;
            if (find_route(edge_to[i], target, depth + 1)) {
                return 1;
            }
        }
        i = out_next[i];
    }
    return 0;
}

int main(void)
{
    int n;
    int m;
    int i;
    int u;
    int v;
    int flow = 0;
    int current;
    int e;
    int d;

    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    flow_edges = (struct FlowEdge *)malloc((2 * m + 5) * sizeof(struct FlowEdge));
    flow_head = (int *)malloc((n + 1) * sizeof(int));
    parent_edge = (int *)malloc((n + 1) * sizeof(int));
    edge_from = (int *)malloc(m * sizeof(int));
    edge_to = (int *)malloc(m * sizeof(int));
    original_edge = (int *)malloc(m * sizeof(int));
    out_head = (int *)malloc((n + 1) * sizeof(int));
    out_next = (int *)malloc(m * sizeof(int));
    edge_used = (int *)malloc(m * sizeof(int));
    route_nodes = (int *)malloc((n + 1) * sizeof(int));
    route_edges = (int *)malloc((n + 1) * sizeof(int));
    route_visited = (int *)malloc((n + 1) * sizeof(int));

    for (i = 1; i <= n; i++) {
        flow_head[i] = -1;
        out_head[i] = -1;
    }
    edge_count = 0;

    for (i = 0; i < m; i++) {
        scanf("%d %d", &u, &v);
        edge_from[i] = u;
        edge_to[i] = v;
        out_next[i] = out_head[u];
        out_head[u] = i;
        original_edge[i] = edge_count;
        edge_used[i] = 0;
        add_flow_edge(u, v);
    }

    while (bfs(n, 1, n)) {
        current = n;
        while (current != 1) {
            e = parent_edge[current];
            flow_edges[e].capacity--;
            flow_edges[e ^ 1].capacity++;
            current = flow_edges[e ^ 1].to;
        }
        flow++;
    }

    for (i = 0; i < m; i++) {
        if (flow_edges[original_edge[i]].capacity == 0) {
            edge_used[i] = 1;
        }
    }

    printf("%d\n", flow);
    for (i = 0; i < flow; i++) {
        for (d = 1; d <= n; d++) {
            route_visited[d] = 0;
        }
        route_length = 0;
        if (!find_route(1, n, 0)) {
            break;
        }
        printf("%d\n", route_length);
        for (d = 0; d < route_length; d++) {
            if (d > 0) {
                printf(" ");
            }
            printf("%d", route_nodes[d]);
        }
        printf("\n");
        for (d = 0; d < route_length - 1; d++) {
            edge_used[route_edges[d]] = 0;
        }
    }

    free(flow_edges);
    free(flow_head);
    free(parent_edge);
    free(edge_from);
    free(edge_to);
    free(original_edge);
    free(out_head);
    free(out_next);
    free(edge_used);
    free(route_nodes);
    free(route_edges);
    free(route_visited);
    return 0;
}

