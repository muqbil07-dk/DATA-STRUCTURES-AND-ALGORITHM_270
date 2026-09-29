#include <stdio.h>
#define MAXN 200005
typedef struct
{
    int length;
    int prefix0, suffix0, best0;
    int prefix1, suffix1, best1;
} Node;
Node tree[4 * MAXN];
char bits[MAXN];
int maximum(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
void makeLeaf(int node, int value)
{
    tree[node].length = 1;
    if (value == 0)
    {
        tree[node].prefix0 = 1;
        tree[node].suffix0 = 1;
        tree[node].best0 = 1;
        tree[node].prefix1 = 0;
        tree[node].suffix1 = 0;
        tree[node].best1 = 0;
    }
    else
    {
        tree[node].prefix0 = 0;
        tree[node].suffix0 = 0;
        tree[node].best0 = 0;
        tree[node].prefix1 = 1;
        tree[node].suffix1 = 1;
        tree[node].best1 = 1;
    }
}
void combine(int node, int leftNode, int rightNode)
{
    Node left = tree[leftNode];
    Node right = tree[rightNode];
    tree[node].length = left.length + right.length;
    tree[node].prefix0 = left.prefix0;
    if (left.prefix0 == left.length)
        tree[node].prefix0 = left.length + right.prefix0;
    tree[node].suffix0 = right.suffix0;
    if (right.suffix0 == right.length)
        tree[node].suffix0 = right.length + left.suffix0;
    tree[node].best0 = maximum(left.best0, right.best0);
    tree[node].best0 = maximum(tree[node].best0,
                               left.suffix0 + right.prefix0);
    tree[node].prefix1 = left.prefix1;
    if (left.prefix1 == left.length)
        tree[node].prefix1 = left.length + right.prefix1;
    tree[node].suffix1 = right.suffix1;
    if (right.suffix1 == right.length)
        tree[node].suffix1 = right.length + left.suffix1;
    tree[node].best1 = maximum(left.best1, right.best1);
    tree[node].best1 = maximum(tree[node].best1,
                               left.suffix1 + right.prefix1);
}
void build(int node, int left, int right)
{
    int middle;
    if (left == right)
    {
        makeLeaf(node, bits[left] - '0');
        return;
    }
    middle = (left + right) / 2;
    build(node * 2, left, middle);
    build(node * 2 + 1, middle + 1, right);
    combine(node, node * 2, node * 2 + 1);
}
void change(int node, int left, int right, int position)
{
    int middle;
    if (left == right)
    {
        if (bits[position] == '0')
            bits[position] = '1';
        else
            bits[position] = '0';

        makeLeaf(node, bits[position] - '0');
        return;
    }
    middle = (left + right) / 2;
    if (position <= middle)
        change(node * 2, left, middle, position);
    else
        change(node * 2 + 1, middle + 1, right, position);
    combine(node, node * 2, node * 2 + 1);
}
int main()
{
    int n, m;
    int i, position;
    int answer;
    scanf("%s", bits + 1);
    scanf("%d", &m);
    n = 0;
    while (bits[n + 1] != '\0')
        n++;
    build(1, 1, n);
    for (i = 0; i < m; i++)
    {
        scanf("%d", &position);
        change(1, 1, n, position);
        answer = maximum(tree[1].best0, tree[1].best1);
        if (i > 0)
            printf(" ");
        printf("%d", answer);
    }
    printf("\n");
    return 0;
}
