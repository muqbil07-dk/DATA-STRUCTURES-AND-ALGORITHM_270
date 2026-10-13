#include <stdio.h>
#include <stdlib.h>
int boy_count;
int girl_count;
int pair_count;
int *head_boy;
int *edge_girl;
int *edge_next;
int *pair_boy;
int *pair_girl;
int *distance_array;
void link(int u,int v)
{
    edge_girl[pair_count] = v;
    edge_next[pair_count] = head_boy[u];
    head_boy[u] = pair_count;
    pair_count++;
}

int bfs(int n)
{
    int *queue;
    int front = 0;
    int back = 0;
    int u;
    int v;
    int e;
    int found = 0;

    queue = (int *)malloc((n + 1) * sizeof(int));
    for (u = 1; u <= n; u++) {
        if (pair_boy[u] == 0) {
            distance_array[u] = 0;
            queue[back++] = u;
        } else {
            distance_array[u] = -1;
        }
    }

    while (front < back) {
        u = queue[front++];
        e = head_boy[u];
        while (e != -1) {
            v = edge_girl[e];
            if (pair_girl[v] == 0) {
                found = 1;
            } else if (distance_array[pair_girl[v]] == -1) {
                distance_array[pair_girl[v]] = distance_array[u] + 1;
                queue[back++] = pair_girl[v];
            }
            e = edge_next[e];
        }
    }
    free(queue);
    return found;
}

int augment(int u)
{
    int e;
    int v;
    int other_boy;

    e = head_boy[u];
    while (e != -1) {
        v = edge_girl[e];
        other_boy = pair_girl[v];
        if (other_boy == 0 ||
            (distance_array[other_boy] == distance_array[u] + 1 && augment(other_boy))) {
            pair_boy[u] = v;
            pair_girl[v] = u;
            return 1;
        }
        e = edge_next[e];
    }
    distance_array[u] = -1;
    return 0;
}

int main(void)
{
    int n;
    int m;
    int k;
    int i;
    int a;
    int b;
    int matching = 0;

    if (scanf("%d %d %d", &n, &m, &k) != 3) {
        return 0;
    }
    boy_count = n;
    girl_count = m;

    head_boy = (int *)malloc((n + 1) * sizeof(int));
    edge_girl = (int *)malloc(k * sizeof(int));
    edge_next = (int *)malloc(k * sizeof(int));
    pair_boy = (int *)calloc(n + 1, sizeof(int));
    pair_girl = (int *)calloc(m + 1, sizeof(int));
    distance_array = (int *)malloc((n + 1) * sizeof(int));

    for (i = 1; i <= n; i++) {
        head_boy[i] = -1;
    }
    pair_count = 0;
    for (i = 0; i < k; i++) {
        scanf("%d %d", &a, &b);
        link(a, b);
    }

    while (bfs(n)) {
        for (i = 1; i <= n; i++) {
            if (pair_boy[i] == 0 && augment(i)) {
                matching++;
            }
        }
    }

    printf("%d\n", matching);
    for (i = 1; i <= n; i++) {
        if (pair_boy[i] != 0) {
            printf("%d %d\n", i, pair_boy[i]);
        }
    }

    free(head_boy);
    free(edge_girl);
    free(edge_next);
    free(pair_boy);
    free(pair_girl);
    free(distance_array);
    return 0;
}

