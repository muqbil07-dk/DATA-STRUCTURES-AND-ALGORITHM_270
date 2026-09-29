#include <stdio.h>
#define MAXN 2005
struct flat_group {
    long long difference;
    long long people;
};
void sort_groups(struct flat_group a[], int n)
{
    int i;
    int j;
    struct flat_group temp;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i].difference > a[j].difference) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
int main(void)
{
    int t;
    int n;
    int i;
    int j;
    long long x;
    long long y;
    long long h;
    long long total;
    long long left;
    int group_count;
    struct flat_group groups[MAXN];
    int possible;
    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d", &n);
        group_count = 0;
        for (i = 0; i < n; i++) {
            scanf("%lld %lld %lld", &x, &y, &h);
            groups[group_count].difference = y - x;
            groups[group_count].people = h;
            group_count++;
        }
        sort_groups(groups, group_count);
        total = 0;
        for (i = 0; i < group_count; i++)
            total += groups[i].people;
        possible = 0;
        if (total % 2 == 0) {
            left = 0;
            i = 0;
            while (i < group_count) {
                j = i;
                while (j < group_count &&
                       groups[j].difference == groups[i].difference) {
                    left += groups[j].people;
                    j++;
                }
                if (left * 2 == total && j < group_count)
                    possible = 1;
                i = j;
            }
        }

        if (possible)
            printf("YES\n");
        else
            printf("NO\n");
    }
    return 0;
}

