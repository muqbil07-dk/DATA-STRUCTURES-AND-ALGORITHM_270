#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    int q;
    int i;
    int j;
    int x1;
    int y1;
    int x2;
    int y2;
    int size;
    int *prefix;
    char row[1005];
    int value;

    scanf("%d %d", &n, &q);
    size = n + 1;
    prefix = (int *)calloc(size * size, sizeof(int));

    for (i = 1; i <= n; i++) {
        scanf("%s", row);
        for (j = 1; j <= n; j++) {
            value = (row[j - 1] == '*') ? 1 : 0;
            prefix[i * size + j] = value
                + prefix[(i - 1) * size + j]
                + prefix[i * size + (j - 1)]
                - prefix[(i - 1) * size + (j - 1)];
        }
    }

    for (i = 0; i < q; i++) {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        value = prefix[x2 * size + y2]
            - prefix[(x1 - 1) * size + y2]
            - prefix[x2 * size + (y1 - 1)]
            + prefix[(x1 - 1) * size + (y1 - 1)];
        printf("%d\n", value);
    }

    free(prefix);
    return 0;
}

