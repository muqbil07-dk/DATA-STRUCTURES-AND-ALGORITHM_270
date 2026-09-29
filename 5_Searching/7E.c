#include <stdio.h>

int is_silver(long long width, long long height)
{
    long long larger;
    long long smaller;

    if (width > height) {
        larger = width;
        smaller = height;
    } else {
        larger = height;
        smaller = width;
    }

    return 10 * larger >= 16 * smaller &&
           10 * larger <= 17 * smaller;
}

int main(void)
{
    int n;
    int i;
    long long width;
    long long height;
    int answer;

    scanf("%d", &n);
    answer = 0;
    for (i = 0; i < n; i++) {
        scanf("%lld %lld", &width, &height);
        if (is_silver(width, height))
            answer++;
    }

    printf("%d\n", answer);
    return 0;
}

