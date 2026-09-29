#include <stdio.h>
#define MAX_VALUES 1000000
#define LIMIT 10000000000000LL
long long starts[MAX_VALUES];
int value_count;
long long integer_sqrt(long long value)
{
    long long low;
    long long high;
    long long middle;
    long long root;
    low = 0;
    high = value;
    root = 0;
    while (low <= high) {
        middle = (low + high) / 2;
        if (middle == 0 || middle <= value / middle) {
            root = middle;
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return root;
}
void build_starts(void)
{
    long long total;
    long long value;
    long long occurrences;
    total = 0;
    value_count = 0;
    value = 1;
    while (total < LIMIT && value_count < MAX_VALUES) {
        starts[value_count] = total + 1;
        occurrences = value * integer_sqrt(value) + (value + 1) / 2;
        total += occurrences;
        value_count++;
        value++;
    }
}
int count_starts_at_most(long long position)
{
    int low;
    int high;
    int middle;
    low = 0;
    high = value_count;
    while (low < high) {
        middle = (low + high) / 2;
        if (starts[middle] <= position)
            low = middle + 1;
        else
            high = middle;
    }
    return low;
}
int main(void)
{
    int q;
    int i;
    long long left;
    long long right;
    int left_value;
    int right_value;

    build_starts();
    scanf("%d", &q);
    for (i = 0; i < q; i++) {
        scanf("%lld %lld", &left, &right);
        left_value = count_starts_at_most(left);
        right_value = count_starts_at_most(right);
        printf("%d\n", right_value - left_value + 1);
    }
    return 0;
}

