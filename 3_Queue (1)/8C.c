#include <stdio.h>
int main()
{
    int n, cacheSize;
    int reference[100];
    int cache[100];
    int used = 0;
    int i, j, position;
    int page;
    scanf("%d %d", &n, &cacheSize);
    for (i = 0; i < n; i++)
        scanf("%d", &reference[i]);
    for (i = 0; i < n; i++)
    {
        page = reference[i];
        position = -1;
        for (j = 0; j < used; j++)
        {
            if (cache[j] == page)
            {
                position = j;
                break;
            }
        }
        if (position != -1)
        {
            for (j = position; j > 0; j--)
                cache[j] = cache[j - 1];
        }
        else
        {
            if (used < cacheSize)
                used++;
            for (j = used - 1; j > 0; j--)
                cache[j] = cache[j - 1];
        }
        cache[0] = page;
    }
    for (i = 0; i < used; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%d", cache[i]);
    }
    printf("\n");
    return 0;
}

