#include <stdio.h>
int a[1000000];
int main()
{
    int n;
    int i;
    int left;
    int right;
    int first;
    int result;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    left = 0;
    right = n - 1;
    first = 1;
    while (left < n && right >= 0)
    {
        if (a[left] > a[right])
        {
            result = 1;
            right--;
        }
        else if (a[left] < a[right])
        {
            result = 2;
            left++;
        }
        else
        {
            result = 0;
            left++;
            right--;
        }
        if (first == 0)
        {
            printf(" ");
        }
        printf("%d", result);
        first = 0;
    }
    printf("\n");
    return 0;
}

