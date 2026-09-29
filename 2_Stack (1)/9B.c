#include <stdio.h>
int main()
{
    int n, m;
    int queue[100005];
    int capacity;
    int front = 0;
    int rear = 0;
    int size = 0;
    int i, j;
    int value;
    int oldSize;
    scanf("%d %d", &n, &m);
    capacity = n + 1;
    for (i = 0; i < n; i++)
    {
        scanf("%d", &value);
        queue[rear] = value;
        rear = (rear + 1) % capacity;
        size++;
        oldSize = size - 1;
        for (j = 0; j < oldSize; j++)
        {
            value = queue[front];
            front = (front + 1) % capacity;
            queue[rear] = value;
            rear = (rear + 1) % capacity;
        }
    }
    printf("top of element %d\n", queue[front]);
    for (i = 0; i < m; i++)
        front = (front + 1) % capacity;
    if (m < n)
        printf("top of element %d\n", queue[front]);
    return 0;
}

