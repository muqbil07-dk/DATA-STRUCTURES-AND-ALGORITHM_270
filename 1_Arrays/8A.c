#include <stdio.h>
int matrix[1000][1000];
int main()
{
    int testCases;
    int n, m;
    int x1, y1, x2, y2;
    int i, j;
    long long sum;
    scanf("%d", &testCases);
    while (testCases > 0)
    {
        scanf("%d %d", &n, &m);
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                scanf("%d", &matrix[i][j]);
            }
        }
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        sum = 0;
        for (i = x1 - 1; i <= x2 - 1; i++)
        {
            for (j = y1 - 1; j <= y2 - 1; j++)
            {
                sum = sum + matrix[i][j];
            }
        }
        printf("%lld\n", sum);
        testCases--;
    }
    return 0;
}

