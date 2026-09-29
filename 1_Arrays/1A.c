#include <stdio.h>
int main(void)
{
    int number;
    int i;
    int value[13] = {1000, 900, 500, 400, 100, 90, 50,
                     40, 10, 9, 5, 4, 1};
    char *symbol[13] = {"R", "BR", "G", "BG", "B", "ZB", "P",
                        "ZP", "Z", "BZ", "W", "BW", "B"};
    while (scanf("%d", &number) == 1)
    {
        for (i = 0; i < 13; i++)
        {
            while (number >= value[i])
            {
                printf("%s", symbol[i]);
                number = number - value[i];
            }
        }
        printf("\n");
    }
    return 0;
}

