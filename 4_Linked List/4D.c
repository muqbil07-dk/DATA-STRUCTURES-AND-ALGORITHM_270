#include <stdio.h>
#include <stdlib.h>
struct node {
    int data;
    struct node *next;
};
struct node *start = NULL;
void append(int data)
{
    struct node *new_node;
    struct node *current;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;

    if (start == NULL) {
        start = new_node;
        return;
    }
    current = start;
    while (current->next != NULL)
        current = current->next;
    current->next = new_node;
}
int insertBefore(int before, int value)
{
    struct node *new_node;
    struct node *current;
    struct node *previous;
    if (start == NULL)
        return 0;
    if (start->data == before) {
        new_node = (struct node *)malloc(sizeof(struct node));
        new_node->data = value;
        new_node->next = start;
        start = new_node;
        return 1;
    }
    previous = start;
    current = start->next;
    while (current != NULL && current->data != before) {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
        return 0;
    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = current;
    previous->next = new_node;
    return 1;
}
void display(void)
{
    struct node *current;
    printf("Linked List:");
    current = start;
    while (current != NULL) {
        printf("->%d", current->data);
        current = current->next;
    }
    printf("\n");
}
int main(void)
{
    int n;
    int value;
    int before;
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        append(value);
    }
    scanf("%d", &before);
    scanf("%d", &value);
    if (!insertBefore(before, value))
        printf("Node not found!\n");
    display();
    return 0;
}

