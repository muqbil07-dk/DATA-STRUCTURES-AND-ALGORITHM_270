#include <stdio.h>
#define MAXN 100000

int main(void)
{
    int t;
    int n;
    int k;
    int a[MAXN];
    int i;
    int maximum;
    int answer;

    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d %d", &n, &k);
        maximum = 0;
        for (i = 0; i < n; i++) {
            scanf("%d", &a[i]);
            if (a[i] > maximum)
                maximum = a[i];
        }

        answer = maximum - k;
        if (answer <= 0)
            printf("-1\n");
        else
            printf("%d\n", answer);
    }
    return 0;
}

