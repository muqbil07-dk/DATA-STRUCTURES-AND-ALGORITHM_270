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
int dequeue()
{
    struct node *temp;
    int value;
    if (front == NULL)
        return -1;
    temp = front;
    value = temp->data;
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
    return value;
}
void display()
{
    struct node *temp;
    printf("Elements in Circular Queue are:");
    if (front != NULL)
    {
        temp = front;
        do
        {
            printf("%d", temp->data);
            if (temp != rear)
                printf(" ");
            temp = temp->next;
        } while (temp != front);
    }
    printf("\n");
}
int main()
{
    int n;
    int i;
    int value;
    int deleted;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &value);
        enqueue(value);
    }
    display();
    deleted = dequeue();
    printf("Deleted value = %d\n", deleted);
    deleted = dequeue();
    printf("Deleted value = %d\n", deleted);
    display();
    return 0;
}

