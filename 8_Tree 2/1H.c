#include <stdio.h>
#include <stdlib.h>
struct Record {
    int node;
};
int **signatureValues;
int *signatureLength;
int *canonicalId;
int *signatureNext;
int *signatureRepresentative;
unsigned long *signatureHash;
int *hashHead;
int bucketCount;
int signatureCount;
int compareInts(const void *first, const void *second)
{
    int a, b;
    a = *(const int *)first;
    b = *(const int *)second;
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}
unsigned long makeHash(int node)
{
    unsigned long hash;
    int i;
    hash = 2166136261UL;
    hash ^= (unsigned long)(signatureLength[node] + 1);
    hash *= 16777619UL;
    for (i = 0; i < signatureLength[node]; i++) {
        hash ^= (unsigned long)(signatureValues[node][i] + 101);
        hash *= 16777619UL;
    }
    return hash;
}
int sameSignature(int first, int second)
{
    int i;
    if (signatureLength[first] != signatureLength[second]) {
        return 0;
    }
    for (i = 0; i < signatureLength[first]; i++) {
        if (signatureValues[first][i] != signatureValues[second][i]) {
            return 0;
        }
    }
    return 1;
}
int getCanonicalId(int node)
{
    unsigned long hash;
    int bucket, id, representative;
    hash = makeHash(node);
    bucket = (int)(hash % (unsigned long)bucketCount);
    id = hashHead[bucket];
    while (id != 0) {
        representative = signatureRepresentative[id];
        if (signatureHash[id] == hash && sameSignature(node, representative)) {
            return id;
        }
        id = signatureNext[id];
    }
    signatureCount++;
    signatureRepresentative[signatureCount] = node;
    signatureHash[signatureCount] = hash;
    signatureNext[signatureCount] = hashHead[bucket];
    hashHead[bucket] = signatureCount;
    return signatureCount;
}

int main(void)
{
    int tests, t, n, i, j, u, v, edgeCount, totalNodes;
    int *head, *to, *nextEdge, *parent, *depth, *stack;
    int *degree, *fill;
    struct Record *records;
    int maxDepth, count, position;

    if (scanf("%d", &tests) != 1) {
        return 0;
    }
    t = tests;
    while(t--) {
        scanf("%d", &n);
        totalNodes = 2 * n;
        head = (int *)malloc((size_t)totalNodes * sizeof(int));
        to = (int *)malloc((size_t)(4 * n) * sizeof(int));
        nextEdge = (int *)malloc((size_t)(4 * n) * sizeof(int));
        parent = (int *)malloc((size_t)totalNodes * sizeof(int));
        depth = (int *)malloc((size_t)totalNodes * sizeof(int));
        stack = (int *)malloc((size_t)totalNodes * sizeof(int));
        degree = (int *)calloc((size_t)totalNodes, sizeof(int));
        fill = (int *)calloc((size_t)totalNodes, sizeof(int));
        records = (struct Record *)malloc((size_t)totalNodes * sizeof(struct Record));
        signatureValues = (int **)malloc((size_t)totalNodes * sizeof(int *));
        signatureLength = (int *)calloc((size_t)totalNodes, sizeof(int));
        canonicalId = (int *)calloc((size_t)totalNodes, sizeof(int));
        bucketCount = 8 * totalNodes + 5;
        hashHead = (int *)calloc((size_t)bucketCount, sizeof(int));
        signatureNext = (int *)calloc((size_t)(totalNodes + 1), sizeof(int));
        signatureRepresentative = (int *)calloc((size_t)(totalNodes + 1), sizeof(int));
        signatureHash = (unsigned long *)calloc((size_t)(totalNodes + 1),
                                                  sizeof(unsigned long));
        signatureCount = 0;

        for (i = 0; i < totalNodes; i++) {
            head[i] = -1;
            parent[i] = -2;
            depth[i] = 0;
            signatureValues[i] = NULL;
        }
        edgeCount = 0;
        for (i = 0; i < 2 * (n - 1); i++) {
            scanf("%d %d", &u, &v);
            if (i < n - 1) {
                u--;
                v--;
            } else {
                u = u - 1 + n;
                v = v - 1 + n;
            }
            to[edgeCount] = v;
            nextEdge[edgeCount] = head[u];
            head[u] = edgeCount++;
            to[edgeCount] = u;
            nextEdge[edgeCount] = head[v];
            head[v] = edgeCount++;
        }

        maxDepth = 0;
        for (j = 0; j < 2; j++) {
            int root, top;
            root = j * n;
            top = 0;
            stack[top++] = root;
            parent[root] = -1;
            depth[root] = 0;
            while (top > 0) {
                u = stack[--top];
                if (depth[u] > maxDepth) {
                    maxDepth = depth[u];
                }
                for (i = head[u]; i != -1; i = nextEdge[i]) {
                    v = to[i];
                    if (v == parent[u]) {
                        continue;
                    }
                    parent[v] = u;
                    depth[v] = depth[u] + 1;
                    stack[top++] = v;
                }
            }
        }

        for (i = 0; i < totalNodes; i++) {
            for (j = head[i]; j != -1; j = nextEdge[j]) {
                v = to[j];
                if (parent[v] == i) {
                    degree[i]++;
                }
            }
            signatureLength[i] = degree[i];
            if (degree[i] > 0) {
                signatureValues[i] = (int *)malloc((size_t)degree[i] * sizeof(int));
            }
        }

        /* Process children before parents. Equal signatures share one ID. */
        for (j = maxDepth; j >= 0; j--) {
            count = 0;
            for (i = 0; i < totalNodes; i++) {
                if (depth[i] == j) {
                    records[count++].node = i;
                    fill[i] = 0;
                }
            }
            for (position = 0; position < count; position++) {
                u = records[position].node;
                for (i = head[u]; i != -1; i = nextEdge[i]) {
                    v = to[i];
                    if (parent[v] == u) {
                        signatureValues[u][fill[u]++] = canonicalId[v];
                    }
                }
                if (signatureLength[u] > 1) {
                    qsort(signatureValues[u], (size_t)signatureLength[u],
                          sizeof(int), compareInts);
                }
                canonicalId[u] = getCanonicalId(u);
            }
        }

        if (canonicalId[0] == canonicalId[n]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }

        for (i = 0; i < totalNodes; i++) {
            free(signatureValues[i]);
        }
        free(records);
        free(signatureValues);
        free(signatureLength);
        free(canonicalId);
        free(signatureNext);
        free(signatureRepresentative);
        free(signatureHash);
        free(hashHead);
        free(head);
        free(to);
        free(nextEdge);
        free(parent);
        free(depth);
        free(stack);
        free(degree);
        free(fill);
    }
    return 0;
}

