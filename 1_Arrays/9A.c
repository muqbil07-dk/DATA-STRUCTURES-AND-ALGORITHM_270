#include <stdio.h>
int matrix[1000][1000];
int rowHasOne[1000];
int columnHasOne[1000];
int main()
{
    int rows, columns;
    int i, j;
    scanf("%d %d", &rows, &columns);
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            scanf("%d", &matrix[i][j]);
            if (matrix[i][j] == 1)
            {
                rowHasOne[i] = 1;
                columnHasOne[j] = 1;
            }
        }
    }
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            if (rowHasOne[i] == 1 || columnHasOne[j] == 1)
            {
                matrix[i][j] = 1;
            }
        }
    }
    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < columns; j++)
        {
            if (j > 0)
            {
                printf(" ");
            }
            printf("%d", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}

