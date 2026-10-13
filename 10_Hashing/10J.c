#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int N;
    int M;
    int i;
    int j;
    int k;
    int residue;
    int *frequency;
    long long answer = 0;
    if (scanf("%d %d", &N, &M) != 2) {
        return 0;
    }

    frequency = (int *)calloc(M, sizeof(int));
    i = 0;
    k = N;
    while(i<k) {
        int value;
        scanf("%d", &value);
        residue = value % M;
        frequency[residue]++;
        i++;
    }

    for (i = 0; i < M; i++) {
        for (j = i; j < M; j++) {
            residue = (M - ((i + j) % M)) % M;
            if (residue < j) {
                continue;
            }
            if (i == j && j == residue) {
                answer += (long long)frequency[i] * (frequency[i] - 1)
                        * (frequency[i] - 2) / 6;
            } else if (i == j) {
                answer += (long long)frequency[i] * (frequency[i] - 1) / 2
                        * frequency[residue];
            } else if (j == residue) {
                answer += (long long)frequency[i] * frequency[j]
                        * (frequency[j] - 1) / 2;
            } else {
                answer += (long long)frequency[i] * frequency[j]
                        * frequency[residue];
            }
        }
    }

    printf("%lld\n", answer);
    free(frequency);
    return 0;
}

