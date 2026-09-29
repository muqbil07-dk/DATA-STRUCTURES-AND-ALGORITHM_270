#include <stdio.h>
int main()
{
    int n;
    long long a[3000];
    int nextGreater[3000];
    int nextSmaller[3000];
    int stack[3000];
    int top;
    int i;
    int f, g;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    top = -1;
    for (i = n - 1; i >= 0; i--)
    {
        while (top >= 0 && a[stack[top]] <= a[i])
            top--;
        if (top == -1)
            nextGreater[i] = -1;
        else
            nextGreater[i] = stack[top];
        top++;
        stack[top] = i;
    }
    top = -1;
    for (i = n - 1; i >= 0; i--)
    {
        while (top >= 0 && a[stack[top]] >= a[i])
            top--;
        if (top == -1)
            nextSmaller[i] = -1;
        else
            nextSmaller[i] = stack[top];
        top++;
        stack[top] = i;
    }
    for (i = 0; i < n; i++)
    {
        f = nextGreater[i];
        if (f == -1)
        {
            printf("-1");
        }
        else
        {
            g = nextSmaller[f];
            if (g == -1)
                printf("-1");
            else
                printf("%lld", a[g]);
        }
        if (i < n - 1)
            printf(" ");
    }
    printf("\n");
    return 0;
}

