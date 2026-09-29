#include <stdio.h>
#include <stdlib.h>
void swapInt(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int arr[],int n,int i)
{
    int largest, left, right;
    largest = i;
    left = 2 * i + 1;
    right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swapInt(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

int main(void)
{
    int m, n, i, heapSize;
    int *rows;
    long long answer;

    scanf("%d %d", &m, &n);

    rows = (int *)malloc((size_t)m * sizeof(int));

    for (i = 0; i < m; i++) {
        scanf("%d", &rows[i]);
    }

    /* Build a maximum heap */
    for (i = m / 2 - 1; i >= 0; i--) {
        heapify(rows, m, i);
    }

    heapSize = m;
    answer = 0;

    /* Sell tickets to n fans */
    for (i = 0; i < n; i++) {
        answer += rows[0];

        /* One seat is occupied in the most expensive row */
        rows[0]--;

        heapify(rows, heapSize, 0);
    }

    printf("%lld\n", answer);

    free(rows);

    return 0;
}
