#include <stdio.h>
#define MAXN 2005

struct interval {
    int left;
    int right;
};

void sort_intervals(struct interval a[], int n)
{
    int i;
    int j;
    struct interval temp;

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (a[i].left > a[j].left ||
                (a[i].left == a[j].left && a[i].right > a[j].right)) {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}

int can_make_length(struct interval a[], int n, int length)
{
    int start_index;
    int j;
    int start;
    int target;
    int reach;

    for (start_index = 0; start_index < n; start_index++) {
        start = a[start_index].left;
        target = start + length;
        reach = a[start_index].right;

        if (reach > target)
            continue;

        for (j = 0; j < n; j++) {
            if (a[j].left < start)
                continue;
            if (a[j].left > reach)
                break;
            if (a[j].right <= target && a[j].right > reach)
                reach = a[j].right;
        }

        if (reach == target)
            return 1;
    }
    return 0;
}

int main(void)
{
    int t;
    int n;
    int length;
    int i;
    struct interval streets[MAXN];

    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d %d", &n, &length);
        for (i = 0; i < n; i++)
            scanf("%d %d", &streets[i].left, &streets[i].right);

        sort_intervals(streets, n);
        if (can_make_length(streets, n, length))
            printf("Yes\n");
        else
            printf("No\n");
    }
    return 0;
}

