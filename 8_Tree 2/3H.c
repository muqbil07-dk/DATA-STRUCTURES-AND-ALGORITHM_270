#include <stdio.h>
#include <stdlib.h>
#define MAXN 100000
#define MAXE 300005
int n, originalM;
int edgeCount;
int edgeFrom[MAXE], edgeTo[MAXE];
int head[MAXN + 5], reverseHead[MAXN + 5];
int nextEdge[MAXE], reverseNext[MAXE];
int toEdge[MAXE], reverseTo[MAXE];
int component[MAXN + 5];
int componentRepresentative[MAXN + 5];
int visited[MAXN + 5];
int order[MAXN + 5];
int stackNodes[MAXN + 5];
int stackEdge[MAXN + 5];
int sourceVertices[MAXN + 5];
int sinkVertices[MAXN + 5];
int shuffledSources[MAXN + 5];
int shuffledSinks[MAXN + 5];
int candidateFrom[MAXN + 5];
int candidateTo[MAXN + 5];
unsigned int randomState = 712367821U;
unsigned int nextRandom(void)
{
    randomState ^= randomState << 13;
    randomState ^= randomState >> 17;
    randomState ^= randomState << 5;
    return randomState;
}
void addEdge(int a, int b)
{
    edgeFrom[edgeCount] = a;
    edgeTo[edgeCount] = b;
    edgeCount++;
}
void makeAdjacency(void)
{
    int i;
    for (i = 1; i <= n; i++) {
        head[i] = -1;
        reverseHead[i] = -1;
    }

    for (i = 0; i < edgeCount; i++) {
        toEdge[i] = edgeTo[i];
        nextEdge[i] = head[edgeFrom[i]];
        head[edgeFrom[i]] = i;

        reverseTo[i] = edgeFrom[i];
        reverseNext[i] = reverseHead[edgeTo[i]];
        reverseHead[edgeTo[i]] = i;
    }
}

int findComponents(int *sourceCount, int *sinkCount)
{
    int i, u, v, e, top;
    int orderCount, componentCount;

    int indegree[MAXN + 5];
    int outdegree[MAXN + 5];

    makeAdjacency();

    for (i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    orderCount = 0;

    for (i = 1; i <= n; i++) {
        if (visited[i]) {
            continue;
        }

        top = 0;
        stackNodes[top] = i;
        stackEdge[top] = head[i];
        top++;

        visited[i] = 1;

        while (top > 0) {
            u = stackNodes[top - 1];
            e = stackEdge[top - 1];

            if (e != -1) {
                stackEdge[top - 1] = nextEdge[e];
                v = toEdge[e];

                if (!visited[v]) {
                    visited[v] = 1;
                    stackNodes[top] = v;
                    stackEdge[top] = head[v];
                    top++;
                }
            } else {
                order[orderCount++] = u;
                top--;
            }
        }
    }

    for (i = 1; i <= n; i++) {
        visited[i] = 0;
    }

    componentCount = 0;

    for (i = orderCount - 1; i >= 0; i--) {
        u = order[i];

        if (visited[u]) {
            continue;
        }

        componentCount++;
        top = 0;
        stackNodes[top++] = u;
        visited[u] = 1;

        componentRepresentative[componentCount] = u;

        while (top > 0) {
            u = stackNodes[--top];
            component[u] = componentCount;

            e = reverseHead[u];

            while (e != -1) {
                v = reverseTo[e];

                if (!visited[v]) {
                    visited[v] = 1;
                    stackNodes[top++] = v;
                }

                e = reverseNext[e];
            }
        }
    }

    for (i = 1; i <= componentCount; i++) {
        indegree[i] = 0;
        outdegree[i] = 0;
    }

    for (i = 0; i < edgeCount; i++) {
        u = component[edgeFrom[i]];
        v = component[edgeTo[i]];

        if (u != v) {
            outdegree[u] = 1;
            indegree[v] = 1;
        }
    }

    *sourceCount = 0;
    *sinkCount = 0;

    for (i = 1; i <= componentCount; i++) {
        if (!indegree[i]) {
            sourceVertices[*sourceCount] =
                componentRepresentative[i];
            (*sourceCount)++;
        }

        if (!outdegree[i]) {
            sinkVertices[*sinkCount] =
                componentRepresentative[i];
            (*sinkCount)++;
        }
    }

    return componentCount;
}

void shuffleArray(int *a, int length)
{
    int i, j, temp;

    for (i = length - 1; i > 0; i--) {
        j = (int)(nextRandom() % (unsigned int)(i + 1));

        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
}

int main(void)
{
    int m, i;
    int components, sourceCount, sinkCount;
    int oldSources, oldSinks, batch, accepted;
    int tries, s, t, newSources, newSinks;
    int answerCount;

    if (scanf("%d %d", &n, &m) != 2) {
        return 0;
    }

    edgeCount = 0;
    originalM = m;

    while(m--) {
        scanf("%d %d", &s, &t);
        addEdge(s, t);
    }

    components = findComponents(&sourceCount, &sinkCount);
    answerCount = 0;

    while (components > 1 &&
           sourceCount > 1 &&
           sinkCount > 1) {

        oldSources = sourceCount;
        oldSinks = sinkCount;

        batch = oldSources < oldSinks
              ? oldSources
              : oldSinks;

        batch /= 2;
        accepted = 0;
        tries = 0;

        while (!accepted) {
            for (i = 0; i < oldSources; i++) {
                shuffledSources[i] = sourceVertices[i];
            }

            for (i = 0; i < oldSinks; i++) {
                shuffledSinks[i] = sinkVertices[i];
            }

            shuffleArray(shuffledSources, oldSources);
            shuffleArray(shuffledSinks, oldSinks);

            accepted = 1;

            for (i = 0; i < batch; i++) {
                s = shuffledSources[i];
                t = shuffledSinks[i];

                candidateFrom[i] = t;
                candidateTo[i] = s;
            }

            for (i = 0; i < batch; i++) {
                addEdge(candidateFrom[i], candidateTo[i]);
            }

            components = findComponents(&newSources, &newSinks);

            if (newSources != oldSources - batch ||
                newSinks != oldSinks - batch) {

                edgeCount -= batch;
                accepted = 0;
                tries++;

                if (tries > 100000) {
                    randomState += 977;
                    tries = 0;
                }
            } else {
                sourceCount = newSources;
                sinkCount = newSinks;
                answerCount += batch;
            }
        }
    }

    if (components > 1) {
        if (sourceCount == 1) {
            s = sourceVertices[0];

            for (i = 0; i < sinkCount; i++) {
                addEdge(sinkVertices[i], s);
                answerCount++;
            }
        } else {
            t = sinkVertices[0];

            for (i = 0; i < sourceCount; i++) {
                addEdge(t, sourceVertices[i]);
                answerCount++;
            }
        }
    }

    printf("%d\n", answerCount);

    for (i = originalM; i < edgeCount; i++) {
        printf("%d %d\n", edgeFrom[i], edgeTo[i]);
    }

    return 0;
}
