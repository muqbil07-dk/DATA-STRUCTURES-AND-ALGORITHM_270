#include <stdio.h>

int digit_sum_hex(int value)
{
    int sum;

    sum = 0;
    while (value > 0) {
        sum += value % 16;
        value /= 16;
    }
    return sum;
}

int gcd(int a, int b)
{
    int temp;

    while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int search(int a, int b)
{
    int value;
    int count;
    int sum;

    if (a > b) {
        value = a;
        a = b;
        b = value;
    }

    count = 0;
    for (value = a; value <= b; value++) {
        sum = digit_sum_hex(value);
        if (gcd(value, sum) > 1)
            count++;
    }
    return count;
}

int main(void)
{
    int t;
    int left;
    int right;

    scanf("%d", &t);
    while (t-- > 0) {
        scanf("%d %d", &left, &right);
        printf("%d\n", search(left, right));
    }
    return 0;
}

