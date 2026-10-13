#include <stdio.h>
#include <stdlib.h>
int *head_graph;
int *head_reverse;
int *to_graph;
int *next_graph;
int *to_reverse;
int *next_reverse;
int edge_count;

void link(int i,int j)
{
    to_graph[edge_count] = j;
    next_graph[edge_count] = head_graph[i];
    head_graph[i] = edge_count;

    to_reverse[edge_count] = i;
    next_reverse[edge_count] = head_reverse[j];
    head_reverse[j] = edge_count;
    edge_count++;
}

int main(void)
{
    int n;
    int m;
    int vertices;
    int i;
    int j;
    int a;
    int b;
    int node;
    int literal_a;
    int literal_b;
    int *visited;
    int *component;
    int *order;
    int *stack;
    int *edge_iterator;
    int order_count = 0;
    int component_count = 0;
    char sign_a;
    char sign_b;

    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    vertices = 2 * m;
    head_graph = (int *)malloc(vertices * sizeof(int));
    head_reverse = (int *)malloc(vertices * sizeof(int));
    to_graph = (int *)malloc((2 * n) * sizeof(int));
    next_graph = (int *)malloc((2 * n) * sizeof(int));
    to_reverse = (int *)malloc((2 * n) * sizeof(int));
    next_reverse = (int *)malloc((2 * n) * sizeof(int));
    visited = (int *)calloc(vertices, sizeof(int));
    component = (int *)malloc(vertices * sizeof(int));
    order = (int *)malloc(vertices * sizeof(int));
    stack = (int *)malloc(vertices * sizeof(int));
    edge_iterator = (int *)malloc(vertices * sizeof(int));

    for (i = 0; i < vertices; i++) {
        head_graph[i] = -1;
        head_reverse[i] = -1;
        component[i] = -1;
    }
    edge_count = 0;

    for (i = 0; i < n; i++) {
        scanf(" %c %d %c %d", &sign_a, &a, &sign_b, &b);
        literal_a = 2 * (a - 1);
        literal_b = 2 * (b - 1);
        if (sign_a == '-') {
            literal_a++;
        }
        if (sign_b == '-') {
            literal_b++;
        }

        link(literal_a ^ 1, literal_b);
        link(literal_b ^ 1, literal_a);
    }

    /* First Kosaraju pass: store vertices by finishing time. */
    for (i = 0; i < vertices; i++) {
        if (visited[i]) {
            continue;
        }
        visited[i] = 1;
        stack[0] = i;
        edge_iterator[0] = head_graph[i];
        j = 1;
        while (j > 0) {
            node = stack[j - 1];
            if (edge_iterator[j - 1] != -1) {
                int e = edge_iterator[j - 1];
                edge_iterator[j - 1] = next_graph[e];
                if (!visited[to_graph[e]]) {
                    visited[to_graph[e]] = 1;
                    stack[j] = to_graph[e];
                    edge_iterator[j] = head_graph[to_graph[e]];
                    j++;
                }
            } else {
                order[order_count] = node;
                order_count++;
                j--;
            }
        }
    }

    /* Second pass on the reverse graph. */
    for (i = order_count - 1; i >= 0; i--) {
        node = order[i];
        if (component[node] != -1) {
            continue;
        }
        component[node] = component_count;
        stack[0] = node;
        j = 1;
        while (j > 0) {
            int current = stack[--j];
            int e = head_reverse[current];
            while (e != -1) {
                int next_node = to_reverse[e];
                if (component[next_node] == -1) {
                    component[next_node] = component_count;
                    stack[j] = next_node;
                    j++;
                }
                e = next_reverse[e];
            }
        }
        component_count++;
    }

    for (i = 0; i < m; i++) {
        if (component[2 * i] == component[2 * i + 1]) {
            printf("IMPOSSIBLE\n");
            free(head_graph);
            free(head_reverse);
            free(to_graph);
            free(next_graph);
            free(to_reverse);
            free(next_reverse);
            free(visited);
            free(component);
            free(order);
            free(stack);
            free(edge_iterator);
            return 0;
        }
    }

    for (i = 0; i < m; i++) {
        /* Component numbers are created in reverse topological order. */
        if (component[2 * i] > component[2 * i + 1]) {
            printf("+ ");
        } else {
            printf("- ");
        }
    }
    printf("\n");

    free(head_graph);
    free(head_reverse);
    free(to_graph);
    free(next_graph);
    free(to_reverse);
    free(next_reverse);
    free(visited);
    free(component);
    free(order);
    free(stack);
    free(edge_iterator);
    return 0;
}

