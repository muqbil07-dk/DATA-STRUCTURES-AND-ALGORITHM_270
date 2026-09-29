#include <stdio.h>
int main(void)
{
    int money, items;
    char name[10][100];
    int price[10];
    int order[10];
    int afford[10] = {0};
    int i, j, temp;
    int left;
    int bought;
    scanf("%d %d", &money, &items);
    for (i = 0; i < items; i++)
    {
        scanf("%s %d", name[i], &price[i]);
        order[i] = i;
    }
    for (i = 0; i < items - 1; i++)
    {
        for (j = i + 1; j < items; j++)
        {
            if (price[order[i]] > price[order[j]])
            {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    left = money;
    bought = 0;
    for (i = 0; i < items; i++)
    {
        j = order[i];
        if (price[j] <= left)
        {
            afford[j] = 1;
            left = left - price[j];
            bought++;
        }
    }
    for (i = 0; i < items; i++)
    {
        if (afford[i])
            printf("I can afford %s\n", name[i]);
        else
            printf("I can't afford %s\n", name[i]);
    }
    if (bought == 0)
        printf("I need more Dollar!\n");
    else
        printf("%d\n", left);

    return 0;
}

