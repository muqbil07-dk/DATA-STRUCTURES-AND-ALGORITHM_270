#include <stdio.h>
int main()
{
    int stack1[5];
    int stack2[5];
    int top1 = -1;
    int top2 = -1;
    int i;
    int value;
    for (i = 0; i < 5; i++)
    {
        scanf("%d", &value);
        if (i % 2 == 0)
        {
            top1++;
            stack1[top1] = value;
        }
        else
        {
            top2++;
            stack2[top2] = value;
        }
    }
    printf("Popped element from stack1 is:%d\n", stack1[top1]);
    printf("Popped element from stack2 is:%d\n", stack2[top2]);
    return 0;
}

