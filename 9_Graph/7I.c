#include <stdio.h>
#include <stdlib.h>
int *parent_array;
int *component_size;
int find_set(int value)
{
    if (parent_array[value] != value) {
        parent_array[value] = find_set(parent_array[value]);
    }
    return parent_array[value];
}
int join(int i,int j)
{
    int root_i;
    int root_j;
    int temp;

    root_i = find_set(i);
    root_j = find_set(j);
    if (root_i == root_j) {
        return 0;
    }
    if (component_size[root_i] < component_size[root_j]) {
        temp = root_i;
        root_i = root_j;
        root_j = temp;
    }
    parent_array[root_j] = root_i;
    component_size[root_i] += component_size[root_j];
    return 1;
}

int main(void)
{
    int n;
    int m;
    int i;
    int a;
    int b;
    int components;
    int largest = 1;
    int root;

    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    parent_array = (int *)malloc((n + 1) * sizeof(int));
    component_size = (int *)malloc((n + 1) * sizeof(int));
    for (i = 1; i <= n; i++) {
        parent_array[i] = i;
        component_size[i] = 1;
    }
    components = n;

    for (i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        if (join(a, b)) {
            components--;
            root = find_set(a);
            if (component_size[root] > largest) {
                largest = component_size[root];
            }
        }
        printf("%d %d\n", components, largest);
    }

    free(parent_array);
    free(component_size);
    return 0;
}

