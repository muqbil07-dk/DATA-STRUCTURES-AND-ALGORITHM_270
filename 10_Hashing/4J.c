#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(void)
{
    int t;
    int test_case = 0;
    int n;
    int i;
    int target;
    int maximum;
    int mutual_pairs;
    int *boy_crush;
    int *girl_crush;
    int *boy_target;
    int *girl_target;
    int *boy_received;
    int *girl_received;
    if (scanf("%d", &t) != 1) {
        return 0;
    }

    while(true) {
        if (test_case == t) {
            break;
        }
        scanf("%d", &n);
        boy_crush = (int *)malloc((n + 1) * sizeof(int));
        girl_crush = (int *)malloc((n + 1) * sizeof(int));
        boy_target = (int *)malloc((n + 1) * sizeof(int));
        girl_target = (int *)malloc((n + 1) * sizeof(int));
        boy_received = (int *)calloc(n + 1, sizeof(int));
        girl_received = (int *)calloc(n + 1, sizeof(int));

        for (i = 1; i <= n; i++) {
            scanf("%d", &boy_crush[i]);
        }
        for (i = 1; i <= n; i++) {
            scanf("%d", &girl_crush[i]);
        }

        for (i = 1; i <= n; i++) {
            boy_target[i] = girl_crush[boy_crush[i]];
            girl_target[i] = boy_crush[girl_crush[i]];
            if (boy_target[i] != i) {
                boy_received[boy_target[i]]++;
            }
            if (girl_target[i] != i) {
                girl_received[girl_target[i]]++;
            }
        }

        maximum = 0;
        for (i = 1; i <= n; i++) {
            if (boy_received[i] > maximum) {
                maximum = boy_received[i];
            }
            if (girl_received[i] > maximum) {
                maximum = girl_received[i];
            }
        }

        mutual_pairs = 0;
        for (i = 1; i <= n; i++) {
            target = boy_target[i];
            if (target != i && i < target && boy_target[target] == i) {
                mutual_pairs++;
            }
            target = girl_target[i];
            if (target != i && i < target && girl_target[target] == i) {
                mutual_pairs++;
            }
        }

        printf("%d %d\n", maximum, mutual_pairs);
        free(boy_crush);
        free(girl_crush);
        free(boy_target);
        free(girl_target);
        free(boy_received);
        free(girl_received);
        test_case++;
    }
    return 0;
}

