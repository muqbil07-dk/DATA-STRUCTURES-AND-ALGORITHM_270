#include <stdio.h>
#define MAXN 50
void sort_ascending(int a[], int n)
{
    int i;
    int j;
    int temp;
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
void sort_descending(int a[], int n)
{
    int i;
    int j;
    int temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i] < a[j]) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
int main(void)
{
    int t;
    int n;
    int a[MAXN];
    int b[MAXN];
    int i;
    long long answer;

    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d", &n);
        for (i = 0; i < n; i++)
            scanf("%d", &a[i]);
        for (i = 0; i < n; i++)
            scanf("%d", &b[i]);

        sort_ascending(a, n);
        sort_descending(b, n);
        answer = 0;
        for (i = 0; i < n; i++)
            answer += (long long)a[i] * b[i];
        printf("%lld\n", answer);
    }
    return 0;
}

