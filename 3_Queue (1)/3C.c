#include <stdio.h>
int main()
{
    int n;
    int queue[100];
    int i, j;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &queue[i]);
    printf("Dequeuing elements:\n");
    for (i = 1; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            if (j > i)
                printf(" ");
            printf("%d", queue[j]);
        }
        printf("\n");
    }
    return 0;
}

