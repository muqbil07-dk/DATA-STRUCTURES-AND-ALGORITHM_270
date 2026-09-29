#include <stdio.h>
int main()
{
    int n;
    int height[100000];
    int nextHigher[100000];
    int stack[100000];
    long long stamina[100000];
    int top = -1;
    int i;
    long long answer;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &height[i]);
    for (i = n - 1; i >= 0; i--)
    {
        while (top >= 0 && height[stack[top]] <= height[i])
            top--;
        if (top == -1)
            nextHigher[i] = -1;
        else
            nextHigher[i] = stack[top];
        top++;
        stack[top] = i;
    }
    answer = 0;
    for (i = n - 1; i >= 0; i--)
    {
        stamina[i] = height[i];
        if (nextHigher[i] != -1)
            stamina[i] = stamina[i] ^ stamina[nextHigher[i]];

        if (stamina[i] > answer)
            answer = stamina[i];
    }
    printf("%lld\n", answer);
    return 0;
}

