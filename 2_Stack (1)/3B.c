#include <stdio.h>
#include <stdlib.h>
#define MAX_N 100005
#define MAX_SUM 82
int bit[MAX_SUM][MAX_N];
int digitSum(int number)
{
    int sum = 0;
    while (number > 0)
    {
        sum = sum + number % 10;
        number = number / 10;
    }
    return sum;
}
int compareNumbers(const void *x, const void *y)
{
    int a = *(const int *)x;
    int b = *(const int *)y;
    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}
int lowerBound(int a[], int n, int value)
{
    int left = 0;
    int right = n - 1;
    int answer = n;
    int middle;
    while (left <= right)
    {
        middle = (left + right) / 2;
        if (a[middle] >= value)
        {
            answer = middle;
            right = middle - 1;
        }
        else
        {
            left = middle + 1;
        }
    }
    return answer;
}
void update(int sum, int index, int position)
{
    while (index < MAX_N)
    {
        if (bit[sum][index] == 0 || position < bit[sum][index])
            bit[sum][index] = position;
        index = index + (index & -index);
    }
}
int query(int sum, int index)
{
    int answer = 0;
    while (index > 0)
    {
        if (bit[sum][index] != 0)
        {
            if (answer == 0 || bit[sum][index] < answer)
                answer = bit[sum][index];
        }
        index = index - (index & -index);
    }
    return answer;
}
int main()
{
    int n, q;
    int a[MAX_N];
    int copy[MAX_N];
    int answer[MAX_N];
    int uniqueCount;
    int i, j;
    int rank;
    int limit;
    int sum;
    int candidate;
    int best;
    int queryIndex;
    scanf("%d %d", &n, &q);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        copy[i] = a[i];
    }
    qsort(copy, n, sizeof(int), compareNumbers);
    uniqueCount = 0;
    for (i = 0; i < n; i++)
    {
        if (i == 0 || copy[i] != copy[i - 1])
        {
            copy[uniqueCount] = copy[i];
            uniqueCount++;
        }
    }
    for (i = n - 1; i >= 0; i--)
    {
        rank = lowerBound(copy, uniqueCount, a[i]) + 1;
        limit = uniqueCount - rank;
        sum = digitSum(a[i]);
        best = 0;
        for (j = 0; j < sum; j++)
        {
            candidate = query(j, limit);
            if (candidate != 0 && (best == 0 || candidate < best))
                best = candidate;
        }
        if (best == 0)
            answer[i] = -1;
        else
            answer[i] = best;
        update(sum, uniqueCount - rank + 1, i + 1);
    }
    for (i = 0; i < q; i++)
    {
        scanf("%d", &queryIndex);
        if (i > 0)
            printf(" ");
        printf("%d", answer[queryIndex - 1]);
    }
    printf("\n");
    return 0;
}
