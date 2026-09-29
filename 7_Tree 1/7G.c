#include <stdio.h>
#include <stdlib.h>
#define MAXL 200005
struct state {
    int len;
    int link;
    int head;
};
struct state st[MAXL];
int stateCount;
int *hashState;
int *hashChar;
int *hashValue;
int *hashNext;
int hashSize;
int hashMask;

int hashCode(int stateNumber, int character) {
    unsigned int value;

    value = (unsigned int)stateNumber * 1000003u;
    value ^= (unsigned int)character * 9176u;
    value ^= value >> 16;
    return (int)(value & (unsigned int)hashMask);
}

int getTransition(int from, int character) {
    int position;

    position = hashCode(from, character);
    while (hashState[position] != -1) {
        if (hashState[position] == from && hashChar[position] == character) {
            return hashValue[position];
        }
        position = (position + 1) & hashMask;
    }
    return -1;
}

void setTransition(int from, int character, int to) {
    int position;

    position = hashCode(from, character);
    while (hashState[position] != -1) {
        if (hashState[position] == from && hashChar[position] == character) {
            hashValue[position] = to;
            return;
        }
        position = (position + 1) & hashMask;
    }

    hashState[position] = from;
    hashChar[position] = character;
    hashValue[position] = to;
    hashNext[position] = st[from].head;
    st[from].head = position;
}

int makeState(void) {
    int number;

    number = stateCount++;
    st[number].len = 0;
    st[number].link = -1;
    st[number].head = -1;
    return number;
}

int cloneState(int original, int newLength) {
    int clone;
    int edge;

    clone = makeState();
    st[clone].len = newLength;
    st[clone].link = st[original].link;

    edge = st[original].head;
    while (edge != -1) {
        setTransition(clone, hashChar[edge], hashValue[edge]);
        edge = hashNext[edge];
    }

    return clone;
}

int extendFrom(int last, int character) {
    int current;
    int p;
    int q;
    int clone;

    q = getTransition(last, character);
    if (q != -1) {
        if (st[q].len == st[last].len + 1) {
            return q;
        }

        clone = cloneState(q, st[last].len + 1);
        p = last;
        while (p != -1 && getTransition(p, character) == q) {
            setTransition(p, character, clone);
            p = st[p].link;
        }
        st[q].link = clone;
        return clone;
    }

    current = makeState();
    st[current].len = st[last].len + 1;
    p = last;

    while (p != -1 && getTransition(p, character) == -1) {
        setTransition(p, character, current);
        p = st[p].link;
    }

    if (p == -1) {
        st[current].link = 0;
    } else {
        q = getTransition(p, character);
        if (st[q].len == st[p].len + 1) {
            st[current].link = q;
        } else {
            clone = cloneState(q, st[p].len + 1);
            while (p != -1 && getTransition(p, character) == q) {
                setTransition(p, character, clone);
                p = st[p].link;
            }
            st[q].link = clone;
            st[current].link = clone;
        }
    }

    return current;
}

int main(void) {
    int n;
    int i;
    int edgeCount;
    int *head;
    int *to;
    int *next;
    int *degree;
    int *parent;
    int *order;
    int orderCount;
    int vertex;
    int edge;
    int child;
    int *position;
    long long answer;

    scanf("%d", &n);

    head = (int *)malloc((n + 1) * sizeof(int));
    to = (int *)malloc((2 * n) * sizeof(int));
    next = (int *)malloc((2 * n) * sizeof(int));
    degree = (int *)calloc(n + 1, sizeof(int));
    parent = (int *)calloc(n + 1, sizeof(int));
    order = (int *)malloc((n + 1) * sizeof(int));
    position = (int *)malloc((n + 1) * sizeof(int));

    for (i = 1; i <= n; i++) {
        head[i] = -1;
    }
    edgeCount = 0;

    for (i = 0; i < n - 1; i++) {
        int u;
        int v;

        scanf("%d %d", &u, &v);
        to[edgeCount] = v;
        next[edgeCount] = head[u];
        head[u] = edgeCount;
        edgeCount++;
        to[edgeCount] = u;
        next[edgeCount] = head[v];
        head[v] = edgeCount;
        edgeCount++;
        degree[u]++;
        degree[v]++;
    }

    orderCount = 1;
    order[0] = 1;
    parent[1] = -1;

    for (i = 0; i < orderCount; i++) {
        vertex = order[i];
        edge = head[vertex];
        while (edge != -1) {
            child = to[edge];
            if (child != parent[vertex]) {
                parent[child] = vertex;
                order[orderCount] = child;
                orderCount++;
            }
            edge = next[edge];
        }
    }

    hashSize = 1;
    while (hashSize < 8 * (n + 1)) {
        hashSize = hashSize * 2;
    }
    hashMask = hashSize - 1;
    hashState = (int *)malloc(hashSize * sizeof(int));
    hashChar = (int *)malloc(hashSize * sizeof(int));
    hashValue = (int *)malloc(hashSize * sizeof(int));
    hashNext = (int *)malloc(hashSize * sizeof(int));

    for (i = 0; i < hashSize; i++) {
        hashState[i] = -1;
    }

    stateCount = 0;
    makeState();
    position[1] = extendFrom(0, degree[1]);

    for (i = 1; i < orderCount; i++) {
        vertex = order[i];
        position[vertex] = extendFrom(position[parent[vertex]], degree[vertex]);
    }

    answer = 0;
    for (i = 1; i < stateCount; i++) {
        answer += (long long)st[i].len - st[st[i].link].len;
    }
    printf("%lld\n", answer);

    free(head);
    free(to);
    free(next);
    free(degree);
    free(parent);
    free(order);
    free(position);
    free(hashState);
    free(hashChar);
    free(hashValue);
    free(hashNext);
    return 0;
}

