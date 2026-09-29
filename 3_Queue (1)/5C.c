#include <stdio.h>
int main()
{
    int n;
    int queue[100];
    int i, j;
    int value;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &value);
        for (j = 0; j < i; j++)
            printf("%d ", queue[j]);
        printf("Enqueuing %d\n", value);
        queue[i] = value;
    }
    for (i = 0; i < n; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d", queue[i]);
    }
    printf("\n");
    return 0;
}

