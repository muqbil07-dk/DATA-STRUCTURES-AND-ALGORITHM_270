#include <stdio.h>

int main(void)
{
    int t;
    int n;
    int i;
    long long d;
    long long answer;
    long long x[1000];

    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d %lld", &n, &d);
        for (i = 0; i < n; i++)
            scanf("%lld", &x[i]);

        answer = d;
        for (i = n - 1; i >= 0; i--)
            answer = (answer / x[i]) * x[i];

        printf("%lld\n", answer);
    }
    return 0;
}

