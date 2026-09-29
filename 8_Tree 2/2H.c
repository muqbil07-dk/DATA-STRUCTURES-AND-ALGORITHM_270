#include <stdio.h>
#include <stdlib.h>
struct Item {
    long long value;
    int id;
};
int minSize, maxSize;
struct Item *minHeap;
struct Item *maxHeap;
int *active;
int beforeMin(struct Item a, struct Item b)
{
    if (a.value != b.value) {
        return a.value < b.value;
    }

    return a.id < b.id;
}
int beforeMax(struct Item a, struct Item b)
{
    if (a.value != b.value) {
        return a.value > b.value;
    }

    return a.id < b.id;
}
void swapItem(struct Item *a, struct Item *b)
{
    struct Item temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
void pushMin(struct Item x)
{
    int i, p;
    i = minSize++;
    minHeap[i] = x;
    while (i > 0) {
        p = (i - 1) / 2;
        if (beforeMin(minHeap[p], minHeap[i])) {
            break;
        }
        swapItem(&minHeap[p], &minHeap[i]);
        i = p;
    }
}
void pushMax(struct Item x)
{
    int i, p;
    i = maxSize++;
    maxHeap[i] = x;
    while (i > 0) {
        p = (i - 1) / 2;
        if (beforeMax(maxHeap[p], maxHeap[i])) {
            break;
        }

        swapItem(&maxHeap[p], &maxHeap[i]);
        i = p;
    }
}

struct Item popMin(void)
{
    struct Item result;
    int i, left, right, best;

    result = minHeap[0];

    minSize--;
    minHeap[0] = minHeap[minSize];

    i = 0;

    while (1) {
        left = 2 * i + 1;
        right = left + 1;
        best = i;

        if (left < minSize &&
            beforeMin(minHeap[left], minHeap[best])) {
            best = left;
        }

        if (right < minSize &&
            beforeMin(minHeap[right], minHeap[best])) {
            best = right;
        }

        if (best == i) {
            break;
        }

        swapItem(&minHeap[i], &minHeap[best]);
        i = best;
    }

    return result;
}

struct Item popMax(void)
{
    struct Item result;
    int i, left, right, best;

    result = maxHeap[0];

    maxSize--;
    maxHeap[0] = maxHeap[maxSize];

    i = 0;

    while (1) {
        left = 2 * i + 1;
        right = left + 1;
        best = i;

        if (left < maxSize &&
            beforeMax(maxHeap[left], maxHeap[best])) {
            best = left;
        }

        if (right < maxSize &&
            beforeMax(maxHeap[right], maxHeap[best])) {
            best = right;
        }

        if (best == i) {
            break;
        }

        swapItem(&maxHeap[i], &maxHeap[best]);
        i = best;
    }

    return result;
}

void removeInactiveMin(void)
{
    while (minSize > 0 && !active[minHeap[0].id]) {
        popMin();
    }
}

void removeInactiveMax(void)
{
    while (maxSize > 0 && !active[maxHeap[0].id]) {
        popMax();
    }
}

int main(void)
{
    int n, q, i, k, nextId;
    long long value, sum, difference;
    struct Item low, high, inserted;
    long long *answer;

    if (scanf("%d %d", &n, &q) != 2) {
        return 0;
    }

    minHeap = (struct Item *)malloc(
        (size_t)(2 * n + 5) * sizeof(struct Item));

    maxHeap = (struct Item *)malloc(
        (size_t)(2 * n + 5) * sizeof(struct Item));

    active = (int *)calloc((size_t)(2 * n + 5), sizeof(int));
    answer = (long long *)malloc((size_t)n * sizeof(long long));

    minSize = 0;
    maxSize = 0;
    sum = 0;
    nextId = 0;

    for(i=0;i<n;i++) {
        scanf("%lld", &value);

        inserted.value = value;
        inserted.id = nextId++;

        active[inserted.id] = 1;

        pushMin(inserted);
        pushMax(inserted);

        sum += value;
    }

    answer[0] = sum;

    for (i = 1; i < n; i++) {
        removeInactiveMin();
        removeInactiveMax();

        low = popMin();
        high = popMax();

        active[low.id] = 0;
        active[high.id] = 0;

        difference = high.value - low.value;

        sum -= low.value + high.value;
        sum += difference;

        inserted.value = difference;
        inserted.id = nextId++;

        active[inserted.id] = 1;

        pushMin(inserted);
        pushMax(inserted);

        answer[i] = sum;
    }

    while (q--) {
        scanf("%d", &k);
        printf("%lld\n", answer[k]);
    }

    free(minHeap);
    free(maxHeap);
    free(active);
    free(answer);

    return 0;
}
