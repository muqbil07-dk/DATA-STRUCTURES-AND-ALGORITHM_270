#include <stdio.h>
#define MAXN 100005
#define LOG 18

int up[LOG][MAXN];

void link(int i, int j) {
    up[0][i] = j;
}

int main(void) {
    int n;
    int q;
    int i;
    int j;
    int employee;
    int boss;
    int levels;

    scanf("%d %d", &n, &q);
    up[0][1] = 0;

    for (i = 2; i <= n; i++) {
        scanf("%d", &boss);
        link(i, boss);
    }

    for (j = 1; j < LOG; j++) {
        for (i = 1; i <= n; i++) {
            up[j][i] = up[j - 1][up[j - 1][i]];
        }
    }

    for (i = 0; i < q; i++) {
        scanf("%d %d", &employee, &levels);
        j = 0;

        while (levels > 0 && employee != 0) {
            if (levels % 2 == 1) {
                employee = up[j][employee];
            }
            levels = levels / 2;
            j++;
        }

        if (employee == 0) {
            printf("-1\n");
        } else {
            printf("%d\n", employee);
        }
    }

    return 0;
}

