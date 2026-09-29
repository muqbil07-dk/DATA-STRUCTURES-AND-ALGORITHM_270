#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void create(struct node **head, int data)
{
    struct node *new_node;
    struct node *last;

    new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    last = *head;
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

void deleteFirst(struct node **head, int count)
{
    struct node *temp;
    int i;

    for (i = 0; i < count && *head != NULL; i++) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

void display(struct node *head)
{
    struct node *current;

    printf("Linked List:");
    current = head;
    while (current != NULL) {
        printf("->%d", current->data);
        current = current->next;
    }
    printf("\n");
}

int main(void)
{
    struct node *head;
    int n;
    int value;
    int count;
    int i;

    head = NULL;
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        create(&head, value);
    }
    scanf("%d", &count);

    deleteFirst(&head, count);
    display(head);
    return 0;
}

