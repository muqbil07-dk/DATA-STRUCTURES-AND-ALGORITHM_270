#include <stdio.h>
#include <math.h>
#include <stdbool.h>
int main(void)
{
    int t;
    int a;
    int b;
    int small;
    int difference;
    long long losing_difference;
    long double phi;

    if (scanf("%d", &t) != 1) {
        return 0;
    }

    phi = (1.0L + sqrtl(5.0L)) / 2.0L;
    while(t--) {
        scanf("%d %d", &a, &b);
        if (a < b) {
            small = a;
            difference = b - a;
        } else {
            small = b;
            difference = a - b;
        }
        losing_difference = (long long)(difference * phi);
        if (losing_difference == small) {
            printf("sami\n");
        } else {
            printf("canthi\n");
        }
    }
    return 0;
}

