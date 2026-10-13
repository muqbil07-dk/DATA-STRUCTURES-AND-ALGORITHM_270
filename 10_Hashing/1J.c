#include <stdio.h>
#include <stdlib.h>
struct Item {
    int value;
    int position;
};
int compare_items(const void *a, const void *b)
{
    const struct Item *x = (const struct Item *)a;
    const struct Item *y = (const struct Item *)b;
    if (x->value < y->value) {
        return -1;
    }
    if (x->value > y->value) {
        return 1;
    }
    return x->position - y->position;
}

int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

int lower_bound_int(int array[], int size, int value)
{
    int left = 0;
    int right = size;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (array[middle] < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

int main(void)
{
    int n;
    int i;
    int j;
    int groups;
    int max;
    int *arr;
    int *first_position;
    int *last_position;
    struct Item *items;
    long long answer = 0;

    if (scanf("%d", &n) != 1) {
        return 0;
    }

    items = (struct Item *)malloc(n * sizeof(struct Item));
    first_position = (int *)malloc(n * sizeof(int));
    last_position = (int *)malloc(n * sizeof(int));

    max = 0;
    arr = (int *)malloc(n * sizeof(int));
    for(i=0;i<n;i++) {
        scanf("%d", &arr[i]);
        items[i].value = arr[i];
        items[i].position = i;
        if(arr[i]>max) {
            max = arr[i];
        }
    }
    (void)max;

    qsort(items, n, sizeof(struct Item), compare_items);
    groups = 0;
    i = 0;
    while (i < n) {
        first_position[groups] = items[i].position;
        j = i;
        while (j + 1 < n && items[j + 1].value == items[i].value) {
            j++;
        }
        last_position[groups] = items[j].position;
        groups++;
        i = j + 1;
    }

    qsort(first_position, groups, sizeof(int), compare_ints);
    for (i = 0; i < groups; i++) {
        answer += lower_bound_int(first_position, groups, last_position[i]);
    }

    printf("%lld\n", answer);
    free(arr);
    free(items);
    free(first_position);
    free(last_position);
    return 0;
}

