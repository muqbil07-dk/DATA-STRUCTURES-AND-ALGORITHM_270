#include <stdio.h>
#include <stdlib.h>
int *A;
int hash[1000001];
int main(void)
{
    int M;
    int Q;
    int N;
    int i;
    int r;
    int q_value;
    int length;
    int current;
    int answer = 0;
    int *maximum_quotient;
    int *quotient;
    int *residue;
    int **difference;

    if (scanf("%d", &M) != 1) {
        return 0;
    }
    scanf("%d", &Q);
    scanf("%d", &N);

    A = (int *)malloc(N * sizeof(int));
    maximum_quotient = (int *)calloc(M, sizeof(int));
    quotient = (int *)malloc(N * sizeof(int));
    residue = (int *)malloc(N * sizeof(int));

    for(i=0;i<N;i++) {
        scanf("%d", &A[i]);
        hash[A[i]]++;
        residue[i] = A[i] % M;
        quotient[i] = A[i] / M;
        if (quotient[i] > maximum_quotient[residue[i]]) {
            maximum_quotient[residue[i]] = quotient[i];
        }
    }

    difference = (int **)malloc(M * sizeof(int *));
    for (r = 0; r < M; r++) {
        length = maximum_quotient[r] + 2 * Q + 3;
        difference[r] = (int *)calloc(length, sizeof(int));
    }

    for (i = 0; i < N; i++) {
        r = residue[i];
        q_value = quotient[i] + Q;
        difference[r][q_value - Q]++;
        difference[r][q_value + Q + 1]--;
    }

    for (r = 0; r < M; r++) {
        length = maximum_quotient[r] + 2 * Q + 3;
        current = 0;
        for (i = 0; i < length; i++) {
            current += difference[r][i];
            if (current > answer) {
                answer = current;
            }
        }
    }

    printf("%d\n", answer);
    for (r = 0; r < M; r++) {
        free(difference[r]);
    }
    free(difference);
    free(A);
    free(maximum_quotient);
    free(quotient);
    free(residue);
    return 0;
}

