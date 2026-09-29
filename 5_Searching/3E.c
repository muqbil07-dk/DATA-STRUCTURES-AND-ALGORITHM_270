#include <stdio.h>

#define MAX 309

int A[MAX][MAX];

int main(void)
{
    int t;
    int r;
    int c;
    int limit;
    int i;
    int j;
    int left;
    int right;
    int width;
    int best;
    int row_min[MAX];
    int row_max[MAX];
    int run;

    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d %d %d", &r, &c, &limit);
        for (i = 0; i < r; i++) {
            for (j = 0; j < c; j++)
                scanf("%d", &A[i][j]);
        }

        best = 0;
        for (left = 0; left < c; left++) {
            for (i = 0; i < r; i++) {
                row_min[i] = A[i][left];
                row_max[i] = A[i][left];
            }

            for (right = left; right < c; right++) {
                width = right - left + 1;
                run = 0;
                for (i = 0; i < r; i++) {
                    if (A[i][right] < row_min[i])
                        row_min[i] = A[i][right];
                    if (A[i][right] > row_max[i])
                        row_max[i] = A[i][right];

                    if (row_max[i] - row_min[i] <= limit)
                        run++;
                    else
                        run = 0;

                    if (run * width > best)
                        best = run * width;
                }
            }
        }
        printf("%d\n", best);
    }
    return 0;
}

