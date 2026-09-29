#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};
struct node *rear = NULL;
void enqueue(int value)
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = value;
    if (rear == NULL)
    {
        rear = newNode;
        newNode->next = newNode;
    }
    else
    {
        newNode->next = rear->next;
        rear->next = newNode;
        rear = newNode;
    }
}
int main()
{
    int n;
    int i;
    int value;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &value);
        enqueue(value);
        printf("%d\n", value);
    }
    return 0;
}

