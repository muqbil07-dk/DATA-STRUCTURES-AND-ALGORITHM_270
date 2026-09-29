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
    if (front == NULL)
    {
        front = newNode;
        rear = newNode;
        newNode->next = newNode;
    }
    else
    {
        newNode->next = front;
        rear->next = newNode;
        rear = newNode;
    }
}
void display()
{
    struct node *temp;
    int first = 1;
    if (front == NULL)
    {
        printf("\n");
        return;
    }
    temp = front;
    do
    {
        if (first == 0)
            printf(" ");
        printf("%d", temp->data);
        first = 0;
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}
void dequeue()
{
    struct node *temp;
    if (front == NULL)
        return;
    temp = front;
    if (front == rear)
    {
        front = NULL;
        rear = NULL;
    }
    else
    {
        front = front->next;
        rear->next = front;
    }
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
    display();
    dequeue();
    display();
    dequeue();
    display();
    return 0;
}
