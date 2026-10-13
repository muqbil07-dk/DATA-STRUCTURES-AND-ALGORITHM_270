#include <stdio.h>
#include <stdlib.h>
struct Query {
    int type;
    int value;
};
int *positions;
int position_count;
int *tree;
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

int lower_bound_position(int value)
{
    int left = 0;
    int right = position_count;
    int middle;
    while (left < right) {
        middle = left + (right - left) / 2;
        if (positions[middle] < value) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

void set_position(int node, int left, int right, int position)
{
    int middle;
    if (left == right) {
        tree[node] = 1;
        return;
    }
    middle = (left + right) / 2;
    if (position <= middle) {
        set_position(node * 2, left, middle, position);
    } else {
        set_position(node * 2 + 1, middle + 1, right, position);
    }
    tree[node] = tree[node * 2] || tree[node * 2 + 1];
}

int first_set_position(int node, int left, int right, int wanted)
{
    int middle;
    int answer;
    if (right < wanted || tree[node] == 0) {
        return -1;
    }
    if (left == right) {
        return left;
    }
    middle = (left + right) / 2;
    answer = first_set_position(node * 2, left, middle, wanted);
    if (answer == -1) {
        answer = first_set_position(node * 2 + 1, middle + 1, right, wanted);
    }
    return answer;
}

int main(void)
{
    int n;
    int q;
    int i;
    int type;
    int value;
    int index;
    int unique_count;
    int *all_positions;
    struct Query *queries;

    if (scanf("%d %d", &n, &q) != 2) {
        return 0;
    }
    (void)n;

    queries = (struct Query *)malloc(q * sizeof(struct Query));
    all_positions = (int *)malloc(q * sizeof(int));
    position_count = 0;

    for(i=0;i<q;i++) {
        scanf("%d %d", &type, &value);
        queries[i].type = type;
        queries[i].value = value;
        if (type == 1) {
            all_positions[position_count] = value;
            position_count++;
        }
    }

    qsort(all_positions, position_count, sizeof(int), compare_ints);
    unique_count = 0;
    for (i = 0; i < position_count; i++) {
        if (i == 0 || all_positions[i] != all_positions[i - 1]) {
            all_positions[unique_count] = all_positions[i];
            unique_count++;
        }
    }
    position_count = unique_count;
    positions = all_positions;
    tree = (int *)calloc(4 * (position_count + 1), sizeof(int));

    for (i = 0; i < q; i++) {
        if (queries[i].type == 1) {
            index = lower_bound_position(queries[i].value);
            if (position_count > 0) {
                set_position(1, 0, position_count - 1, index);
            }
        } else {
            index = lower_bound_position(queries[i].value);
            if (index == position_count) {
                printf("-1\n");
            } else {
                index = first_set_position(1, 0, position_count - 1, index);
                if (index == -1) {
                    printf("-1\n");
                } else {
                    printf("%d\n", positions[index]);
                }
            }
        }
    }

    free(queries);
    free(positions);
    free(tree);
    return 0;
}

