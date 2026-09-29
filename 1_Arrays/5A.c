#include <stdio.h>
int main(void)
{
    char nums[100][20];
    char words[13][10] = {"ZERO", "ONE", "TWO", "THREE", "FOUR",
                           "FIVE", "SIX", "SEVEN", "EIGHT", "NINE",
                           "TEN", "ELEVEN", "TWELVE"};
    int count[26] = {0};
    int total = 0;
    int i, j, number;
    int first;
    char ch;
    while (total < 100 && scanf("%s", nums[total]) == 1)
    {
        number = 0;
        for (j = 0; nums[total][j] != '\0'; j++)
            number = number * 10 + nums[total][j] - '0';
        total++;
        if (number == 999)
            break;
        if (number >= 0 && number <= 12)
        {
            for (j = 0; words[number][j] != '\0'; j++)
            {
                ch = words[number][j];
                count[ch - 'A']++;
            }
        }
    }
    for (i = 0; i < total; i++)
    {
        if (i > 0)
            printf(" ");
        printf("%s", nums[i]);
    }
    printf(".");
    first = 1;
    for (i = 0; i < 26; i++)
    {
        for (j = 0; j < count[i]; j++)
        {
            if (first)
            {
                printf(" ");
                first = 0;
            }
            else
                printf(" ");
            printf("%c", 'A' + i);
        }
    }
    printf("\n");
    return 0;
}

