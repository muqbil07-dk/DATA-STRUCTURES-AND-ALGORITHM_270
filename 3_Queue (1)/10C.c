#include <stdio.h>
int main()
{
    int n;
    int queue[100];
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &queue[i]);
    printf("Queue:");
    for (i = 0; i < n; i++)
        printf("%d%s", queue[i], i == n - 1 ? "" : " ");
    printf("\n");
    printf("Reversed Queue:");
    for (i = n - 1; i >= 0; i--)
        printf("%d%s", queue[i], i == 0 ? "" : " ");
    printf("\n");
    return 0;
}
