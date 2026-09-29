#include <stdio.h>

int main(void)
{
    int t;
    int n;
    int window;
    int i;
    int current;
    int best;
    char beauty[105];

    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d", &n);
        scanf("%104s", beauty);

        window = (n + 1) / 2;
        current = 0;
        for (i = 0; i < window; i++)
            current += beauty[i] - '0';
        best = current;

        for (i = window; i < n; i++) {
            current += beauty[i] - '0';
            current -= beauty[i - window] - '0';
            if (current > best)
                best = current;
        }
        printf("%d\n", best);
    }
    return 0;
}

