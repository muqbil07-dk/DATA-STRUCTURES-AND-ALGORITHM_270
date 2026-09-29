#include <stdio.h>
#include <stdlib.h>
#define MAXN 200000
long long tree[4 * MAXN + 5];
long long lazyP[4 * MAXN + 5];
long long lazyQ[4 * MAXN + 5];
long long arr[MAXN + 5];
long long indexSum(int l, int r)
{
    long long count;

    count = r - l + 1;

    return ((long long)l + r) * count / 2;
}

void build(int k,int l,int r)
{
    int mid;

    if (l == r) {
        tree[k] = arr[l];
        return;
    }

    mid = (l + r) / 2;

    build(k * 2, l, mid);
    build(k * 2 + 1, mid + 1, r);

    tree[k] = tree[k * 2] + tree[k * 2 + 1];
}

void apply(int k, int l, int r, long long p, long long q)
{
    tree[k] += p * indexSum(l, r);
    tree[k] += q * (r - l + 1LL);

    lazyP[k] += p;
    lazyQ[k] += q;
}

void push(int k, int l, int r)
{
    int mid;

    if (lazyP[k] == 0 && lazyQ[k] == 0) {
        return;
    }

    if (l != r) {
        mid = (l + r) / 2;

        apply(k * 2, l, mid, lazyP[k], lazyQ[k]);
        apply(k * 2 + 1,
              mid + 1,
              r,
              lazyP[k],
              lazyQ[k]);
    }

    lazyP[k] = 0;
    lazyQ[k] = 0;
}

void update(int k,
            int l,
            int r,
            int ql,
            int qr,
            long long p,
            long long q)
{
    int mid;

    if (qr < l || r < ql) {
        return;
    }

    if (ql <= l && r <= qr) {
        apply(k, l, r, p, q);
        return;
    }

    push(k, l, r);

    mid = (l + r) / 2;

    update(k * 2, l, mid, ql, qr, p, q);
    update(k * 2 + 1,
           mid + 1,
           r,
           ql,
           qr,
           p,
           q);

    tree[k] = tree[k * 2] + tree[k * 2 + 1];
}

long long query(int k, int l, int r, int ql, int qr)
{
    int mid;
    long long leftAnswer, rightAnswer;

    if (qr < l || r < ql) {
        return 0;
    }

    if (ql <= l && r <= qr) {
        return tree[k];
    }

    push(k, l, r);

    mid = (l + r) / 2;

    leftAnswer = query(k * 2, l, mid, ql, qr);
    rightAnswer = query(k * 2 + 1,
                        mid + 1,
                        r,
                        ql,
                        qr);

    return leftAnswer + rightAnswer;
}

int main(void)
{
    int n, q, i, type, a, b;
    long long answer;

    if (scanf("%d %d", &n, &q) != 2) {
        return 0;
    }

    for (i = 1; i <= n; i++) {
        scanf("%lld", &arr[i]);
    }

    build(1, 1, n);

    while (q--) {
        scanf("%d %d %d", &type, &a, &b);

        if (type == 1) {
            update(1,
                   1,
                   n,
                   a,
                   b,
                   1,
                   1 - (long long)a);
        } else {
            answer = query(1, 1, n, a, b);
            printf("%lld\n", answer);
        }
    }

    return 0;
}
