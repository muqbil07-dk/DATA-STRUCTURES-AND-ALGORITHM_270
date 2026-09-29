#include <stdio.h>
#include <stdlib.h>
long long *values;
int *inIncreasing;
int *inDecreasing;
int valueCount;
int compareLongLong(const void *first, const void *second)
{
    long long a, b;
    a = *(const long long *)first;
    b = *(const long long *)second;
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}
int findValue(long long value)
{
    int left, right, middle;
    left = 0;
    right = valueCount - 1;
    while (left <= right) {
        middle = (left + right) / 2;
        if (values[middle] == value) {
            return middle;
        }
        if (values[middle] < value) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}
int main(void)
{
    int n, q, i, j, peak, index, size, maxIndex;
    long long *initial;
    long long *operations;
    long long value;
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    initial = (long long *)malloc(
        (size_t)n * sizeof(long long));

    for (i = 0; i < n; i++) {
        scanf("%lld", &initial[i]);
    }

    scanf("%d", &q);

    operations = (long long *)malloc(
        (size_t)q * sizeof(long long));

    for (i = 0; i < q; i++) {
        scanf("%lld", &operations[i]);
    }

    values = (long long *)malloc(
        (size_t)(n + q) * sizeof(long long));

    valueCount = 0;

    for (i = 0; i < n; i++) {
        values[valueCount++] = initial[i];
    }

    for (i = 0; i < q; i++) {
        values[valueCount++] = operations[i];
    }

    qsort(values,
          (size_t)valueCount,
          sizeof(long long),
          compareLongLong);

    j = 0;

    for (i = 0; i < valueCount; i++) {
        if (j == 0 || values[i] != values[j - 1]) {
            values[j++] = values[i];
        }
    }

    valueCount = j;

    inIncreasing = (int *)calloc(
        (size_t)valueCount, sizeof(int));

    inDecreasing = (int *)calloc(
        (size_t)valueCount, sizeof(int));

    peak = 0;

    for (i = 1; i < n; i++) {
        if (initial[i] > initial[peak]) {
            peak = i;
        }
    }

    maxIndex = findValue(initial[peak]);

    for (i = 0; i <= peak; i++) {
        index = findValue(initial[i]);
        inIncreasing[index] = 1;
    }

    for (i = peak + 1; i < n; i++) {
        index = findValue(initial[i]);
        inDecreasing[index] = 1;
    }

    size = n;

    for(i=0;i<n;i++) {
    }

    for (i = 0; i < q; i++) {
        value = operations[i];
        index = findValue(value);

        if (index == maxIndex) {
            printf("%d\n", size);
            continue;
        }

        if (index > maxIndex) {
            inIncreasing[index] = 1;
            maxIndex = index;
            size++;
        } else if (!inIncreasing[index] &&
                   !inDecreasing[index]) {
            inIncreasing[index] = 1;
            size++;
        } else if (inIncreasing[index] &&
                   !inDecreasing[index]) {
            inDecreasing[index] = 1;
            size++;
        }

        printf("%d\n", size);
    }

    {
        int first;

        first = 1;

        for (i = 0; i < valueCount; i++) {
            if (inIncreasing[i]) {
                if (!first) {
                    printf(" ");
                }

                printf("%lld", values[i]);
                first = 0;
            }
        }

        for (i = valueCount - 1; i >= 0; i--) {
            if (inDecreasing[i]) {
                if (!first) {
                    printf(" ");
                }

                printf("%lld", values[i]);
                first = 0;
            }
        }

        printf("\n");
    }

    free(initial);
    free(operations);
    free(values);
    free(inIncreasing);
    free(inDecreasing);

    return 0;
}
