#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};
struct node *front = NULL;
struct node *rear = NULL;
void enqueue(int value)
{
    struct node *newNode;
    newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;
    if (rear == NULL)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}
void printQueue()
{
    struct node *temp;
    int first = 1;
    temp = front;
    while (temp != NULL)
    {
        if (first == 0)
            printf(" ");
        printf("%d", temp->data);
        first = 0;
        temp = temp->next;
    }
    printf("\n");
}
void dequeue()
{
    struct node *temp;
    if (front == NULL)
        return;
    temp = front;
    front = front->next;
    if (front == NULL)
        rear = NULL;
    free(temp);
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
    }
    printQueue();
    dequeue();
    printQueue();
    return 0;
}

