#include <stdio.h>
#include <stdlib.h>
void addFenwick(int *fenwick, int n, int index, int amount) {
    while (index <= n) {
        fenwick[index] += amount;
        index += index & -index;
    }
}
int findKth(int *fenwick, int n, int position) {
    int step;
    int index;
    int value;
    step = 1;
    while (step * 2 <= n) {
        step = step * 2;
    }
    index = 0;
    value = 0;
    while (step > 0) {
        if (index + step <= n && value + fenwick[index + step] < position) {
            index += step;
            value += fenwick[index];
        }
        step = step / 2;
    }
    return index + 1;
}

int main(void) {
    int n;
    int i;
    int position;
    int index;
    int *values;
    int *fenwick;
    scanf("%d", &n);
    values = (int *)malloc((n + 1) * sizeof(int));
    fenwick = (int *)calloc(n + 1, sizeof(int));
    for (i = 1; i <= n; i++) {
        scanf("%d", &values[i]);
        addFenwick(fenwick, n, i, 1);
    }

    for (i = 0; i < n; i++) {
        scanf("%d", &position);
        index = findKth(fenwick, n, position);
        if (i > 0) {
            printf(" ");
        }
        printf("%d", values[index]);
        addFenwick(fenwick, n, index, -1);
    }
    printf("\n");

    free(values);
    free(fenwick);
    return 0;
}

