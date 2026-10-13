#include <stdio.h>
#include <stdlib.h>
int *parent_array;
int *size_array;

int find_set(int value)
{
    if (parent_array[value] != value) {
        parent_array[value] = find_set(parent_array[value]);
    }
    return parent_array[value];
}

void unite(int a, int b)
{
    int temp;
    a = find_set(a);
    b = find_set(b);
    if (a == b) {
        return;
    }
    if (size_array[a] < size_array[b]) {
        temp = a;
        a = b;
        b = temp;
    }
    parent_array[b] = a;
    size_array[a] += size_array[b];
}

int main(void)
{
    int n;
    int m;
    int a;
    int b;
    int i;
    int component_count = 0;
    int representative_count = 0;
    int *representatives;

    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    parent_array = (int *)malloc((n + 1) * sizeof(int));
    size_array = (int *)malloc((n + 1) * sizeof(int));
    representatives = (int *)malloc((n + 1) * sizeof(int));

    for (i = 1; i <= n; i++) {
        parent_array[i] = i;
        size_array[i] = 1;
    }

    while(m--) {
        scanf("%d %d", &a, &b);
        unite(a, b);
    }

    for (i = 1; i <= n; i++) {
        if (find_set(i) == i) {
            representatives[representative_count] = i;
            representative_count++;
        }
    }
    component_count = representative_count;

    printf("%d\n", component_count - 1);
    for (i = 1; i < representative_count; i++) {
        printf("%d %d\n", representatives[0], representatives[i]);
    }

    free(parent_array);
    free(size_array);
    free(representatives);
    return 0;
}

