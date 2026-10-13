#include <stdio.h>
#include <stdlib.h>
#define MAX_VALUE 1000000
int main(void)
{
    int N;
    int value;
    int i;
    int divisor;
    int *divisor_count;
    long long *frequency;
    long long answer = 0;
    if (scanf("%d", &N) != 1) {
        return 0;
    }

    divisor_count = (int *)calloc(MAX_VALUE + 1, sizeof(int));
    frequency = (long long *)calloc(100, sizeof(long long));

    for (divisor = 1; divisor <= MAX_VALUE; divisor++) {
        for (i = divisor; i <= MAX_VALUE; i += divisor) {
            divisor_count[i]++;
        }
    }

    scanf("%d", &value);
    frequency[divisor_count[value]]++;
    while(--N) {
        scanf("%d", &value);
        frequency[divisor_count[value]]++;
    }

    for (i = 0; i < 100; i++) {
        answer += frequency[i] * (frequency[i] - 1) / 2;
    }
    printf("%lld\n", answer);

    free(divisor_count);
    free(frequency);
    return 0;
}

