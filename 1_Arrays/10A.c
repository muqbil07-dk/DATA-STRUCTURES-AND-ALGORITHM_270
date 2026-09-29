#include <stdio.h>
int main()
{
    int t;
    int n;
    int size[100];
    int sorted[100];
    int i, j, temp;
    int rank;
    int answer;
    scanf("%d", &t);
    while (t > 0)
    {
        scanf("%d", &n);
        for (i = 0; i < n; i++)
        {
            scanf("%d", &size[i]);
            sorted[i] = size[i];
        }
        for (i = 0; i < n - 1; i++)
        {
            for (j = i + 1; j < n; j++)
            {
                if (sorted[i] > sorted[j])
                {
                    temp = sorted[i];
                    sorted[i] = sorted[j];
                    sorted[j] = temp;
                }
            }
        }
        answer = 0;
        for (i = 0; i < n; i++)
        {
            rank = 1;
            for (j = 0; j < n; j++)
            {
                if (sorted[j] < size[i])
                {
                    if (j == 0 || sorted[j] != sorted[j - 1])
                    {
                        rank++;
                    }
                }
            }
            answer = answer + rank;
        }
        printf("%d\n", answer);
        t--;
    }
    return 0;
}

