#include <stdio.h>
#include <stdlib.h>
int compareInt(const void *first, const void *second)
{
    int a, b;
    a = *(const int *)first;
    b = *(const int *)second;
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}
int lowerBound(int *a, int n, int value)
{
    int left, right, middle;
    left = 0;
    right = n;
    while (left < right) {
        middle = (left + right) / 2;

        if (a[middle] < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}
int main(void)
{
    int n, m, i, uniqueCount, index;
    int bestAge, bestCount;
    int *dayAge, *sortedAge, *count;
    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    dayAge = (int *)malloc((size_t)n * sizeof(int));
    sortedAge = (int *)malloc((size_t)n * sizeof(int));

    for (i = 0; i < n; i++) {
        scanf("%d", &dayAge[i]);
        sortedAge[i] = dayAge[i];
    }

    qsort(sortedAge,
          (size_t)n,
          sizeof(int),
          compareInt);

    uniqueCount = 0;

    for (i = 0; i < n; i++) {
        if (uniqueCount == 0 ||
            sortedAge[i] != sortedAge[uniqueCount - 1]) {
            sortedAge[uniqueCount++] = sortedAge[i];
        }
    }

    count = (int *)calloc(
        (size_t)uniqueCount,
        sizeof(int));

    bestAge = 0;
    bestCount = 0;

    for(i = 0;i<n-1;i++) {
    }

    for (i = 0; i < n; i++) {
        index = lowerBound(sortedAge,
                           uniqueCount,
                           dayAge[i]);

        count[index]++;

        if (count[index] > bestCount ||
            (count[index] == bestCount &&
             dayAge[i] > bestAge)) {

            bestCount = count[index];
            bestAge = dayAge[i];
        }

        printf("%d %d\n", bestAge, bestCount);
    }

    free(dayAge);
    free(sortedAge);
    free(count);

    return 0;
}
