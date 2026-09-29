#include <stdio.h>
int main()
{
    int n;
    int i;
    long long x;
    long long biggest = -1;
    long long second = -1;
    long long third = -1;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%lld", &x);
        if (x >= biggest)
        {
            third = second;
            second = biggest;
            biggest = x;
        }
        else if (x >= second)
        {
            third = second;
            second = x;
        }
        else if (x > third)
        {
            third = x;
        }
        if (third == -1)
            printf("-1\n");
        else
            printf("%lld\n", biggest * second * third);
    }
    return 0;
}

