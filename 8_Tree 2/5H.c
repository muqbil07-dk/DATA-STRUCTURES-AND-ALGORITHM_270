#include <stdio.h>
#include <stdlib.h>
int heap[200005];
int heapSize;
void swapInt(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void pushHeap(int value)
{
    int i, parent;
    i = heapSize++;
    heap[i] = value;
    while (i > 0) {
        parent = (i - 1) / 2;
        if (heap[parent] <= heap[i]) {
            break;
        }
        swapInt(&heap[parent], &heap[i]);
        i = parent;
    }
}
int popHeap(void)
{
    int result, i, left, right, smallest;
    result = heap[0];
    heapSize--;
    heap[0] = heap[heapSize];
    i = 0;
    while (1) {
        left = i * 2 + 1;
        right = left + 1;
        smallest = i;
        if (left < heapSize &&
            heap[left] < heap[smallest]) {
            smallest = left;
        }
        if (right < heapSize &&
            heap[right] < heap[smallest]) {
            smallest = right;
        }
        if (smallest == i) {
            break;
        }
        swapInt(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return result;
}

int printheap(int N)
{
    (void)N;

    if (heapSize == 0) {
        return -1;
    }

    return heap[0];
}

int main(void)
{
    int n, i, value, leaf, other;
    int *degree, *code;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    code = (int *)malloc((size_t)(n - 2) * sizeof(int));
    degree = (int *)malloc((size_t)(n + 1) * sizeof(int));

    for (i = 1; i <= n; i++) {
        degree[i] = 1;
    }

    for (i = 0; i < n - 2; i++) {
        scanf("%d", &code[i]);
        degree[code[i]]++;
    }

    heapSize = 0;

    for (i = 1; i <= n; i++) {
        if (degree[i] == 1) {
            pushHeap(i);
        }
    }

    for (i = 0; i < n - 2; i++) {
        value = code[i];
        leaf = popHeap();

        printf("%d %d\n", leaf, value);

        degree[value]--;

        if (degree[value] == 1) {
            pushHeap(value);
        }
    }

    leaf = popHeap();
    other = popHeap();

    printf("%d %d\n", leaf, other);

    free(code);
    free(degree);

    return 0;
}
