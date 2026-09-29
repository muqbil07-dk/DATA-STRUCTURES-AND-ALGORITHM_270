#include <stdio.h>
int main()
{
    int n;
    int price[1000];
    int span[1000];
    int stack[1000];
    int top = -1;
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &price[i]);
    for (i = 0; i < n; i++)
    {
        while (top >= 0 && price[stack[top]] <= price[i])
            top--;
        if (top == -1)
            span[i] = i + 1;
        else
            span[i] = i - stack[top];
        top++;
        stack[top] = i;
    }
    for (i = 0; i < n; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d", span[i]);
    }
    printf("\n");
    return 0;
}




