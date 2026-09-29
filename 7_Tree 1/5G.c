#include <stdio.h>
#include <stdlib.h>

int *tree;

void build(int *aa, int k, int l, int r) {
    int middle;

    if (l == r) {
        tree[k] = aa[l];
        return;
    }

    middle = (l + r) / 2;
    build(aa, 2 * k, l, middle);
    build(aa, 2 * k + 1, middle + 1, r);

    if (tree[2 * k] < tree[2 * k + 1]) {
        tree[k] = tree[2 * k];
    } else {
        tree[k] = tree[2 * k + 1];
    }
}

int query(int k, int l, int r, int ql, int qr) {
    int middle;
    int leftValue;
    int rightValue;

    if (ql <= l && r <= qr) {
        return tree[k];
    }

    middle = (l + r) / 2;

    if (qr <= middle) {
        return query(2 * k, l, middle, ql, qr);
    }
    if (ql > middle) {
        return query(2 * k + 1, middle + 1, r, ql, qr);
    }

    leftValue = query(2 * k, l, middle, ql, qr);
    rightValue = query(2 * k + 1, middle + 1, r, ql, qr);

    if (leftValue < rightValue) {
        return leftValue;
    }
    return rightValue;
}

int main(void) {
    int n;
    int q;
    int i;
    int *aa;
    int l;
    int r;

    scanf("%d %d", &n, &q);
    aa = (int *)malloc((n + 1) * sizeof(int));
    tree = (int *)malloc((4 * n + 5) * sizeof(int));

    for (i = 1; i <= n; i++) {
        scanf("%d", &aa[i]);
    }

    build(aa, 1, 1, n);

    for (i = 0; i < q; i++) {
        scanf("%d %d", &l, &r);
        printf("%d\n", query(1, 1, n, l, r));
    }

    free(aa);
    free(tree);
    return 0;
}

