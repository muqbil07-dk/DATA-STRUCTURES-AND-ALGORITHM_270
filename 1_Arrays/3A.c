#include <stdio.h>
int main(void)
{
    int testCases;
    int n, i;
    int price[100];
    int buy, sell;
    int first;
    scanf("%d", &testCases);
    while (testCases > 0)
    {
        scanf("%d", &n);
        for (i = 0; i < n; i++)
            scanf("%d", &price[i]);
        i = 0;
        first = 1;
        while (i < n - 1)
        {
            while (i < n - 1 && price[i] >= price[i + 1])
                i++;
            if (i == n - 1)
                break;
            buy = i;
            while (i < n - 1 && price[i] <= price[i + 1])
                i++;
            sell = i;
            if (!first)
                printf(" ");
            printf("(%d %d)", buy, sell);
            first = 0;
            i++;
        }
        if (first)
            printf("No Profit");
        printf("\n");
        testCases--;
    }
    return 0;
}
