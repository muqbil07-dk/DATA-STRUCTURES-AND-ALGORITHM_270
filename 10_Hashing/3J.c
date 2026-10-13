#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Spending {
    char name[11];
    long long amount;
};
int compare_spending(const void *a, const void *b)
{
    const struct Spending *x = (const struct Spending *)a;
    const struct Spending *y = (const struct Spending *)b;
    return strcmp(x->name, y->name);
}
void add_to_top_three(long long top[], long long value)
{
    if (value >= top[0]) {
        top[2] = top[1];
        top[1] = top[0];
        top[0] = value;
    } else if (value >= top[1]) {
        top[2] = top[1];
        top[1] = value;
    } else if (value > top[2]) {
        top[2] = value;
    }
}

int main(void)
{
    int t;
    int n;
    int i;
    int j;
    int best_group;
    long long top[3];
    long long total;
    long long best_total;
    struct Spending *spending;
    char best_name[11];

    if (scanf("%d", &t) != 1) {
        return 0;
    }

    while(t--) {
        scanf("%d", &n);
        spending = (struct Spending *)malloc(n * sizeof(struct Spending));
        for (i = 0; i < n; i++) {
            scanf("%10s %lld", spending[i].name, &spending[i].amount);
        }
        qsort(spending, n, sizeof(struct Spending), compare_spending);

        best_total = -1;
        best_group = 0;
        i = 0;
        while (i < n) {
            j = i;
            top[0] = 0;
            top[1] = 0;
            top[2] = 0;
            while (j < n && strcmp(spending[i].name, spending[j].name) == 0) {
                add_to_top_three(top, spending[j].amount);
                j++;
            }
            total = top[0] + top[1] + top[2];
            if (total > best_total ||
                (total == best_total && strcmp(spending[i].name, spending[best_group].name) < 0)) {
                best_total = total;
                best_group = i;
                strcpy(best_name, spending[i].name);
            }
            i = j;
        }
        printf("%s %lld\n", best_name, best_total);
        free(spending);
    }
    return 0;
}

