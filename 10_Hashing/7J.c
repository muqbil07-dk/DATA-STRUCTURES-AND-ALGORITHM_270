#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 2005
int NA[N];
int compare_long_long(const void *a, const void *b)
{
    long long x = *(const long long *)a;
    long long y = *(const long long *)b;
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

int main(void)
{
    int n;
    int i;
    int j;
    long long current;
    long long best;
    long long *values;
    int value_count = 0;
    long long answer = 0;

    if (scanf("%d", &n) != 1) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        scanf("%d", &NA[i]);
    }

    values = (long long *)malloc((long long)n * (n + 1) / 2 * sizeof(long long));
    for (i = 0; i < n; i++) {
        current = 0;
        best = LLONG_MIN;
        for (j = i; j < n; j++) {
            if (current < 0) {
                current = NA[j];
            } else {
                current += NA[j];
            }
            if (current > best) {
                best = current;
            }
            values[value_count] = best;
            value_count++;
        }
    }

    qsort(values, value_count, sizeof(long long), compare_long_long);
    for (i = 0; i < value_count; i++) {
        if (i == 0 || values[i] != values[i - 1]) {
            answer += values[i];
        }
    }
    printf("%lld\n", answer);
    free(values);
    return 0;
}

