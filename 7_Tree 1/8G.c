#include <stdio.h>
#include <stdlib.h>

struct operation {
    char type;
    int a;
    long long b;
};

int compareLongLong(const void *first, const void *second) {
    long long a;
    long long b;

    a = *(const long long *)first;
    b = *(const long long *)second;
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}

int lowerBound(long long *values, int count, long long target) {
    int left;
    int right;
    int middle;

    left = 0;
    right = count;
    while (left < right) {
        middle = (left + right) / 2;
        if (values[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

int upperBound(long long *values, int count, long long target) {
    int left;
    int right;
    int middle;

    left = 0;
    right = count;
    while (left < right) {
        middle = (left + right) / 2;
        if (values[middle] <= target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

void addFenwick(int *fenwick, int size, int index, int amount) {
    while (index <= size) {
        fenwick[index] += amount;
        index += index & -index;
    }
}

int sumFenwick(int *fenwick, int index) {
    int result;

    result = 0;
    while (index > 0) {
        result += fenwick[index];
        index -= index & -index;
    }
    return result;
}

int main(void) {
    int n;
    int q;
    int i;
    int coordinateCount;
    int index;
    int leftIndex;
    int rightIndex;
    long long *salary;
    long long *coordinates;
    struct operation *operations;
    int *fenwick;

    scanf("%d %d", &n, &q);
    salary = (long long *)malloc((n + 1) * sizeof(long long));
    coordinates = (long long *)malloc((n + q + 1) * sizeof(long long));
    operations = (struct operation *)malloc(q * sizeof(struct operation));

    for (i = 1; i <= n; i++) {
        scanf("%lld", &salary[i]);
        coordinates[i - 1] = salary[i];
    }

    for (i = 0; i < q; i++) {
        scanf(" %c %d %lld", &operations[i].type,
              &operations[i].a, &operations[i].b);
        if (operations[i].type == '!') {
            coordinates[n + i] = operations[i].b;
        } else {
            coordinates[n + i] = salary[1];
        }
    }

    qsort(coordinates, n + q, sizeof(long long), compareLongLong);
    coordinateCount = 0;
    for (i = 0; i < n + q; i++) {
        if (i == 0 || coordinates[i] != coordinates[i - 1]) {
            coordinates[coordinateCount] = coordinates[i];
            coordinateCount++;
        }
    }

    fenwick = (int *)calloc(coordinateCount + 1, sizeof(int));
    for (i = 1; i <= n; i++) {
        index = lowerBound(coordinates, coordinateCount, salary[i]) + 1;
        addFenwick(fenwick, coordinateCount, index, 1);
    }

    for (i = 0; i < q; i++) {
        if (operations[i].type == '!') {
            index = lowerBound(coordinates, coordinateCount, salary[operations[i].a]) + 1;
            addFenwick(fenwick, coordinateCount, index, -1);
            salary[operations[i].a] = operations[i].b;
            index = lowerBound(coordinates, coordinateCount, salary[operations[i].a]) + 1;
            addFenwick(fenwick, coordinateCount, index, 1);
        } else {
            leftIndex = lowerBound(coordinates, coordinateCount, operations[i].a);
            rightIndex = upperBound(coordinates, coordinateCount, operations[i].b);
            printf("%d\n", sumFenwick(fenwick, rightIndex)
                - sumFenwick(fenwick, leftIndex));
        }
    }

    free(salary);
    free(coordinates);
    free(operations);
    free(fenwick);
    return 0;
}

