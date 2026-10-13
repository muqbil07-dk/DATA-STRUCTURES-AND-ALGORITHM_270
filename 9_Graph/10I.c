#include <stdio.h>

#define MAXN 505
#define MAXM 1005

int capacity[MAXN][MAXN];
int adjacency[MAXN][MAXN];
int degree_array[MAXN];
int previous_vertex[MAXN];
int visited[MAXN];
int queue_array[MAXN];
int edge_u[MAXM];
int edge_v[MAXM];
int n;
int m;

void link(int i,int h)
{
    adjacency[i][degree_array[i]] = h;
    degree_array[i]++;
}

int bfs(int n)
{
    int front = 0;
    int back = 0;
    int current;
    int i;
    int next_vertex;

    for (i = 1; i <= n; i++) {
        previous_vertex[i] = -1;
        visited[i] = 0;
    }
    queue_array[back++] = 1;
    visited[1] = 1;
    previous_vertex[1] = 0;

    while (front < back) {
        current = queue_array[front++];
        for (i = 0; i < degree_array[current]; i++) {
            next_vertex = adjacency[current][i];
            if (capacity[current][next_vertex] > 0 && !visited[next_vertex]) {
                visited[next_vertex] = 1;
                previous_vertex[next_vertex] = current;
                queue_array[back++] = next_vertex;
                if (next_vertex == n) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int main(void)
{
    int i;
    int a;
    int b;
    int current;
    int flow = 0;
    int cut_count = 0;

    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    for (i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        edge_u[i] = a;
        edge_v[i] = b;
        capacity[a][b]++;
        capacity[b][a]++;
        link(a, b);
        link(b, a);
    }

    while (bfs(n)) {
        current = n;
        while (current != 1) {
            a = previous_vertex[current];
            capacity[a][current]--;
            capacity[current][a]++;
            current = a;
        }
        flow++;
    }

    /* The last BFS leaves visited[] equal to the source side of the cut. */
    for (i = 0; i < m; i++) {
        if (visited[edge_u[i]] != visited[edge_v[i]]) {
            cut_count++;
        }
    }

    printf("%d\n", cut_count);
    for (i = 0; i < m; i++) {
        if (visited[edge_u[i]] != visited[edge_v[i]]) {
            printf("%d %d\n", edge_u[i], edge_v[i]);
        }
    }
    (void)flow;
    return 0;
}

