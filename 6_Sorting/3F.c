#include <stdio.h>
#define MAXN 100
void sort_long_long(long long a[], int n)
{
    int i;
    int j;
    long long temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
int main(void)
{
    int q;
    int n;
    int m;
    int i;
    int j;
    long long value;
    long long row_sum[MAXN];
    long long column_sum[MAXN];
    int possible;
    scanf("%d", &q);
    while (q-- > 0) {
        scanf("%d", &n);
        m = n;
        for (i = 0; i < n; i++)
            row_sum[i] = 0;
        for (j = 0; j < m; j++)
            column_sum[j] = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                scanf("%lld", &value);
                row_sum[i] += value;
                column_sum[j] += value;
            }
        }
        sort_long_long(row_sum, n);
        sort_long_long(column_sum, m);
        possible = 1;
        if (n != m)
            possible = 0;
        else {
            for (i = 0; i < n; i++) {
                if (row_sum[i] != column_sum[i])
                    possible = 0;
            }
        }
        if (possible)
            printf("Possible\n");
        else
            printf("Impossible\n");
    }
    return 0;
}

