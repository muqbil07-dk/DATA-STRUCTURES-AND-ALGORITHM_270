#include <stdio.h>
int main()
{
    int n, m;
    int first[100000];
    int second[100000];
    int i;
    int firstOutput;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; i++)
        scanf("%d", &first[i]);
    for (i = 0; i < m; i++)
        scanf("%d", &second[i]);
    firstOutput = 1;
    for (i = n - 1; i >= 0; i--)
    {
        if (firstOutput == 0)
            printf(" ");
        printf("%d", first[i]);
        firstOutput = 0;
    }
    for (i = m - 1; i >= 0; i--)
    {
        if (firstOutput == 0)
            printf(" ");
        printf("%d", second[i]);
        firstOutput = 0;
    }
    printf("\n");
    return 0;
}

