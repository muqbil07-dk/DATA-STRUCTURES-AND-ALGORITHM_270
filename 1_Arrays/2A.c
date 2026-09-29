#include <stdio.h>
int main(void)
{
    int rows, columns;
    int i, j;
    int layer;
    char ch;
    scanf("%d %d", &rows, &columns);
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            layer = i;
            if (j < layer)
                layer = j;
            if (rows - 1 - i < layer)
                layer = rows - 1 - i;
            if (columns - 1 - j < layer)
                layer = columns - 1 - j;

            if (layer % 2 == 0)
                ch = 'Y';
            else
                ch = '0';
            printf("%c", ch);
            if (j < columns - 1)
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}

