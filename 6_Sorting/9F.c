#include <stdio.h>
#define MAXP 1505
#define NEGATIVE -1000000000000000000LL
int main(void)
{
    int t;
    int n;
    int k;
    int p;
    int i;
    int j;
    int take;
    int value;
    long long prefix[35];
    long long dp[MAXP];
    long long next_dp[MAXP];
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d %d %d", &n, &k, &p);
        for (i = 0; i <= p; i++)
            dp[i] = NEGATIVE;
        dp[0] = 0;
        for (i = 0; i < n; i++) {
            prefix[0] = 0;
            for (j = 1; j <= k; j++) {
                scanf("%d", &value);
                prefix[j] = prefix[j - 1] + value;
            }

            for (j = 0; j <= p; j++)
                next_dp[j] = NEGATIVE;

            for (j = 0; j <= p; j++) {
                if (dp[j] == NEGATIVE)
                    continue;
                for (take = 0; take <= k && j + take <= p; take++) {
                    if (dp[j] + prefix[take] > next_dp[j + take])
                        next_dp[j + take] = dp[j] + prefix[take];
                }
            }
            for (j = 0; j <= p; j++)
                dp[j] = next_dp[j];
        }
        printf("%lld\n", dp[p]);
    }
    return 0;
}

