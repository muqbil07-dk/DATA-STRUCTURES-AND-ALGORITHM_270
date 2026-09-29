#include <stdio.h>
#define MAXN 10000
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
    int girls[MAXN];
    int boys[MAXN];
    int i;
    long long answer;
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d", &n);
        for (i = 0; i < n; i++)
            scanf("%d", &girls[i]);
        for (i = 0; i < n; i++)
            scanf("%d", &boys[i]);
        sort_ascending(girls, n);
        sort_descending(boys, n);
        answer = 0;
        for (i = 0; i < n; i++) {
            if (girls[i] % boys[i] == 0 || boys[i] % girls[i] == 0)
                answer++;
        }
        printf("%lld\n", answer);
    }
    return 0;
}
